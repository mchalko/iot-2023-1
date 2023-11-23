<!-- ## Project 1 for IoT course at university of Oulu

- Assignment : [link](assignment.pdf)
- RIOT documentation : https://doc.riot-os.org/
- Testbed docs : https://www.iot-lab.info/docs/
- Testbed : https://www.iot-lab.info/testbed
- Testbed labs : https://labs.iot-lab.info/
- MQTT broker : https://mosquitto.org/
- Cloud service : Trying oracle cloud infrastructure?

---

- Used hardware : ? -->


# Mini Lab Project 1 - Internet of Things - 521043S-3004

**Group Members** -
- Miroslav Chalko
- Kuisma Hannuksela
- Sehani Siriwardana

## Introduction to project

### Description
This is a team project that create software solution enabling the secure and energy-efficient transmission of sensor data from smart objects to a cloud backend. Additionally, the collected data will be visualized through the cloud. 

### Project scope

In this project, using sensors measure weather parameters such as temperature, pressure and light, store the data in cloud and display data in a webpage.

![Local Image](images/diagram_of_project.png)


## Technologies used in project

### Boards and Sensors
In this project, we used the IoT-LaB M3 type board in FIT IOT-LAB test bed and focused on the sensors,
- Light sensor -  This measures ambient light intensity in lux - ISL29020
- Pressure  and Temperature sensor - This measures atmospheric pressure in hPa - LPS331AP

Sensors are accesses via I2C protocol.

![Local Image](images/Architecture.PNG)

[FIT IOT-LAB](https://www.iot-lab.info/docs/boards/iot-lab-m3/)


### Operating System 
The FIT IOT-LAB M3 board which is mounted on FIT IOT-LAB testbed is running RIOT (https://www.riot-os.org) operating system.

### Protocols 
The measurment data aquired by sensors are trnsfer through internet via Ipv6, DTLS, CoAP protocols.

IPv6 (Internet Protocol version 6) is the latest version of the Internet Protocol, offering a larger address space. 

DTLS (Datagram Transport Layer Security) is a security protocol providing communication privacy for datagram protocols.

CoAP (Constrained Application Protocol) is a lightweight web transfer protocol designed for resource-constrained devices, often used in IoT applications. The CoAP server was implemented by using python library ```iaocoap```.

### Cloud 
Oracle cloud was selected as the cloud infrastructure we were going to use. Following are the feature of Oracle cloud,

Free for Limited-time 30 day free trial
- US $300 credit for 30 days
- Up to eight instances across all available services
- Up to 5 TB of storage

Always Free
- Compute: (Note- 1 Oracle OCPU = 2 vCPUs)
- 2 AMD-based VMs: 1/8 OCPU = 0.25 vCPU with 1 GB RAM each
- 4 Arm-based VMs: 24 GB RAM total, 3,000 OCPU hours and - 18,000 GB memory hours per month
- 2 Block Volumes Storage, 200 GB total
- 10 GB Object Storage - Standard
- 10 GB Object Storage - Infrequent Access
- 10 GB Archive Storage
- 10TB of network data egress/month per originating region
- Resource Manager (managed terraform)
- 5 OCI Bastions
- 2 Oracle Autonomous Databases incl. Oracle Application Express (APEX), Oracle SQL Developer etc., each with 20GB storage
- NoSQL Database with 25GB storage per table, up to 3 tables
- 4 Load Balancers: 1 Flexible (10Mbps) and 3 Network
Monitoring and Notifications


### Database and Webpage

The MongoDB was selected as the database management system and 

## Procedure

- First, the FIT IOT-LAB test M3 board was selected from the test bed. We focused only on two sensors in this board, namely light sensor and pressure and temperature sensor.  



