import bottle
import mqtt_client as mqtt
import os
import sys


SERVER_OPTS = {
        "host": "0.0.0.0",
        "port": 80,
        "reloader": False,
        "debug": True,
        "quiet": False
    }

STATIC_WEB_ROUTES = {
    "/" : "index",
}

def make_path(path):
    p =  f"{os.path.dirname(os.path.abspath(sys.argv[0]))}/views/{path}"
    return p

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

@route('/sensor', method='POST')
def get_value(name):
    return "0"


for k, v in STATIC_WEB_ROUTES.items():
    # apply custom headers
    route(k, "GET")(lambda x=v, **kwargs : bottle.template(make_path(x), **kwargs))
    

# ------------------------------------------------------------------------------
# Run the httpserver
# ------------------------------------------------------------------------------
mqtt.connect()
bottle.run(**SERVER_OPTS)
mqtt.disconnect()