/** 
 *  @file robotdriver.h
 *  @brief This is a *.h file that define function,variables,structures and macros
 *
 *  @author zzy
 *  @date <March.27.2015>
 *  @version <2.0>
 *
 * The *.h File contains many macro definition and five important structure, class RobotInterface affirmed the ri 
 * member variables and some the member function including the control of the robot moving and rocker arm;infrared detect obstacles, image    
 * acquisition, update the data.
 */

#ifndef ROBOT_DRIVER_CPP_H
#define ROBOT_DRIVER_CPP_H

#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdint.h>
#include <stdbool.h>

// Sockets
#include <sys/socket.h>
#include <arpa/inet.h>

/**************************************
 * Movement Definitions
 **************************************/
#define RI_STOP			0                      ///<Stops any current movement.
#define RI_MOVE_FORWARD		1     ///<Moves the robot forward.
#define RI_MOVE_BACKWARD	2        ///<Moves the robot backward.
#define RI_MOVE_LEFT		3                ///<Moves the robot to the left.
#define RI_MOVE_RIGHT		4           ///<Moves the robot to the right.
#define RI_TURN_LEFT		5               ///<Turns the robot to the left.
#define RI_TURN_RIGHT		6         ///<Turns the robot to the right.

#define RI_MOVE_FWD_LEFT	7     ///<Moves the robot forward and left at the same time.
#define RI_MOVE_FWD_RIGHT	8     ///<Moves the robot forward and right at the same time.
#define RI_MOVE_BACK_LEFT	9    ///<Moves the robot backward and left at the same time.
#define RI_MOVE_BACK_RIGHT	10  ///<Moves the robot backward and right at the same time.

#define RI_TURN_LEFT_20DEG	17    ///<Rotates the robot 20 degrees to the left.
#define RI_TURN_RIGHT_20DEG	18  ///<Rotates the robot 20 degrees to the right.

#define RI_HEAD_UP		11                  ///<Moves the head to the highest position.
#define RI_HEAD_MIDDLE		13      ///<Moves the head to the middle position.
#define RI_HEAD_DOWN		12          ///<Moves the head to the lowest position.

#define RI_FASTEST		1                 ///<the fastest speed.
#define RI_SLOWEST		10              ///<the slowest speed.

/***************************************
 * Response Code Definitions
 ***************int************************/
#define RI_RESP_SUCCESS		0               ///<The function was successfully run.
#define RI_RESP_FAILURE		1                  ///<The function failed in an unspecified way.
#define RI_RESP_BUSY		2                      ///<The function is busy.
#define RI_RESP_NOT_IMPLEMENTED	3   ///<The function response unimplement.
#define RI_RESP_UNK_CGI		4             ///<The function response unk cgi.
#define RI_RESP_NO_NS_SIGNAL	5     ///<The function response no signal.

#define RI_RESP_PARAM_RANGE_ERR	22       ///<The function response that the parameter's range is error.
#define RI_RESP_NO_PARAM	23             ///<The function response no parameter.

/***************************************
 * Sensor data description
 ***************************************/
/** @brief The sensor data */
typedef struct {
    unsigned int		length;
    unsigned int		unused;
    unsigned int 		left_wheel_dir;
    unsigned int 		left_wheel_enc_ticks;
    unsigned int		right_wheel_dir;
    unsigned int		right_wheel_enc_ticks;
    unsigned int		rear_wheel_dir;
    unsigned int		rear_wheel_enc_ticks;
    unsigned int		unused2;
    unsigned int		head_position;
    unsigned int		battery;
    unsigned int		status;
} RIData;

// Wheel Direction
#define RI_WHEEL_MASK(x) ((x >> 1) & 1)    ///<The wheel's direction is mask(x).
#define RI_WHEEL_FORWARD	0                   ///<The wheel's direction is forward.
#define RI_WHEEL_BACKWARD	1              ///<The wheel's direction is backward.

// Wheel IDs
#define RI_WHEEL_LEFT	0                     ///<The wheel's ID is left.
#define RI_WHEEL_RIGHT	1                     ///<The wheel's ID is right.
#define RI_WHEEL_REAR	2                     ///<The wheel's ID is rear.

/* Status field in the sensor data */
#define RI_STATUS_LED		(1 << 0)
#define RI_STATUS_IR_POWER	(1 << 1)
#define RI_STATUS_IR_DETECTOR	(1 << 2)

/***************************************
 * Sensor report data description
 ***************************************/
/** @brief The sensor report data*/
typedef struct {
    /* Rovio location in relation to the room beacon */
    int			x, y; /* -32767 to 32768 */
    float			theta; /* -PI to PI */
    unsigned int		room_id; /* 0 = Home base, 1 - 9 other rooms */
    unsigned int		strength; /* Navigation signal strength: 0 - 65535: Strong > 47000, No Signal < 5000 */
    // Robot operational state
    unsigned int		state; /* RI_ROBOT_STATE below, current robot state */
    // Camera controls
    unsigned int		brightness; /* Brightness of the camera */
    unsigned int		cam_res; /* Camera Resolution */
    unsigned int		frame_rate; /* Camera frame rate */
    unsigned int		speaker_volume; /* Speaker volume */
    unsigned int		mic_volume; /* Microphone volume */
    // Wifi info
    unsigned int		wifi; /* Wifi signal strength */
    // Battery charge info
    unsigned int		battery; /* Battery level */
    unsigned int		charging; /* Battery charging */
    // Head position
    unsigned int		head_position; /* Head position */
} RIReport;

// Robot state values, describes the current action of the robot
#define RI_ROBOT_STATE_IDLE	0
#define RI_ROBOT_STATE_DRIVING	1
#define RI_ROBOT_STATE_DOCKING	2
#define RI_ROBOT_STATE_PATH	3
#define RI_ROBOT_STATE_REC_PATH	4

// Robot head positions
#define RI_ROBOT_HEAD_LOW	204
// MID is actually between 135 and 140
#define RI_ROBOT_HEAD_MID	137
#define RI_ROBOT_HEAD_HIGH	65

// Light Status
#define RI_LIGHT_OFF		0
#define RI_LIGHT_ON		1

// Nav Signal Strength
#define RI_ROBOT_NAV_SIGNAL_STRONG	3
#define RI_ROBOT_NAV_SIGNAL_MID		2
#define RI_ROBOT_NAV_SIGNAL_WEAK	1
#define RI_ROBOT_NAV_SIGNAL_NO_SIGNAL	0
// Wifi Signal Strength
#define RI_ROBOT_WIFI_LOW		0
#define RI_ROBOT_WIFI_HIGH		254

// Battery level
// Robot turns itself off below this level
#define RI_ROBOT_BATTERY_OFF		100
// Robot tries to go home below this level
#define RI_ROBOT_BATTERY_HOME		106
// Robot is operating under normal conditions below this level
#define RI_ROBOT_BATTERY_MAX		127

/* Camera definitions */
#define RI_CAMERA_DEFAULT_BRIGHTNESS	0x28
#define RI_CAMERA_DEFAULT_CONTRAST	0x48

// 176x144
#define RI_CAMERA_RES_176		0
// 320x240
#define RI_CAMERA_RES_320		1
// 352x240
#define RI_CAMERA_RES_352		2
// 640x480
#define RI_CAMERA_RES_640		3

// Microphone volume
#define RI_CAMERA_MIC_LOW		0
#define RI_CAMERA_MIC_HIGH		31

// Speaker volume
#define RI_CAMERA_SPEAKER_LOW		0
#define RI_CAMERA_SPEAKER_HIGH		31

// Camera quality
#define RI_CAMERA_QUALITY_LOW		0
#define RI_CAMERA_QUALITY_MID		1
#define RI_CAMERA_QUALITY_HIGH		2
#define RI_CAMERA_MAX_IMG_SIZE		(1024*1024)

// Camera I2C Addresses
#define RI_CAMERA_AGC_ADDR		0x14
#define RI_CAMERA_BRIGHTNESS_ADDR	0x55
#define RI_CAMERA_CONTRAST_ADDR		0x56
#define RI_CAMERA_NIGHTMODE_ADDR	0x3b

/** @brief Centroid data*/
typedef struct st SquaresType;
struct st {
    CvPoint center;
    int area;
    SquaresType *next;
};

// Default square size
#define RI_DEFAULT_SQUARE_SIZE			250

// Battery charging?
#define RI_BATTERY_CHARGING_THRESH	80

// Robot Games Server
#define DEFAULT_SERVER_NAME		"kujo.cs.pitt.edu"

// Map Coordinate Limits
#define MAP_MAX_X                       7
#define MAP_MAX_Y                       5

// Map Types
#define MAP_OBJ_EMPTY                   0x00
#define MAP_OBJ_ROBOT_1                 0x01
#define MAP_OBJ_ROBOT_2                 0x02
#define MAP_OBJ_PELLET                  0x03
#define MAP_OBJ_POST                    0x04
#define MAP_OBJ_RESERVE_1               0x05
#define MAP_OBJ_RESERVE_2               0x06

/** @brief Map object structure*/
typedef struct MapObj MapObjType;
struct MapObj {
    int x;
    int y;
    int type;
    int points;
    MapObjType *next;
};

// API Decoder
#define MAP_OBJ_TYPE(t)                 ((t & 0xF0) >> 4)
#define MAP_OBJ_SCORE(s)                (s & 0xF)
#define MAP_OBJ_ENC(t,s)                (((t & 0x0F) << 4) | (s & 0xF))

// Error codes
#define SERR_NONE                       (0)
#define SERR_INVALID_MOVE               (-1)
#define SERR_INVALID_COORD              (-2)
#define SERR_INVALID_ROBOT              (-3)

// ******************************************************************
// * Robot user interface
// ******************************************************************

#define MAX_ADDR_LEN			128
typedef struct RobotIf {
    char address[MAX_ADDR_LEN];
    char gs_address[MAX_ADDR_LEN];
    int sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in game_server_addr;

    // Robot number
    int id;

    // Current robot encoder counts
    unsigned long long right_wheel_enc;
    unsigned long long left_wheel_enc;
    unsigned long long rear_wheel_enc;

    // Report caches, remember to update before calling any of the getters
    RIReport report;
    RIData sensor;
} RobotIfType;



/**
 * @class RobotInterface
 * @brief The class RobotInterface provides the robot interface and many functions
 *
 * The class RobotInerface provides the robot interface and function, such as:the control of the robot moving and rocker arm;infrared detect  
 * obstacles, image acquisition, image save, update the data and so on.
 */
class RobotInterface {
	private:
        RobotIfType  ri;           ///<This holds the robot interface code
	public:
        /**
         *@brief RobotInterface() Create a new instance of the RobotInterface class to initialize the robot interface instance.
         */
          RobotInterface(const char *address, int robot_id);
        /**
          *@brief A destructor.
          */
         ~RobotInterface();

      /**
       *@brief Robot API Version
       */
       void APIVersion(int* major, int* minor);


      /**
        * @brief Robot Movement, move the robot or its' arm.
        */
        int move(int movement, int speed);
        /**
         * @brief Robot Movement, goHome.
         */
        int goHome(void);
        /**
         * @brief Robot Movement, get wheel's direction.
         */
        int getWheelDirection(int wheel);
        /**
         * @brief Robot Movement, get  wheel's encoder.
         */
        int getWheelEncoder(int wheel);
        /**
         * @brief Robot Movement, get wheel's encoder totally.
         */
        int getWheelEncoderTotals(int wheel);
        /**
         * @brief Robot Movement, get robot's headposition.
         */
        int getHeadPosition(void);
		
        /**
         * @brief IR, IR detector.
         */
         bool IRDetected(void);
        /**
         * @brief IR, enable/disable the IR.
         */
        int IR(int status);
        /**
         * @brief store the status of IR detector's .
         */
        int IRStatus(void);

          /**
         * @brief Headlight,turn on the headlight.
         */
        int Headlight(int status);

        /**
         * @brief North Star Report, returns the X coordinate of the robot from the North Star system.
         */
		int X(void);
        /**
         * @brief North Star Report, returns the Y coordinate of the robot from the North Star system.
         */
		int Y(void);
        /**
         * @brief North Star Report, returns the direction of the robot from the North Star system.
         */
		float Theta(void);
        /**
         * @brief North Star Report, returns the signal strength of the North Star system indicated by the RoomID.
         */
		int NavStrength(void);
        /**
         * @brief North Star Report, returns the signal strength of the North Star system indicated by the RoomID.
         */
		int NavStrengthRaw(void);
        /**
         * @brief North Star Report, returns the battery life.
         */
		int Battery(void);
        /**
         * @brief North Star Report, returns the wifi strength.
         */
		int WifiStrengthRaw(void);
        /**
         * @brief RoomID, returns the beacon ID of the North Star system with the strongest signal.
         */
		int RoomID(void);

        /**
         * @brief Image, captures an image from the camera.
         */
        int getImage(IplImage *image);
        /**
         * @brief Image, save an image from the camera.
         */
        int saveImage(IplImage *image);
        /**
         * @brief Image, takes a 1 plane image and returns a list of the squares in an image.
         */
        SquaresType *findSquares(IplImage *image, int threshold);
        /**
         * @brief Image, configures the camera for use.
         */
        int cameraConfigure(int brightness, int contrast, int framerate, int resolution, int quality);
        /**
         * @brief Image, configures the volume for use.
         */
        int volumeConfigure(int mic_volume, int speaker_volume);

        /**
         * @brief Reports, get sensors' data.
         */
        RIData *getSensors(void);
        /**
         * @brief Reports, get reports.
         */
        RIReport *getReport(void);
        /**
         * @brief Reports, update the sensor and report data.
         */
        int update(void);
        /**
         * @brief Report, Reset the cached data.
         */
        void resetState(void);

        /**
         * @brief Game API, updates the robot's location on the map.
         */
		int updateMap(int x, int y);
        /**
         * @brief Game API, reserves the robot's location on the map.
         */
          int reserveMap(int x, int y);
          /**
           * @brief Game API, get the current map from the server.
           */
         MapObjType* getMap(int *score1, int* score2);
         };

#endif    /*ROBOT_DRIVER_CPP_H*/
