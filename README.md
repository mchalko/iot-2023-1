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

## Introduction to project

### Description
This is a team project that create software solution enabling the secure and energy-efficient transmission of sensor data from smart objects to a cloud backend. Additionally, the collected data will be visualized through the cloud. 

### Project scope

In this project, using sensors measure weather parameters such as temperature, pressure and light, store the data in cloud and display data in a webpage.

![Local Image](../iot-2023-1/images/diagram_of_project.png)


## Technologies used in project

### Boards and Sensors
In this project, we used the IoT-LaB M3 type board in FIT IOT-LAB test bed and focused on the sensors,
- Light sensor -  This measures ambient light intensity in lux - ISL29020
- Pressure  and Temperature sensor - This measures atmospheric pressure in hPa - LPS331AP

Sensors are accesses via I2C protocol.

![Local Image](../iot-2023-1/images/Architecture.PNG)

[FIT IOT-LAB](https://www.iot-lab.info/docs/boards/iot-lab-m3/)


### Operating System 
The FIT IOT-LAB M3 board which is mounted on FIT IOT-LAB testbed is running RIOT (https://www.riot-os.org) operating system.

### Protocols 
The measurment data aquired by sensors are trnsfer through internet via Ipv6, DTLS, CoAP protocols.

IPv6 (Internet Protocol version 6) is the latest version of the Internet Protocol, offering a larger address space. 

DTLS (Datagram Transport Layer Security) is a security protocol providing communication privacy for datagram protocols.

CoAP (Constrained Application Protocol) is a lightweight web transfer protocol designed for resource-constrained devices, often used in IoT applications.


