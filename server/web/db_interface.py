#!/usr/bin/python3
# Author: Miroslav Chalko
# Interface for the database

import pymongo 

KEYS = ["temperature", "pressure", "light"]
HOST = "mongodb://localhost:27017/"
DB_NAME = "iot-database"
COLLECTION_NAME = "data"

dbclient = pymongo.MongoClient(HOST)
db = dbclient[DB_NAME]
collection = db[COLLECTION_NAME]

def _id_to_time(id):
    """ Convert id to time """
    return id.generation_time.strftime("%d.%m. %H:%M")

def get_last_data():
    """ Get last data from database """
    return {k:v for k, v in collection.find_one(sort=[('_id', pymongo.DESCENDING)]).items() if k in KEYS}

def get_last_time():
    """ Get last time of data insertion """
    return _id_to_time(collection.find_one(sort=[('_id', pymongo.DESCENDING)])["_id"])

def get_last(key:str, count:int) -> dict:
    """ Get last count values of key """
    if key not in KEYS:
        return {}
    return { _id_to_time(x["_id"]): x[key] for x in collection.find(sort=[('_id', pymongo.DESCENDING)], limit=count)}

def get_last_all(count:int) -> dict:
    """ Get last count values """
    return { _id_to_time(x["_id"]): {k : x[k] for k in KEYS} for x in collection.find(sort=[('_id', pymongo.DESCENDING)], limit=count)}
