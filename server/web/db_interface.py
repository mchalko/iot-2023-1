#!/usr/bin/python3
# Author: Miroslav Chalko
# Interface for the database

import pymongo 
import multiprocessing

KEYS = ["temperature", "pressure", "light"]

dbclient = pymongo.MongoClient("mongodb://localhost:27017/")
db = dbclient["iot-database"]
collection = db["data"]
process = None

last_data = None

def _watch_db(data):
    """ Watch database for changes "" """
    watcher = collection.watch([{'$match': {'operationType': 'insert'}}])
    for change in watcher:
        for k, v in change["fullDocument"].items():
            data[k] = v

def _id_to_time(id):
    """ Convert id to time """
    return id.generation_time.strftime("%d.%m. %H:%M")


def get_last_data():
    """ Get last data from database """
    return {k:v for k, v in last_data.items() if k in KEYS}

def get_last_time():
    """ Get last time of data insertion """
    return _id_to_time(last_data["_id"])

def get_last(key:str, count:int) -> dict:
    """ Get last count values of key """
    if key not in KEYS:
        return {}
    return { _id_to_time(x["_id"]): x[key] for x in collection.find(sort=[('_id', pymongo.DESCENDING)], limit=count)}
    
def init():
    """ Initialize and start watching database """
    global process, last_data
    last_data = multiprocessing.Manager().dict()
    for k, v in collection.find_one(sort=[('_id', pymongo.DESCENDING)]).items():
        last_data[k] = v
    process = multiprocessing.Process(target=_watch_db, args=(last_data,))
    process.start()
    
def stop():
    """ Stop watching database """
    process.terminate()
    