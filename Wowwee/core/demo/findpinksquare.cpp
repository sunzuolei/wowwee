#include "robotdriver.h"
#include "robotcolor.h"
#include <iostream>
#include <string>

int main() {
   int major ,minor ;
   IplImage *image = NULL, *hsv = NULL, *threshold = NULL;
   SquaresType *squares, *biggest, *sq_idx;
   CvPoint pt1, pt2;
   int sq_amt;
   const char *IP = "192.168.10.18";
	// Setup the robot interface
    RobotInterface *robot = new RobotInterface(IP, 0);

	// Print the API Version
    robot->APIVersion(&major, &minor);
	std::cout << "Robot API Test: API Version v" << major << "." << minor << std::endl;
	
	// Setup the camera
    if(robot->cameraConfigure(RI_CAMERA_DEFAULT_BRIGHTNESS, RI_CAMERA_DEFAULT_CONTRAST, 30, RI_CAMERA_RES_640, RI_CAMERA_QUALITY_HIGH)) {
		std::cout << "Failed to configure the camera!" << std::endl;
		exit(-1);
	}
	
	// Create a window to display the output
	cvNamedWindow("Rovio Camera", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Biggest Square", CV_WINDOW_AUTOSIZE);
	
	// Create an image to store the image from the camera
	image = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);

	// Create an image to store the HSV version in
	// We configured the camera for 640x480 above, so use that size here
	hsv = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);

	// And an image for the thresholded version
	threshold = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);

	// Move the head up to the middle position
    //robot->move(RI_HEAD_MIDDLE, RI_FASTEST);

	// Action loop
	do {
		// Update the robot's sensor information
		if(robot->update() != RI_RESP_SUCCESS) {
			std::cout << "Failed to update sensor information!" << std::endl;
			continue;
		}
		
		// Get the current camera image and display it
		
		if(robot->getImage(image) != RI_RESP_SUCCESS) {
			std::cout << "Unable to capture an image!" << std::endl;
			continue;
		}
		cvShowImage("Rovio Camera", image);
		
		// Convert the image from RGB to HSV
		cvCvtColor(image, hsv, CV_BGR2HSV);

		// Pick out only the pink color from the image
		cvInRangeS(hsv, RC_PINK_LOW, RC_PINK_HIGH, threshold);

		// Find the squares in the image
		squares = robot->findSquares(threshold, RI_DEFAULT_SQUARE_SIZE);
		
		// Loop over the squares and find the biggest one
		biggest = squares;
		sq_idx = squares;
		while(sq_idx != NULL) {
			if(sq_idx->area > biggest->area)
				biggest = sq_idx;
			sq_idx = sq_idx->next;
		}
		
		// Only draw if we have squares
		if(biggest != NULL) {
			// Draw an X marker on the image
			sq_amt = (int) (sqrt(biggest->area) / 2);	

			// Upper Left to Lower Right
			pt1.x = biggest->center.x - sq_amt;
			pt1.y = biggest->center.y - sq_amt;
			pt2.x = biggest->center.x + sq_amt;
			pt2.y = biggest->center.y + sq_amt;
			cvLine(image, pt1, pt2, CV_RGB(0, 255, 0), 3, CV_AA, 0);

			// Lower Left to Upper Right
			pt1.x = biggest->center.x - sq_amt;
			pt1.y = biggest->center.y + sq_amt;
			pt2.x = biggest->center.x + sq_amt;
			pt2.y = biggest->center.y - sq_amt;
			cvLine(image, pt1, pt2, CV_RGB(0, 255, 0), 3, CV_AA, 0);
		}

		// Display the image with the drawing on it
		cvShowImage("Biggest Square", image);
		
		// Update the UI (10ms wait)
		cvWaitKey(10);

		// Release the square data
		while(squares != NULL) {
			sq_idx = squares->next;
			delete(squares);
			squares = sq_idx;	
		}

        // Move forward unless there's something in front of the robot
       if(!robot->IRDetected())
        robot->move(RI_MOVE_FORWARD, RI_SLOWEST);
	} while(1);	

	// Clean up (although we'll never get here...)
	delete(robot);

	cvDestroyWindow("Rovio Camera");
	cvDestroyWindow("Biggest Square");
	
	// Free the images
	cvReleaseImage(&hsv);
	cvReleaseImage(&threshold);
	cvReleaseImage(&image);


	return 0;
}

