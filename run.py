#!/usr/bin/python3
# Author: Miroslav Chalko
# Script for automatic deployment of experiment on IoT-LAB

import json
import subprocess
import glob
import os
import argparse

# public IP ranges for each site
IP_RANGE = {
    "grenoble": "2001:660:5307:3100::/64 - 2001:660:5307:317f::/64",
    "lille": "2001:660:4403:0480::/64 - 2001:660:4403:04ff::/64",
    "saclay": "2001:660:3207:04c0::/64 - 2001:660:3207:04ff::/64",
    "strasbourg": "2a07:2e40:fffe:00e0::/64 - 2a07:2e40:fffe:00ff::/64"
}

SITE = "grenoble" # site where experiment will be run
NAME = "IOTproject" # name of experiment
DURATION = 120 # duration of experiment in minutes
TIMEOUT = 30 # timeout for experiment to start
WIRELESS_CHANNEL = 18 # wireless channel for 802.15.4
PAN_ID = 0x2288 # pan id for 802.15.4
BOARD = "iotlab-m3" # board type

END_NODE_PATH = "end-node" # path to end-node firmware
ROUTER_PATH = "border-router" # path to router firmware


def run_command(command: str) -> str:
    """ Run command and return stdout """
    print("> " + command)
    result = subprocess.run(command.split(
        " "), stdout=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print(f"Failed to run command {command}")
        exit(1)
    return result.stdout.strip()


def get_executable(path: str) -> str:
    """ Get firmware executable by path """
    return glob.glob(f"{path}/bin/{BOARD}/*.bin")[0]


def get_experiment() -> str:
    """ Try to get experiment id with given name """
    # check if experiment is already running
    result = run_command("iotlab-experiment get -e")
    result = json.loads(result)
    if "Running" in result:
        running_ids = result["Running"]
        for id in running_ids:
            result = run_command(f"iotlab-experiment get -i {id} -p")
            if json.loads(result)["name"] == NAME:
                print(f"Found experiment {id} with matching name")
                return id
    return None


def create_experiment() -> str:
    """ Create new experiment """
    # reserve nodes
    result = run_command(
        f"iotlab-experiment submit -n {NAME} -d {DURATION} -l 2,archi=m3:at86rf231+site={SITE}")
    experiment_id = json.loads(result)["id"]
    print(f"Experiment {experiment_id} created")
    return experiment_id


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="run.py", description="Script for automatic deployment of experiment on IoT-LAB")
    parser.add_argument(
        "-r", "--router", help="Flash router fw", action="store_true")
    parser.add_argument("-e", "--endnode",
                        help="Flash end-node fw", action="store_true")
    parser.add_argument("-t", "--terminate",
                        help="Terminate experiment", action="store_true")
    args = parser.parse_args()

    # create experiment
    experiment_id = get_experiment()
    if args.terminate:  # check if only terminate
        if experiment_id is not None:
            run_command(f"iotlab-experiment stop -i {experiment_id}")
        print("Experiment terminated")
        exit(0)
    if experiment_id is None:
        experiment_id = create_experiment()

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
    end_node_id, router_id = [a.split(".")[0]
                              for a in json.loads(result)["nodes"]]
    print(f"End node id: {end_node_id}, Router id: {router_id}")

    # make fw for nodes
    if args.endnode:
        run_command(
            f"make -C {END_NODE_PATH} BOARD={BOARD} DEFAULT_CHANNEL={WIRELESS_CHANNEL} DEFAULT_PAN_ID={PAN_ID} clean all")
    if args.router:
        run_command(
            f"make -C {ROUTER_PATH} ETHOS_BAUDRATE=500000 BOARD={BOARD} DEFAULT_CHANNEL={WIRELESS_CHANNEL} DEFAULT_PAN_ID={PAN_ID} clean all")
    if args.endnode or args.router:
        print("Firmware built")
    # flash nodes
    if args.endnode:
        run_command(
            f"iotlab-node -i {experiment_id} --flash {get_executable(END_NODE_PATH)} -l {SITE},{end_node_id.replace('-',',')}")
    if args.router:
        run_command(
            f"iotlab-node -i {experiment_id} --flash {get_executable(ROUTER_PATH)} -l {SITE},{router_id.replace('-',',')}")
    if args.endnode or args.router:
        print("Firmware flashed")

    if args.router:
        print(f"""
To start router open a new terminal, ssh to {SITE}, check free interfaces and start router:
ssh <name>@{SITE}.iot-lab.info
ip -6 addr | grep tap
sudo ethos_uhcpd.py {router_id} <tap> <ipv6_prefix>::/64

Available prefixes for {SITE} are {IP_RANGE[SITE]}""")
