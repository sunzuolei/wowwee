# The driver and field test demos for Rovio Wowwee
`Cmake` `C++` `driver` `Linux`

![Alt text](./driver/Rovio Wowwee.jpg)

The driver is developed under **Ubuntu 14.04**, but it should work with all the **Linux** distributions. Before you use the driver to control your Rovio, please pay some attention to the below:

## Table of Contents 
-------------------
- [Dependencies](#library-dependencies)
- [Demo](#demo)
      - [The Obstacle Avoiding](#the-obstacle-avoiding)
      - [The camera capture an image](#the-camera-capture-an-image)
      - [The rovio can find the biggest pink square and mark it](#the-rovio-can-find-the-biggest-pink-square-and-mark-it)
      - [The rovio can track the object that you boxed out](#the-rovio-can-track-the-object-that-you-boxed-out)
- [How to run a demo](#how-to-run-a-demo)
- [Contributor](#Contributor)

## Dependencies
----------------------
The building will fail if the required third part libraries are not available on your machine. Please run the following command to install CMake, OpenCV, libjpeg by apt-get: 

```
sudo apt-get install cmake libopencv-dev libjpeg
```
## Demos
-------------------
### Obstacle Avoiding
>The demo is to test the IR function. If there is obstacle in front of the Rovio, it will turn left, otherwise, it will go forward. Please watch the online [video](http://v.youku.com/v_show/id_XODE5MjYyMTQw.html).

### The camera capture an image and save it
>The demo is to capture image and show it in the screen, then save it in a folder that you can define in saveImage member functiion.

### The rovio can find the biggest pink square and mark it
>Please watch the online [video](http://v.youku.com/v_show/id_XMTMxMjAwNTMzMg==.html?from=y1.7-1.2&qq-pf-to=pcqq.c2c)

### The rovio can track the object that you boxed out
>The demo use the TLD algrithm, functional but slow, I put the TLD in thirdpart folder.

## How to run a demo
-------------------
First you should connect to the Rovio's network, you could use the adhoc model or local lan network, I test the driver with the adhoc model, just  connect to the WiFi (SSID:ROVIO_WOWWEE)
```
cd Wowwee
mkdir build
cd build
cmake ..
make
cd ../demo_run
./obstacleavoidance
./findpinksquare
./saveimage
./run_tld -p ../thirdpart/TLD/parameters.yml -tl
```
## References
-------------------
This work would be impossible without the excellent open source projects:
* [Rovio WowWee driver API](http://kujo.cs.pitt.edu/cs1567/index.php/CPP_API) from University of Pittsburgh
* [The award-winning, real-time Algorithm Tacking-Learning-Detection (TLD)](http://personal.ee.surrey.ac.uk/Personal/Z.Kalal/tld.html), which is built in Matlab initially, the famous [paper](http://kahlan.eps.surrey.ac.uk/featurespace/tld/Publications/2011_tpami) can help you to understand details.   
* [The C++ version of TLD](https://github.com/alantrrs/OpenTLD) modified by Alantrrs

## Contributor
-------------------
- 张子洋: [zzy@mpig.com.cn](zzy@mpig.com.cn)

---------
Cheers!
:panda_face:



