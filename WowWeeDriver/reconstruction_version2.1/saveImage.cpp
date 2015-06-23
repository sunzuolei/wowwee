#include "robotdriver.h"
#include "robotcolor.h"
#include <iostream>
#include <string>

int main() {
    int major, minor;
    IplImage *image = NULL;
   const char *IP = "192.168.10.18";
    // Setup the robot interface
    RobotInterface *robot = new RobotInterface(IP, 0);

    // Print the API Version
    robot->APIVersion(&major, &minor);
    std::cout << "Robot API Test: API Version v" << major << "." << minor << std::endl;

    // Setup the camera
    if(robot->cameraConfigure(RI_CAMERA_DEFAULT_BRIGHTNESS, RI_CAMERA_DEFAULT_CONTRAST, 5, RI_CAMERA_RES_640, RI_CAMERA_QUALITY_HIGH)) {
        std::cout << "Failed to configure the camera!" << std::endl;
        exit(-1);
    }

    // Create a window to display the output
    cvNamedWindow("Rovio Camera", CV_WINDOW_AUTOSIZE);


    // Create an image to store the image from the camera
    image = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);

    // Move the head up to the middle position
  //  robot->move(RI_HEAD_MIDDLE, RI_FASTEST);
    // Update the robot's sensor information
     robot->getImage(image);
     cvShowImage("Rovio Camera", image);
     cvWaitKey(0);
    robot->saveImage(image);


    // Clean up (although we'll never get here...)
    delete(robot);

    return 0;
}
