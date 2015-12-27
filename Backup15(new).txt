// This file contains all macros and preprocessor directives

// Header files
// Header file for WPI standard hardware/robot overhead.
#include "WPILib.h"

// Header file for math functions
#include <math.h>

// Include the libraries for the camera
#include "vision/AxisCamera.h"

// Header file for time functions
#include <time.h>

// Macro Functions
// Clears the Driver Station output display
#define CLEARMESSAGE DriverStationLCD::GetInstance()->Clear()

// Provides full free-form formatting, as per the usual printf(). Displays formatted text, a, on Driver Station on line, b.
#define DISPLAYPRINTF(b, a, ...) {DriverStationLCD::GetInstance()->Printf(DriverStationLCD::kUser_Line ## b, 1, a, ## __VA_ARGS__); DriverStationLCD::GetInstance()->UpdateLCD();}

#define CAMERATARGETBUTTON leftStick->GetRawButton(5)
#define SHOOTBUTTON leftStick->GetRawButton(1)
#define PICKUPBUTTON leftStick->GetRawButton(3)
#define PICKDOWNBUTTON leftStick->GetRawButton(2)
#define SPINNERBUTTON leftStick->GetRawButton(4)
#define KENBUTTON leftStick->GetRawButton(5)
#define STICKYBUTTON rightStick->GetRawButton(11)


// Macros
// Object type macros
#define DRIVEMOTOR Talon // Change to type of PWM controller being used for drive motors

// Port number macros
// Motors
#define RLMOTORPORT 1 //4 Port number for the left front motor
#define RRMOTORPORT 4 //1 Port number for the left rear motor
#define FLMOTORPORT 2 //2 Port number for the right front motor
#define FRMOTORPORT 3 //3 Port number for the right rear motor
#define PICKUPMOTOR1 7
#define PICKUPMOTOR2 8
#define PICKUPMOTOR3 9

#define TESTSWITCHPORT 14
#define DOWNSWITCHPORT 13

#define SHOOTERPORTONE 5
#define SHOOTERPORTTWO 6

#define LEDPORT 2

#define RLENCODERPORTA 9
#define RLENCODERPORTB 8
#define RRENCODERPORTA 13
#define RRENCODERPORTB 12
#define FLENCODERPORTA 7
#define FLENCODERPORTB 6
#define FRENCODERPORTA 11
#define FRENCODERPORTB 10

#define GYROPORT 1
#define ARMGYROPORT 2

// Joysticks
#define RIGHTJOYSTICKPORT 1 // Port number for the right jostick
#define LEFTJOYSTICKPORT 2 // Port number for the left joystick

//Camera macros
#define HUEMAX 255
#define HUEMIN 0
#define SATURATIONMAX 15
#define SATURATIONMIN 0
#define LUMINANCEMAX 255
#define LUMINANCEMIN 20 // 160
#define REDMIN 0
#define REDMAX 50
#define BLUEMIN 0
#define BLUEMAX 255
#define GREENMIN 230
#define GREENMAX 255
#define MINIMUMAREA 10
#define GOALWIDTH 2.0
#define CAMERAFREQUENCY 3000 // The number of times the IsOperatorControl() or IsAutonomous() loops must run before updating the camera image
#define HALFCAMERAVIEWINGANGLE 23.5 // Half of the viewing angle of the camera
#define LINEARDISTANCEK 1.0 // The camera distance is multiplied by this constant
#define CONSTANTDISTANCEK 0.0 // The camera distance has this added to it
#define IMAGEWIDTH 320.0 // The width of the image from the camera
#define IMAGEHEIGHT 240.0 // The height of the image from the camera
#define MIN_RECT_LENGTH 30
#define MAX_RECT_LENGTH 190
#define MAX_RECT_HEIGHT 180
#define MIN_RECT_HEIGHT 30

#define JOYSTICKDEADBAND 0.2
#define ENCODERDEADBAND 150
#define Pi 3.1415926535897932384626433832795028841971f
