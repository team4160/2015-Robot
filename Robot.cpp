#include "WPILib.h"

class Robot: public SampleRobot
{
Talon leftDrive;
Talon rightDrive;
CANTalon middleDrive;
Victor middleDrive2;
Victor lift;
Victor lift2;
Encoder encoder;
Joystick controller;
bool XButton = 0;
bool SquareButton = 0;
bool CircleButton = 0;
bool TriangleButton = 0;
bool OptionsButton = 0;

public:
	Robot() :
		leftDrive(0),
		rightDrive(1),
		middleDrive(0),
		middleDrive2(2),
		lift(3),
		lift2(4),
		encoder(7, 8, false, Encoder::k4X),
		controller(0)

	{
		// Defines the number of samples to average when determining the rate.
				// On a quadrature encoder, values range from 1-255; larger values
				//   result in smoother but potentially less accurate rates than lower values.
				encoder.SetSamplesToAverage(5);

				// Defines how far the mechanism attached to the encoder moves per pulse.
				// In this case, we assume that a 360 count encoder is directly attached
				//   to a 3 inch diameter (1.5inch radius) wheel, and that we want to
				//   measure distance in inches.
				encoder.SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 1.5);

				// Defines the lowest rate at which the encoder will not be considered
				//   stopped, for the purposes of the GetStopped() method.
				// Units are in distance / second, where distance refers to the units
				//   of distance that you are using, in this case inches.
				encoder.SetMinRate(1.0);
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			leftDrive.Set((controller.GetRawAxis(5))); // Two left wheels which are chained together spin
																		// proportionally to the value of the Left Analog Stick Y Axis.
																	// Positive 1 means full speed forward, Negative 1 means full speed backwards. [.5 is 50% speed.]
																		// Note: motors are also backwards so the value is multiplied by a negative
																		// to spin in the correct direction

			rightDrive.Set(controller.GetRawAxis(1) * -1);				// Two right wheels which are chained together spin
																		// proportionally to the value of the Right Analog Stick Y Axis.

						if ((controller.GetRawAxis(4) > -1) && (controller.GetRawAxis(3) == -1)) {	// If Right Trigger is pressed and the Left Trigger isn't,
							middleDrive.Set((controller.GetRawAxis(4) + 1) /2);				// Spin the middle wheels which are on the same shaft proportional to how
							middleDrive2.Set((controller.GetRawAxis(4) + 1) /2);			// much the trigger is pressed.

																						// Note: trigger un-pressed has a value of -1, pressed it is +1.
																						// Mathematical process of +1, then divide by 2 maps out these values so that
																						// un-pressed will have the value 0, while pressed makes the value 1.
						}
						else if ((controller.GetRawAxis(3) > -1) && (controller.GetRawAxis(4) == -1)) {	// If Left Trigger is pressed and the Right Trigger isn't,
							middleDrive.Set(((controller.GetRawAxis(3) + 1) /2) * -1);
							middleDrive2.Set(((controller.GetRawAxis(3) + 1) /2) * -1);		// Spin the middle wheels which are on the same shaft proportional to how
																							// much the trigger is pressed.
						}
						else {														// All other possibilities make it so that the wheels will not move.
							middleDrive.Set(0);
							middleDrive2.Set(0);										// E.G. Both triggers are pressed, the wheels will not spin.
						}


						// BOOL VALUES SET HERE



						if ((controller.GetRawButton(2) == 1) && (controller.GetRawButton(1) == 0)					// X button is pressed, everything else isn't
								&& (controller.GetRawButton(3) == 0) && (controller.GetRawButton(4) == 0)
								&& (controller.GetRawButton(10) == 0)){
							XButton = 1;																					// Boolean 1 is set to true
														SquareButton = 0;														// Everything else isn't
														CircleButton = 0;
														TriangleButton = 0;
														OptionsButton = 0;
						}
						else if ((controller.GetRawButton(2) == 0) && (controller.GetRawButton(1) == 1)				// Square button is pressed, everything else isn't
								&& (controller.GetRawButton(3) == 0) && (controller.GetRawButton(4) == 0)
								&& (controller.GetRawButton(10) == 0)){
														XButton = 0;
							SquareButton = 1;																					// Boolean 2 is set to true
														CircleButton = 0;														// Everything else isn't
														TriangleButton = 0;
														OptionsButton = 0;
						}
						else if ((controller.GetRawButton(2) == 0) && (controller.GetRawButton(1) == 0)				// Circle button is pressed, everything else isn't
								&& (controller.GetRawButton(3) == 1) && (controller.GetRawButton(4) == 0)
								&& (controller.GetRawButton(10) == 0)){
														XButton = 0;
														SquareButton = 0;
							CircleButton = 1;																					// Boolean 3 is set to true
														TriangleButton = 0;														// Everything else isn't
														OptionsButton = 0;
						}
						else if ((controller.GetRawButton(2) == 0) && (controller.GetRawButton(1) == 0)				// Triangle button is pressed, everything else isn't
								&& (controller.GetRawButton(3) == 0) && (controller.GetRawButton(4) == 1)
								&& (controller.GetRawButton(10) == 0)){
														XButton = 0;
														SquareButton = 0;
														CircleButton = 0;
							TriangleButton = 1;																					// Boolean 4 is set to true
														OptionsButton = 0;														// Everything else isn't
						}
						else if ((controller.GetRawButton(2) == 0) && (controller.GetRawButton(1) == 0)				// Options button is pressed, everything else isn't
								&& (controller.GetRawButton(3) == 0) && (controller.GetRawButton(4) == 0)
								&& (controller.GetRawButton(10) == 1)){
														XButton = 0;
														SquareButton = 0;
														CircleButton = 0;
														TriangleButton = 0;
							OptionsButton = 1;																					// Boolean 5 is set to true
						}																							// Everything else isn't
						else if ((controller.GetRawButton(2) == 0) && (controller.GetRawButton(1) == 0)
								&& (controller.GetRawButton(3) == 0) && (controller.GetRawButton(4) == 0)			// No buttons are pressed
								&& (controller.GetRawButton(10) == 0)){
						}																							// Don't mess with the current Booleans
						else {
							XButton = 0;
							SquareButton = 0;
							CircleButton = 0;																					// More than one button is pressed
							TriangleButton = 0;																					// Set all Booleans to false
							OptionsButton = 0;
						}


						// STAGES OF LIFTS

						if (XButton == 1){												// Boolean 1 is true,
							if (encoder.GetDistance() >= 2){							// Bring Lift Motors to stage 1
								lift.Set(-1);
								lift2.Set(-1);
							}
							else {														// Lift Motors are at correct height
								lift.Set(0);
								lift2.Set(0);
								XButton = 0;											// Kill Boolean 1
							}
						}
						else if (SquareButton == 1) {									// Boolean 2 is true,
							if (encoder.GetDistance() <= 10){							// Bring Lift Motors to stage 2
								lift.Set(1);
								lift2.Set(1);
							}
							else if (encoder.GetDistance() >= 14){
								lift.Set(-1);
								lift2.Set(-1);
							}
							else{														// Lift Motors are at correct height
								lift.Set(0);
								lift2.Set(0);
								SquareButton = 0;										// Kill Boolean 2
							}
						}
						else if (CircleButton == 1) {									// Boolean 3 is true,
							if (encoder.GetDistance() <= 24){							// Bring Lift Motors to stage 3
								lift.Set(1);
								lift2.Set(1);
							}
							else if (encoder.GetDistance() >= 28){
								lift.Set(-1);
								lift2.Set(-1);
							}
							else{														// Lift Motors are at correct height
								lift.Set(0);
								lift2.Set(0);
								CircleButton = 0;										// Kill Boolean 3
							}
						}
						else if (TriangleButton == 1) {									// Boolean 4 is true,
							if (encoder.GetDistance() <= 40){							// Bring Lift Motors to stage 4
								lift.Set(1);
								lift2.Set(1);
							}
							else if (encoder.GetDistance() >= 44){
								lift.Set(-1);
								lift2.Set(-1);
							}
							else{														// Lift Motors are at correct height
								lift.Set(0);
								lift2.Set(0);
								TriangleButton = 0;										// Kill Boolean 4
							}
						}
						else if (OptionsButton == 1) {									// Boolean 5 is true,
							if (encoder.GetDistance() <= 55){							// Bring Lift Motors to stage 5
								lift.Set(1);
								lift2.Set(1);
							}
							else{														// Lift Motors are at correct height
								lift.Set(0);
								lift2.Set(0);
								OptionsButton = 0;										// Kill Boolean 5
							}
						}
						else{															// No Booleans are set
							lift.Set(0);												// Do nothing
							lift2.Set(0);
						}
																									// Inputs the values of the analog sticks, buttons
						if (controller.GetRawButton(5) == true){
							lift.Set(.5);
							lift.Set(.5);}
						if (controller.GetRawButton(6) == true){
							lift.Set(-.5);
							lift.Set(-.5);}

						SmartDashboard::PutNumber("Right Y Axis(1)", controller.GetRawAxis(1));		// and the triggers into the Smart Dashboard.
						SmartDashboard::PutNumber("Left Y Axis(5)", controller.GetRawAxis(5));
						SmartDashboard::PutNumber("Left Trigger(3)", controller.GetRawAxis(3));
						SmartDashboard::PutNumber("Right Trigger(4)", controller.GetRawAxis(4));
						SmartDashboard::PutNumber("Encoder Distance", encoder.GetDistance());
						SmartDashboard::PutNumber("Encoder Rate", encoder.GetRate());
						SmartDashboard::PutNumber("XButton", XButton);
						SmartDashboard::PutNumber("SquareButton", SquareButton);
						SmartDashboard::PutNumber("CircleButton", CircleButton);
						SmartDashboard::PutNumber("TriangleButton", TriangleButton);
						SmartDashboard::PutNumber("OptionsButton", OptionsButton);


						Wait(.005);													// Give the RoboRIO time to update.

		}
	}

};

START_ROBOT_CLASS(Robot);
