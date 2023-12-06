#!/bin/bash
# Author: Miroslav Chalko
# Start script for server

DIR=$(dirname $(realpath -s $0))

mkdir -p log
sudo systemctl start mongod
nohup python $DIR/server.py > $DIR/log/coap.log 2>&1 &
echo $! > $DIR/log/coap_pid
nohup python $DIR/web/web.py > $DIR/log/web.log 2>&1 &
echo $! > $DIR/log/web_pid

