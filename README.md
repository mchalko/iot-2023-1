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
This is a team project that creates software solutions enabling the secure and energy-efficient transmission of sensor data from smart objects to a cloud backend. Additionally, the collected data will be visualized through the cloud.

### Project scope

In this project, sensors measure weather parameters such as temperature, pressure and light, store the data in clouds and display data in a webpage.


![Local Image](images/diagram_of_project.png)


## Technologies used in project


### Boards and Sensors
In this project, we used the IoT-LaB M3 type board in FIT IOT-LAB test bed and focused on the sensors,
- Light sensor -  This measures ambient light intensity in lux - ISL29020
- Pressure  and Temperature sensor - This measures atmospheric pressure in hPa - LPS331AP


Sensors are accessed via I2C protocol.


![Local Image](images/Architecture.PNG)


[FIT IOT-LAB](https://www.iot-lab.info/docs/boards/iot-lab-m3/)



### Operating System
The FIT IOT-LAB M3 board which is mounted on the FIT IOT-LAB testbed is running RIOT (https://www.riot-os.org) operating system.


### Protocols
The measurement data acquired by sensors are transferred through the internet via Ipv6, DTLS, CoAP protocols.


IPv6 (Internet Protocol version 6) is the latest version of the Internet Protocol, offering a larger address space.


DTLS (Datagram Transport Layer Security) is a security protocol providing communication privacy for datagram protocols.


CoAP (Constrained Application Protocol) is a lightweight web transfer protocol designed for resource-constrained devices, often used in IoT applications. The CoAP server was implemented by using the python library ```iaocoap```.


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
- Virtual Cloud Networks (VCN): Maximum of 2 VCNs, includes IPv4 and IPv6 support


### Database and Web Page


MongoDB was selected as the database management system and the implementation of the database interface was done by using python library ```pymongo```.


The webpage was developed using Bottleneck Framework and Bootstrap.


## Procedure


- First, the FIT IOT-LAB test M3 board was selected from the test bed. We focused only on two sensors in this board, namely light sensor and pressure and temperature sensor. SEnsors continue to measure light intensity, atmospheric pressure and ambient temperature.


- Then, initiate the pressure sensor and light sensor to start sampling data using I2C communication. There is one sensor to measure both pressure and temperature. It reads temperature and Pressure. Then, the light sensor reads light intensity. These 2 sensors connected to the MCU via the I2C bus are embedded into the IoT-LAB M3 board. At MCU, temperature, pressure and light intensity raw measured data are converted to values in Celcius, Pascal and Lux respectively.


    - Sensor reading cycle summary


        -  libraries used:
            - lpsxxx: RIOT pressure and temperature sensor driver
                - bug in the driver caused wrong temperature readings in the range of 170+ Celsius
                    (https://github.com/RIOT-OS/RIOT/issues/20093)
                - fixed with internal driver lpsxxx_internal / lps331
            - isl29020: RIOT light sensor driver for measuring ambient light in lux
            - ztimer for setting sleep time
                - RIOT OS will set the deepest possible sleep mode when idle.
        - modules:
        - Sleep time between measurements:
            - dynamically scaled between 2.5 and 60 seconds after each reading cycle
            - 1000 * (30.0 / diff^2) ms,
            where diff = difference between consecutive measurements * sensor-specific sensitivity multiplier
            (max diff of the two lps measurements used)


- Then, the board (end-node) is connected to 802.15.4 network, which is a local network. The data acquired are transferred through this network. In order to connect to the internet we use a border router. Here, this border router is also connected to the same local 802.15.4 network and this border router is connected to the master board using a serial link. The data that transferred my en-node is now transferred to the master board through serial link. Then, this master board transfers data to internet as normal ipv6 packet and it is received by the server which is running on a linux machine to process.


- The data transferred to internet is stored in MongoDB which the in between communication is carried using CoAP and also the measured data (temperature, pressure and light intensity) including time(UTC) are transferred to the web page to display. In the second case, the communication is carried out using CoAP and DTLS for encryption. [Click here to go to webpage](http://144.24.196.189:8080/)



## Demonstration


The following is the demonstration video of our project,


[![DEMO VIDEO](images/demo_project.png)](https://youtu.be/iyjr8yyTiv8)




