#include "robotdriver.h"
#include "robotcolor.h"
#include <iostream>
#include <string>

int main() {
    int major, minor;
    IplImage *image = NULL;
    // Make sure we have a valid command line argument
    /*if(argv <= 1) {
        std::cout << "Usage: robot_test <address of robot>" << std::endl;
        exit(-1);
    }*/
 const char *IP = "192.168.10.18";
    // Setup the robot interface
    RobotInterface *robot = new RobotInterface(IP, 0);

    // Print the API Version
    robot->APIVersion(&major, &minor);
    std::cout << "Robot API Test: API Version v" << major << "." << minor << std::endl;

    if(robot->update() != RI_RESP_SUCCESS)
        std::cout << "Failed to update sensor information!" << std::endl;

      robot->IRDetected();
      robot->IRStatus();


    // Clean up (although we'll never get here...)
    //delete(robot);

    return 0;
}
