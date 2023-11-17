#!/bin/bash
# Author: Miroslav Chalko
# Stop script for server

sudo systemctl stop mongod
kill -9 `cat log/web_pid`
rm log/web_pid
kill -9 `cat log/coap_pid`
rm log/coap_pid
