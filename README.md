# The Driver for Rovio Wowwee
`Cmake` `C++` `driver` `Linux`

![Alt text](./Wowwee/Rovio Wowwee.jpg)

The driver is under **linux**, and I test it with **ubuntu 14.04**. Before you use the driver to control your Rovio, please pay some attention to the below:

## Table of Contents 
-------------------
- [Library Dependencies](#library-dependencies)
      - [Cmake](#cmake)
      - [Opencv](#opencv)
      - [libjpeg](#libjpeg)
- [The member function](#the-member-function)
      - [configuration](#configuration)
      - [mobility control](#mobility-control)
      - [infrared](#infrared)
      - [camera](#camera)
      - [LED](#led)
      - [sensor data](#sensor-data)
- [Demo](#demo)
      - [The Obstacle Avoiding](#the-obstacle-avoiding)
      - [The camera capture an image](#the-camera-capture-an-image)
- [How to run a demo](#how-to-run-a-demo)
- [For more information](#for-more-information)

## Library Dependencies
----------------------

Before you use the driver, you need to install some dependencies.

### Cmake 
> sudo apt-get install cmake

### Opencv
>sudo apt-get install libopencv-dev

###libjpeg

>sudo apt-cache search libjpeg

>sudo apt-get install libjpeg




## The member function 
-------------------

### configuration

### mobility control

### infrared

### camera

### LED

### sensor data


## Demo
-------------------
### The Obstacle Avoiding
>The demo is to test the IR function. If there is obstacle in front of the Rovio, it will turn left. And it will go forward if there is no obstacle. 

### The camera capture an image and save it
>The demo is to capture image and show it in the screen, then save it in a folder that you can define in saveImage member functiion.
### The rovio can find the biggest pink square and mark it.
>The demo you can see [http://v.youku.com/v_show/id_XMTMxMjAwNTMzMg==.html?from=y1.7-1.2&qq-pf-to=pcqq.c2c](http://v.youku.com/v_show/id_XMTMxMjAwNTMzMg==.html?from=y1.7-1.2&qq-pf-to=pcqq.c2c)
### The rovio can tracking object that you box out.
>The demo use the TLD algrithm, functional but slow, I put the TLD in thirdpart folder.

## How to run a demo
-------------------
First you should connect to the Rovio's network, you could use the adhoc model or local lan network, I test the driver with the adhoc model, just  connect to the Wifi(SSID:ROVIO_WOWWEE)

>cd Wowwee

>mkdir build

>cd build

>cmake ..

>make

>cd ../demo

>./testobstacleavoiding
>./findpinksquare
>./saveImage
>./run_tld -p ../core/thirdpart/parameters.yml


## For more information
-------------------
- E-mail:[szl@mpig.com.cn](szl@mpig.com.cn)

---------
Thank you!
:panda_face:



