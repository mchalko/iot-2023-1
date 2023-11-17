#!/bin/bash
# Author: Miroslav Chalko
# Start script for server

mkdir -p log
sudo systemctl start mongod
nohup python server.py > log/coap.log 2>&1 &
echo $! > log/coap_pid
cd web
nohup python web.py > ../log/web.log 2>&1 &
echo $! > ../log/web_pid

