# The Driver for Rovio Wowwee
`Cmake` `C++` `driver` `Linux`

![Alt text](./Wowwee/Rovio Wowwee.jpg)

The driver is under **linux**, and I test it with **ubuntu 14.04**. Before you use the driver to control your Rovio, please pay some attention to the below:
 
-------------------

## Library Dependencies

Before you use the driver, you need to install some dependencies.

### Cmake 
> sudo apt-get install cmake

### Opencv
>sudo apt-get install libopencv-dev

###libjpeg

>sudo apt-cache search libjpeg
>sudo apt-get install libjpeg


-------------------

## The member function 

###configuration

### mobility control

### infrared


### camera

### LED

### sensor data
-------------------

## Demo
### The Obstacle Avoiding
>The demo is to test the IR function. If there is obstacle in front of the Rovio, it will turn left. And it will go forward if there is no obstacle. 

### The camera capture an image

-------------------
## How to run a demo
First you should connect to the Rovio's network, you could use the adhoc model or local lan network, I test the driver with the adhoc model, just  connect to the Wifi(SSID:ROVIO_WOWWEE)

>cd Wowwee

>mkdir build

>cd build

>cmake ..

>make

>cd ../testbin

>./testobstacleavoiding

-------------------

## For more information
- E-mail:[sunzuolei@gmail.com](sunzuolei@gmail.com)

---------
Thank you!
:panda_face:



