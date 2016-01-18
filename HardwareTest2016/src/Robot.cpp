#include "WPILib.h"

const int CANID_DRIVE_TRAIN_FRONT_LEFT  = 1;
const int CANID_DRIVE_TRAIN_FRONT_RIGHT = 2;
const int CANID_DRIVE_TRAIN_REAR_LEFT   = 3;
const int CANID_DRIVE_TRAIN_REAR_RIGHT  = 4;

const int PCMCHANNEL_SOME_MOTOR = 0;

const int PORTID_JOYSTICK_1 = 5;

class Robot: public IterativeRobot
{
	SpeedController* driveTrainFrontLeft;
	SpeedController* driveTrainFrontRight;
	SpeedController* driveTrainRearLeft;
	SpeedController* driveTrainRearRight;
	SpeedController* someMotor;
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	LiveWindow *lw;
	int autoLoopCounter;

public:
	Robot() :
		// These must be initialized in the same order as they are declared above.
		driveTrainFrontLeft(new CANTalon(CANID_DRIVE_TRAIN_FRONT_LEFT)),
		driveTrainFrontRight(new CANTalon(CANID_DRIVE_TRAIN_FRONT_RIGHT)),
		driveTrainRearLeft(new CANTalon(CANID_DRIVE_TRAIN_REAR_LEFT)),
		driveTrainRearRight(new CANTalon(CANID_DRIVE_TRAIN_REAR_RIGHT)),
		someMotor(new Victor(PCMCHANNEL_SOME_MOTOR)),
		myRobot(driveTrainFrontLeft, driveTrainFrontRight),
		stick(PORTID_JOYSTICK_1),
		lw(LiveWindow::GetInstance()),
		autoLoopCounter(0)
	{
		printf("Robot ctor ENTER\n");
		myRobot.SetExpiration(0.1);
		printf("Robot ctor EXIT\n");
	}

private:
	void AutonomousInit()
	{
		printf("Robot::AutonomousInit\n");
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic()
	{
		if(autoLoopCounter < 100) //Check if we've completed 100 loops (approximately 2 seconds)
		{
			myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			autoLoopCounter++;
			} else {
			myRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	void DisabledInit()
	{
		printf("Robot::DisabledInit\n");
	}

	void DisabledPeriodic()
	{
		//printf("Robot::DisabledPeriodic\n");
	}

	void RobotInit()
	{
		printf("Robot::RobotInit ENTER\n");
		lw = LiveWindow::GetInstance();
		printf("Robot::RobotInit EXIT\n");
	}

	void TeleopInit()
	{
		printf("Robot::TeleopInit\n");
	}

	void TeleopPeriodic()
	{
		myRobot.ArcadeDrive(stick); // Arcade-style driving
	}

	void TestInit()
	{
		printf("Robot::TestInit\n");
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
