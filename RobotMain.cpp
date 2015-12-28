/******************************************************************************
 * 
 * 	Sprockets 2014
 * 	Authors: 	William Surmak
 * 	Last Updated:	07/01/2014
 * 
 ******************************************************************************/


// Include our own header file with our own macros
#include "New Robot.h"


// Our main and only class. You could consider this an alteration of "int main(void)" if it makes it easier.
class SimpleTracker : public SimpleRobot
{
    // Local variables
    DRIVEMOTOR *flMotor; // Left-front drive motor
    DRIVEMOTOR *frMotor; // Left-rear drive motor
    DRIVEMOTOR *rlMotor; // Right-front drive motor
    DRIVEMOTOR *rrMotor; // Right-rear drive motor
    Talon *pickup1;
    Talon *pickup2;
    Talon *shooterMotorOne;
    Talon *shooterMotorTwo;
    Joystick *rightStick; // Right joystick
    Joystick *leftStick; // Left joystick
    HSLImage *cameraImage; // Hue/Saturation/Luminence image from camera
    BinaryImage *binaryImage; // The object used to store and edit the filtered image
    Image *imaqImage; // Stores the image in a format that the built-in imaq functions can use
    double maxTargetWidth; // Width of clearest target in view
    double maxTargetHeight; // Height of clearest target in view
    Counter *frEncoder;
    Counter *flEncoder;
    Counter *rrEncoder;
    Counter *rlEncoder;
    DigitalInput *shooterSwitch;
    DigitalInput *downSwitch;
    Gyro *gyro;
    Talon* spinner;
    Relay *led;

    /* "Constructor". This code is run when the robot is first turned on. */
    public:
	SimpleTracker(void)
	{	
		// Joysticks
		rightStick = new Joystick(RIGHTJOYSTICKPORT); // Right-joystick
		leftStick = new Joystick(LEFTJOYSTICKPORT); // Left-joystick
		
		// Motors
		rlMotor = new DRIVEMOTOR(RLMOTORPORT); // Left-front drive motor
		rrMotor = new DRIVEMOTOR(RRMOTORPORT); // Left-rear drive motor
		flMotor = new DRIVEMOTOR(FLMOTORPORT); // Right-front drive motor
		frMotor = new DRIVEMOTOR(FRMOTORPORT); // Right-rear drive motor
		pickup1 = new Talon(PICKUPMOTOR1);
		pickup2 = new Talon(PICKUPMOTOR2);
		spinner = new Talon(PICKUPMOTOR3);
		
		rrEncoder = new Counter(RRENCODERPORTA);
		rlEncoder = new Counter(RLENCODERPORTA);
		frEncoder = new Counter(FRENCODERPORTB);
		flEncoder = new Counter(FLENCODERPORTB);
		
		led = new Relay(LEDPORT);
		
		gyro = new Gyro(GYROPORT);
		
		shooterSwitch = new DigitalInput(TESTSWITCHPORT);
		downSwitch = new DigitalInput(DOWNSWITCHPORT);
		
		shooterMotorOne = new Talon(SHOOTERPORTONE);
		shooterMotorTwo = new Talon(SHOOTERPORTTWO);
		
	    AxisCamera &camera = AxisCamera::GetInstance();
	    
	    // Set the camera's preferences
	    camera.WriteResolution(camera.kResolution_320x240); // Make sure this resolution matches the width and height macros
	    camera.WriteCompression(0);
	    camera.WriteBrightness(50);
	    camera.WriteColorLevel(256);
	    
	    rrEncoder->Start();
	    rlEncoder->Start();
	    frEncoder->Start();
	    flEncoder->Start();
	    gyro->Reset();
	    gyro->SetSensitivity(0.08);
	}
	
	
    /* Code to run while in tele-op, or driver-controlled  mode. */
	void OperatorControl(void)
	{
		float direction, magnitude, rotation; // Y-positions of left and right joysticks
		float leftX, leftY;
		double  rrWheelSpeed = 0.5, rlWheelSpeed = 0.5, frWheelSpeed = 0.5, flWheelSpeed = 0.5;
		double  rlMultiplier = 1, rrMultiplier = 1, frMultiplier = 1, flMultiplier = 1;
		float frontGyroAngle, gyroAngle, frontCorrection;
		
//	    rrEncoder->Start();
//	    rlEncoder->Start();
//	    frEncoder->Start();
//	    flEncoder->Start();

		
		while(IsOperatorControl())
		{
			// Teleop code
			GetWatchdog().Feed();
			
			
//			DISPLAYPRINTF(1, "Angle %0.3f", direction);
//			DISPLAYPRINTF(5, "multi %0.3f", rrMultiplier);
//			DISPLAYPRINTF(3, "Rotation %0.3f", rotation);
//			DISPLAYPRINTF(4, "time %d", shooterPause);
//			DISPLAYPRINTF(5, "Right %0.3f", magnitude);
//			DISPLAYPRINTF(6, "time %0.3f", time);
			
			
//			DISPLAYPRINTF(1, "RR %0.3f", rrMultiplier);
//			DISPLAYPRINTF(2, "RL %0.3f", rlMultiplier);
//			DISPLAYPRINTF(3, "FL %0.3f", flMultiplier);
//			DISPLAYPRINTF(4, "FR %0.3f", frMultiplier);
//			DISPLAYPRINTF(5, "RRC %0.3f", rrWheelSpeed);
			
//			DISPLAYPRINTF(1, "FL %d", flEncoderValue);
//			DISPLAYPRINTF(2, "FR %d", frEncoderValue);
//			DISPLAYPRINTF(3, "RL %d", rlEncoderValue);
//			DISPLAYPRINTF(4, "RR %d", rrEncoderValue);
			DISPLAYPRINTF(6, "gyroD %0.3f", gyroAngle);
			
			led->Set(Relay::kForward);
			
//			DISPLAYPRINTF(1, "rrRPM %f", rrMotor->Get());
//			DISPLAYPRINTF(2, "rlRPM %f", rlMotor->Get());
//			DISPLAYPRINTF(3, "flRPM %f", flMotor->Get());
//			DISPLAYPRINTF(5, "frRPM %f", frMotor->Get());
//			DISPLAYPRINTF(6, "angle %f", gyroAngle);

			CLEARMESSAGE;
			
			leftY = leftStick->GetRawAxis(2);
			leftX = leftStick->GetRawAxis(1);
			rotation = rightStick->GetRawAxis(2);
			
//			frEncoderValue = frEncoder->Get();
//			flEncoderValue = flEncoder->Get();
//			rrEncoderValue = rrEncoder->Get();
//			rlEncoderValue = rlEncoder->Get();
		
			// Get our gyro angle and correct it
			gyroAngle = gyro->GetAngle();
			gyroAngle *= 12.85;
			
			// convert to radians
			frontGyroAngle = (gyroAngle / 180) * Pi;
			frontCorrection = frontGyroAngle;
			
			// If there is no enough movment on the joystick disregard the command
			if(leftY < JOYSTICKDEADBAND && leftY > -JOYSTICKDEADBAND)leftY = 0;
			if(leftX < JOYSTICKDEADBAND && leftX > -JOYSTICKDEADBAND)leftX = 0;
			if(rotation < JOYSTICKDEADBAND && rotation > -JOYSTICKDEADBAND) rotation = 0;
			
			// calculate the magnitude, direction, and rotation
     			magnitude = sqrt((leftY * leftY) + (leftX * leftX));
			direction = leftStick->GetDirectionRadians();
			rotation = rightStick->GetRawAxis(1);
			
			// if we are trying to just go forward use front correction to ensure a straight line
			if(sqrt(rotation *rotation) < 0.1)
			{
				frontCorrection = sin(frontGyroAngle);
			}
			// otherwise allow the robot to torate freely
			else
			{
				frontCorrection = 0;
				gyro->Reset();
			}
			
			//set the wheel speeds
			flWheelSpeed = (magnitude * sin(direction - (Pi /4)) + rotation) - frontCorrection;
			frWheelSpeed = (magnitude * cos(direction - (Pi /4)) + rotation)- frontCorrection;
			rlWheelSpeed = (magnitude * -cos(direction - (Pi /4)) + rotation)- frontCorrection;
			rrWheelSpeed = (magnitude * -sin(direction - (Pi /4)) + rotation)- frontCorrection;
			
			//ensure we never go over 100% power
			if(flWheelSpeed > 1) flWheelSpeed = 1;
			if(frWheelSpeed > 1) frWheelSpeed = 1;
			if(rrWheelSpeed > 1) rrWheelSpeed = 1;
			if(rlWheelSpeed > 1) rlWheelSpeed = 1;
     		
//			flMotor->Set((flWheelSpeed * flMultiplier) *-1); //rr
//			frMotor->Set(frWheelSpeed * frMultiplier); //rl
//			rlMotor->Set((rlWheelSpeed * rlMultiplier) *-1);// fr
//			rrMotor->Set(rrWheelSpeed * rrMultiplier);
			
//			flMotor->Set((rightStick->GetRawAxis(2)));
//			rrMotor->Set((leftStick->GetRawAxis(2)));
//			frMotor->Set((leftStick->GetRawAxis(2)));
//			rlMotor->Set((rightStick->GetRawAxis(2)));
			
			//set the wheel speed
			flMotor->Set(flWheelSpeed * flMultiplier);
			frMotor->Set(frWheelSpeed * frMultiplier);
			rlMotor->Set(rlWheelSpeed * rlMultiplier);
			rrMotor->Set(rrWheelSpeed * rrMultiplier);
			
			//shooter
			if(shooterSwitch->Get())
			{
				shooterMotorOne->Set(-0.3f);
				shooterMotorTwo->Set(-0.3f);
			}
			else if(SHOOTBUTTON && !downSwitch->Get())
			{
				shooterMotorOne->Set(1.0f);
				shooterMotorTwo->Set(1.0f);
			}
			else if(STICKYBUTTON)
			{
				shooterMotorOne->Set(-0.3f);
				shooterMotorTwo->Set(-0.3f);
			}
			else
			{
				shooterMotorOne->Set(0.0f);
				shooterMotorTwo->Set(0.0f);
			}
			
			//rollers
			if(SPINNERBUTTON)
			{
				spinner->Set(1.0f);
			}
			else if(KENBUTTON)
			{
				spinner->Set(-1.0f);
			}
			else spinner->Set(0.0f);
			
			
			//pickup
		    if(PICKUPBUTTON)
			{
				pickup1->Set(1.0f);
				pickup2->Set(1.0f);
			}
			else if(PICKDOWNBUTTON && downSwitch->Get())
			{
				pickup2->Set(-1.0f);
				pickup1->Set(-1.0f);
			}
			else
			{
				pickup2->Set(0.0f);
				pickup1->Set(0.0f);
			}
		}
	} // End of teleop
	
	/* Code to run while in autonomous, or fully-automated mode. */
	void Autonomous(void)
	{
		int distinctParticless = 0;
		int moveFlag = 0;
		int moveCycles = 0;
		double gyroAngle, frontCorrection;
		double rlWheelSpeed, rrWheelSpeed, frWheelSpeed, flWheelSpeed;
		double magnitude = 0.8;
		double direction = 0;
		double rotation = 0;
		double frontGyroAngle;
		int particleFlag = 0;
		int shootFlag = 0;
		int move1 = 0, move2 = 0;
		
		while(IsAutonomous())
		{
			// Autonomous code
			GetWatchdog().Feed();
			DISPLAYPRINTF(3, "particles %d", distinctParticless);
			DISPLAYPRINTF(6, "count %d", moveCycles);
			
			CLEARMESSAGE;
			AxisCamera &camera = AxisCamera::GetInstance();
			
			// If we don't have a target, look for one while moving forward
			if(shootFlag == 0) 
			{
				distinctParticless = GetProcessedImage(camera);
				if(move1 == 0) 
				{
					moveCycles = 50;
					move1 = 1;
				}
			}
			
			//If we found the target move a little closer and prepare to shoot
			if(distinctParticless >= 2 && shootFlag == 0)
			{
				shootFlag = 1;
				if(move2 == 0)
				{
					moveCycles = 10000;
					move2 = 1;
				}
			}
			
			gyroAngle = gyro->GetAngle();
			gyroAngle *= 12.85;
			
			// after moving shoot the ball
			if(shootFlag == 1 && moveCycles < 1 && particleFlag == 0)
			{
				shooterMotorOne->Set(0.3f);
				shooterMotorTwo->Set(0.3f);
				
				rrMotor->Set(0.0f);
				rlMotor->Set(0.0f);
				frMotor->Set(0.0f);
				flMotor->Set(0.0f);
			}
			
			// Rewind the shooter after the shot
			if(shooterSwitch->Get() || particleFlag == 1)
			{
				shooterMotorOne->Set(0.0f);
				shooterMotorTwo->Set(0.0f);
				particleFlag = 1;

			}
			
			// drive forward if needed
			if(moveCycles > 0)
			{
				
				frontGyroAngle = (gyroAngle / 180) * Pi;
				frontCorrection = frontGyroAngle;
				frontCorrection = sin(frontGyroAngle);
				
				flWheelSpeed = (magnitude * sin(direction - (Pi /4)) + rotation) - frontCorrection;
				frWheelSpeed = (magnitude * cos(direction - (Pi /4)) + rotation)- frontCorrection;
				rlWheelSpeed = (magnitude * -cos(direction - (Pi /4)) + rotation)- frontCorrection;
				rrWheelSpeed = (magnitude * -sin(direction - (Pi /4)) + rotation)- frontCorrection;
				
				frMotor->Set(frWheelSpeed);
				flMotor->Set(flWheelSpeed);
				rrMotor->Set(rrWheelSpeed);
				rlMotor->Set(rlWheelSpeed);
				
				moveCycles--;
			}
			
			// once we are done moving stop
			if(moveCycles <= 1)
			{
				frMotor->Set(0.0f);
				flMotor->Set(0.0f);
				rrMotor->Set(0.0f);
				rlMotor->Set(0.0f);
				
			}
			
			//pickup1->Set(1.0f);
			//pickup2->Set(1.0f);
		}
	} // End of Autonomous
	
	 /* Take the camera image and pro  cess it, returning the x-position of the largest particle. This should represent the
	horizontal centre of the most in-focus target. Comparing this value to the image width (320) should allow us to
	centre the image by rotating the robot. If the targets are out of view, -1 is returned. */ 
	int GetProcessedImage(AxisCamera &camera)
	{
		register int i;
		int numberOfParticles, distinctParticles = 0;
		double width, height; //250
		double rainbow, maxrainbow = 500, minrainbow = 10;
		
		// Save the image as a BinaryImage Object
		cameraImage = camera.GetImage();
		//binaryImage = cameraImage->ThresholdHSL(HUEMIN, HUEMAX, SATURATIONMIN, SATURATIONMAX, LUMINANCEMIN, LUMINANCEMAX);
		binaryImage = cameraImage->ThresholdRGB(REDMIN, REDMAX, GREENMIN, GREENMAX, BLUEMIN, BLUEMAX);

		imaqImage = binaryImage->GetImaqImage();
		
		// Perform the Convex Hull operation
		imaqConvexHull(imaqImage, imaqImage, 1);
		
		// Count the number of distinct sections remaining
		imaqCountParticles(imaqImage, 2, &numberOfParticles);
			    
	    // Save image to the cRIO's memory (enable for debugging purposes only)
	    //cameraImage->Write("camIm4.jpeg");
	    //binaryImage->Write("binIm4.bmp");
	
	    // For each particle found
	    for(i = 0; i < numberOfParticles; i++)
	    {
	    	// Get the width and height of the given particle
	    	imaqMeasureParticle(imaqImage, i, 0, IMAQ_MT_BOUNDING_RECT_WIDTH, &width);
	    	imaqMeasureParticle(imaqImage, i, 0, IMAQ_MT_BOUNDING_RECT_HEIGHT, &height);
	    	rainbow = width * height;
	    	
	    	if(rainbow > minrainbow && rainbow  < maxrainbow)
	    	{
	    		distinctParticles++;
	    	}

	    }
	    // Find the x-position of the centre of the largest particle, assumed to be the nearest target
	   // DISPLAYPRINTF(2, "particles %d", distinctParticles);
	    
	    delete binaryImage;
	    delete cameraImage;
	    return distinctParticles;  
	}
	
};

/* The entry point is FRC_UserProgram_StartupLibraryInit. Tell the linker where our code is. */
START_ROBOT_CLASS(SimpleTracker);
