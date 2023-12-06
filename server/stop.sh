#!/bin/bash
# Author: Miroslav Chalko
# Stop script for server

DIR=$(dirname $(realpath -s $0))

sudo systemctl stop mongod
kill -9 `cat $DIR/log/web_pid`
rm $DIR/log/web_pid
kill -9 `cat $DIR/log/coap_pid`
rm $DIR/log/coap_pid
