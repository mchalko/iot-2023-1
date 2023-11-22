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
- Light sensor -  ISL29020
- Pressure  and Temperature sensor - LPS331AP
Sensors are accesses via I2C protocol.



Operating Systems - RIOT (https://www.riot-os.org)

Protocols - Ipv6, DTLS, CoAP


