#include "WPILib.h"

const int CANID_DRIVE_TRAIN_FRONT_LEFT  = 1;
const int CANID_DRIVE_TRAIN_FRONT_RIGHT = 2;
const int CANID_DRIVE_TRAIN_REAR_LEFT   = 3;
const int CANID_DRIVE_TRAIN_REAR_RIGHT  = 4;

const int PCMCHANNEL_SOME_MOTOR_0 = 0;
const int PCMCHANNEL_SOME_MOTOR_1 = 1;
const int PCMCHANNEL_SOME_MOTOR_2 = 2;
const int PCMCHANNEL_SOME_MOTOR_3 = 3;
const int PCMCHANNEL_SOME_MOTOR_4 = 4;
const int PCMCHANNEL_SOME_MOTOR_5 = 5;
const int PCMCHANNEL_SOME_MOTOR_6 = 6;
const int PCMCHANNEL_SOME_MOTOR_7 = 7;
const int PCMCHANNEL_SOME_MOTOR_8 = 8;
const int PCMCHANNEL_SOME_MOTOR_9 = 9;

const int PORTID_JOYSTICK_1 = 0;

class Robot: public IterativeRobot
{
	SpeedController* driveTrainFrontLeft;
	SpeedController* driveTrainFrontRight;
	SpeedController* driveTrainRearLeft;
	SpeedController* driveTrainRearRight;
	SpeedController* someMotor0;
	SpeedController* someMotor1;
	SpeedController* someMotor2;
	SpeedController* someMotor3;
	SpeedController* someMotor4;
	SpeedController* someMotor5;
	SpeedController* someMotor6;
	SpeedController* someMotor7;
	SpeedController* someMotor8;
	SpeedController* someMotor9;
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
		someMotor0(new Victor(PCMCHANNEL_SOME_MOTOR_0)),
		someMotor1(new Victor(PCMCHANNEL_SOME_MOTOR_1)),
		someMotor2(new Victor(PCMCHANNEL_SOME_MOTOR_2)),
		someMotor3(new Victor(PCMCHANNEL_SOME_MOTOR_3)),
		someMotor4(new Victor(PCMCHANNEL_SOME_MOTOR_4)),
		someMotor5(new Victor(PCMCHANNEL_SOME_MOTOR_5)),
		someMotor6(new Victor(PCMCHANNEL_SOME_MOTOR_6)),
		someMotor7(new Victor(PCMCHANNEL_SOME_MOTOR_7)),
		someMotor8(new Victor(PCMCHANNEL_SOME_MOTOR_8)),
		someMotor9(new Victor(PCMCHANNEL_SOME_MOTOR_9)),
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
