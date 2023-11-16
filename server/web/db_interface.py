#!/usr/bin/python3
# Author: Miroslav Chalko
# Interface for the database

import pymongo 
import multiprocessing

dbclient = pymongo.MongoClient("mongodb://localhost:27017/")
db = dbclient["iot-database"]
collection = db["data"]
process = None

last_data = None

def get_last_data():
    return {k:v for k, v in last_data.items() if k in ["temperature", "pressure", "light"]}

def get_last_time():
    return last_data["_id"].generation_time.strftime("%d.%m. %H:%M")

def _watch_db(data):
    watcher = collection.watch([{'$match': {'operationType': 'insert'}}])
    for change in watcher:
        for k, v in change["fullDocument"].items():
            data[k] = v
    
def init():
    global process, last_data
    last_data = multiprocessing.Manager().dict()
    for k, v in collection.find_one(sort=[('_id', pymongo.DESCENDING)]).items():
        last_data[k] = v
    process = multiprocessing.Process(target=_watch_db, args=(last_data,))
    process.start()
    
def stop():
    process.terminate()
    