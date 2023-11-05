#!/usr/bin/python3
# Author: Miroslav Chalko
# Script for automatic deployment of experiment on IoT-LAB

import json
import subprocess
import glob
import os

IP_RANGE = {
    "grenoble": "2001:660:5307:3100::/64 - 2001:660:5307:317f::/64",
    "lille": "2001:660:4403:0480::/64 - 2001:660:4403:04ff::/64",
    "saclay": "2001:660:3207:04c0::/64 - 2001:660:3207:04ff::/64",
    "strasbourg": "2a07:2e40:fffe:00e0::/64 - 2a07:2e40:fffe:00ff::/64"
}

SITE = "grenoble"
NAME = "IOTproject"
DURATION = 60
TIMEOUT = 30
WIRELESS_CHANNEL = 18
PAN_ID = 0x2288
BOARD = "iotlab-m3"

END_NODE_PATH = "end-node"
ROUTER_PATH = "border-router"

def run_command(command: str):
    print("> " + command)
    result = subprocess.run(command.split(
        " "), stdout=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print(f"Failed to run command {command}")
        print(result.stderr)
        exit(1)
    return result.stdout.strip()

def get_executable(path:str):
    return glob.glob(f"{path}/bin/{BOARD}/*.bin")[0]

if __name__ == "__main__":
    
    # check if experiment is already running
    result = run_command("iotlab-experiment get -e")
    result = json.loads(result)
    if "Running" in result:
        running_ids = result["Running"]
        for id in running_ids:
            result = run_command(f"iotlab-experiment get -i {id} -p")
            if json.loads(result)["name"] == NAME:
                experiment_id = id
                print(f"Experiment {experiment_id} already running, using it")
                break
    else :
        # reserve nodes
        result = run_command(
            f"iotlab-experiment submit -n {NAME} -d {DURATION} -l 2,archi=m3:at86rf231+site={SITE}")
        experiment_id = json.loads(result)["id"]
        print(f"Experiment {experiment_id} created")
    # wait for experiment to start
    result = run_command(
        f"iotlab-experiment wait -i {experiment_id} --timeout {TIMEOUT} --cancel-on-timeout")
    if result != '"Running"':
        print("Failed to start experiment")
        exit(1)
    print("Experiment started")
    # get node list
    result = run_command(
        f'iotlab-experiment get -i {experiment_id} -p')
    end_node_id, router_id = [a.split(".")[0] for a in json.loads(result)["nodes"]]
    print(f"End node id: {end_node_id}, Router id: {router_id}")
    # make fw for nodes
    run_command(
        f"make -C {END_NODE_PATH} BOARD={BOARD} DEFAULT_CHANNEL={WIRELESS_CHANNEL} DEFAULT_PAN_ID={PAN_ID}")
    run_command(f"make -C {ROUTER_PATH} ETHOS_BAUDRATE=500000 BOARD={BOARD} DEFAULT_CHANNEL={WIRELESS_CHANNEL} DEFAULT_PAN_ID={PAN_ID}")
    print("Firmware built")
    # flash nodes
    run_command(f"iotlab-node -i {experiment_id} --flash {get_executable(END_NODE_PATH)} -l {SITE},{end_node_id.replace('-',',')}")
    run_command(f"iotlab-node -i {experiment_id} --flash {get_executable(ROUTER_PATH)} -l {SITE},{router_id.replace('-',',')}")
    print("Firmware flashed")
    
    print(f"""
To start router open a new terminal, check free interfaces and run:
ip -6 addr | grep tap
sudo ethos_uhcpd.py {router_id} <tap> <ipv6_prefix>::/64"

Available prefixes for {SITE} are {IP_RANGE[SITE]}""")
