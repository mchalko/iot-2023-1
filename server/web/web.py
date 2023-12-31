#!/usr/bin/python3
# Author: Miroslav Chalko
# Web server for IoT-LAB project

import bottle
import db_interface as db
import os
import sys

SERVER_OPTS = {
        "host": "0.0.0.0",
        "port": 8080,
        "reloader": False,
        "debug": True,
        "quiet": False
    }

STATIC_WEB_ROUTES = {
    "/" : "home",
    "/home" : "home",
    "/about" : "about",
    "/data" : "data"
}

def route(path: str, method: str = "GET"):
    """Decorator to add default headers to routes"""
    def inner(func):
        def wrapper(*args, **kwargs):
            # add default headers
            bottle.response.set_header('Content-Language', 'en')
            return func(*args, **kwargs)
        bottle.route(path=path, method=method)(wrapper)
        return func
    return inner

@route('/get_data', method='POST')
def get_data():
    return db.get_last_data()

@route('/get_time', method='POST')
def get_time():
    return db.get_last_time()

# need to make sure we are in the right directory, so paths of views are correct
work_dir = os.path.dirname(os.path.abspath(sys.argv[0]))
os.chdir(work_dir)

# routes for static web pages
for k, v in STATIC_WEB_ROUTES.items():
    # apply custom headers
    route(k, "GET")(lambda x=v, **kwargs : bottle.template( f"views/{x}", **kwargs))
    
# Run the httpserver
bottle.run(**SERVER_OPTS)