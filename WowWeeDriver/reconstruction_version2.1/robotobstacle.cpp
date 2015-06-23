#include "robotdriver.h"
#include <iostream>
#include <string>

int main() {
   const char *IP ="192.168.10.18";

	// Setup the robot interface
   RobotInterface *robot = new RobotInterface(IP, 0);

	// Action loop
	do {
		// Update the robot's sensor information
        if(robot->update() != RI_RESP_SUCCESS) {
			std::cout << "Failed to update sensor information!" << std::endl;
			continue;

		}

		// Move forward unless there's something in front of the robot
        if(!robot->IRDetected())
        {robot->move(RI_MOVE_FORWARD, RI_FASTEST);
           printf("11");}
        else
            robot->move(RI_MOVE_LEFT,RI_FASTEST);

	} while(1);	

	// Clean up
	delete(robot);
	return 0;
}
