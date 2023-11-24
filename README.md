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

The MongoDB was selected as the database management system and the implementation of database interface was done by using python library ```pymongo```. 

The webpage was developed using Bottleneck Framework and Bootstrap.

## Procedure

- First, the FIT IOT-LAB test M3 board was selected from the test bed. We focused only on two sensors in this board, namely light sensor and pressure and temperature sensor. SEnsors continues to measure light intensity, atmospheric pressure and ambient temperature. 

- Then, initiates the pressure sensor and light sensor to start sampling data using I2C communication. There is one sensor to mesasure both pressure and temperature. It reads temperature and then convert raw sensor data to temperature value in Celsius. The pressure raw sensor data converted to value in Pascals. Then, the light sensor reads light intensity and convert raw data to a value in lux. These 2 sensors connected to the MCU via the I2C bus are embedded into the IoT-LAB M3 board.

- Then, the board (end-node) is connected to 802.15.4 network, which is a local network. The data aquired are transferred throught this network. In order to connect to internet we use border router. Here, this border router also connectd to the same local 802.15.4 network and this border router is connected to master board using serial link. Tha data that transferred my en-node are now transferred to master board through serial link. Then, this master board transfer data to internet as normal ipv6 packet and it is recieved by the server that process data.

- The data transferred to internet is stored in MongoDB which the in between communcation is carried using CoAP and also 








## Demonstration

The following is the demonstration video of our project,

[![Amazing Video](images/demo_project.png)](https://youtu.be/iyjr8yyTiv8)

<!-- [![Amazing Video](https://img.youtube.com/vi/iyjr8yyTiv8/0.jpg)](https://youtu.be/iyjr8yyTiv8) -->

<!-- [![Alt Text](path/to/your/image.png)](https://www.youtube.com/your-video-link) -->
