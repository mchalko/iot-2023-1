#!/usr/bin/python3
# Author: Miroslav Chalko
# COAP server for IoT-LAB project, saves data into MongoDB database

import datetime
import logging
import asyncio
import aiocoap.resource as resource
from aiocoap.numbers.contentformat import ContentFormat
from aiocoap.credentials import CredentialsMap
import aiocoap
import pymongo 
import subprocess
import json

CLIENT_ID = "client"
CLIENT_PSK = "123"
KEYS = {"temperature" : float, "pressure" : float, "light" : int}

dbclient = pymongo.MongoClient("mongodb://localhost:27017/")
db = dbclient["iot-database"]
collection = db["data"]

def get_global_ipv6():
    """Returns the local IPv6 address of the device"""
    proc = subprocess.Popen("ip -6 addr | grep inet6", shell=True, stdout=subprocess.PIPE)
    out, err = proc.communicate()
    lines = out.decode('utf-8').split('\n')
    for line in lines:
        if 'global' in line:
            return line.strip().split(' ')[1].split('/')[0]
    return None

def get_local_time():
    """Returns the local time"""
    return datetime.datetime.now().strftime("%d-%m-%Y %H:%M")

class WelcomeResource(resource.Resource):
    """Default welcome resource"""
    async def render_get(self, request):
        return aiocoap.Message(payload=b"Welcome to the IoT-project COAP server", 
                               content_format=ContentFormat.TEXT)

class TimeResource(resource.Resource):
    """Resource providing current time"""
    async def render_get(self, request):
        return aiocoap.Message(payload=get_local_time().encode('ascii'))

class DataResource(resource.Resource):
    """Resource accepting data in PUT requests"""
    async def render(self, request):
        print('payload: %s' % request.payload)
        # try to parse the payload as json and save it to the database
        try:
            loaded = json.loads(request.payload.decode('utf-8'))
            data = {}
            for k, v in loaded.items():
                if k in KEYS.keys():
                    data[k] = KEYS[k](v)
            collection.insert_one(data)
            return aiocoap.Message(code=aiocoap.CREATED)
        except Exception as e:
            print("Error receiving data: " + str(e))
            return aiocoap.Message(code=aiocoap.INTERNAL_SERVER_ERROR, payload=str(e).encode('ascii'))

# logging setup
logging.basicConfig(level=logging.INFO)
logging.getLogger("coap-server").setLevel(logging.DEBUG)

async def main():
    print("Starting server..")
    
    root = resource.Site()
    root.add_resource(['.well-known', 'core'],
            resource.WKCResource(root.get_resources_as_linkheader))
    root.add_resource([], WelcomeResource())
    root.add_resource(['time'], TimeResource())
    root.add_resource(['data'], DataResource())
    
    creds = CredentialsMap()
    creds.load_from_dict({'*': {"dtls": {"psk": {"ascii": CLIENT_PSK}, "client-identity": {"ascii": CLIENT_ID}}}})

    address = get_global_ipv6()
    if address is None:
        print("No global IPv6 address found, exiting")
        return
    
    await aiocoap.Context.create_server_context(root, bind=(address, 5683), transports=["tinydtls_server", "tinydtls", "udp6"], server_credentials=creds)
    await asyncio.get_running_loop().create_future()

asyncio.run(main())