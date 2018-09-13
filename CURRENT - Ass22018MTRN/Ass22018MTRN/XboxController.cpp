#include "XboxController.h"

XINPUT_BATTERY_INFORMATION BatteryInformation;
XINPUT_STATE State;
XINPUT_VIBRATION Vibration;

//Instance of controller made within main, assigns ID here
GamePad::XBoxController::XBoxController(XInputWrapper * xinput, DWORD id)	
{
		ControllerID = id;
}

//Either assigns controller ID or collects the current data member value. Unsure which it should be doing!
DWORD GamePad::XBoxController::GetControllerId()
{
	return ControllerID;											//Returns the data member ID value												
}

bool GamePad::XBoxController::IsConnected()
{
	int currentID = ControllerID;									//Gets the ID value of the current controller
	DWORD result = XInputGetState(currentID, &State);				//Checks the status this controller

	if (result == ERROR_SUCCESS)									//Could this be simplified to return(!ERROR_SUCCESS);? Depends on the compile environment apparently
	{
		return true;
	}else{
		return false;
	}	
}



//The following function definitions deal with handling of each button on the controller
bool GamePad::XBoxController::PressedA()
{
	bool A_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
	//could probably just do return((State.Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0); Same for all the ones below but oh well, this is clear to read
	return A_button_pressed;
}

bool GamePad::XBoxController::PressedB()
{
	bool B_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
	return B_button_pressed;
}

bool GamePad::XBoxController::PressedX()
{
	bool X_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
	return X_button_pressed;
}

bool GamePad::XBoxController::PressedY()
{
	bool Y_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
	return Y_button_pressed;
}

bool GamePad::XBoxController::PressedLeftShoulder()
{
	bool Left_Shoulder_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
	return Left_Shoulder_button_pressed;
}

bool GamePad::XBoxController::PressedRightShoulder()
{
	bool Right_Shoulder_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
	return Right_Shoulder_button_pressed;
}

bool GamePad::XBoxController::PressedLeftDpad()
{
	bool Left_Dpad_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
	return Left_Dpad_button_pressed;
}

bool GamePad::XBoxController::PressedRightDpad()
{
	bool Right_Dpad_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
	return Right_Dpad_button_pressed;
}

bool GamePad::XBoxController::PressedUpDpad()
{
	bool Up_Dpad_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
	return Up_Dpad_button_pressed;
}

bool GamePad::XBoxController::PressedDownDpad()
{
	bool Down_Dpad_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
	return Down_Dpad_button_pressed;
}

bool GamePad::XBoxController::PressedStart()
{
	bool Start_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
	return Start_button_pressed;
}

bool GamePad::XBoxController::PressedBack()
{
	bool Back_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
	return Back_button_pressed;
}

bool GamePad::XBoxController::PressedLeftThumb()
{
	bool Left_Thumb_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
	return Left_Thumb_button_pressed;
}

bool GamePad::XBoxController::PressedRightThumb()
{
	bool Right_Thumb_button_pressed = ((State.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);
	return Right_Thumb_button_pressed;
}



//The following function definitions will return the amount the triggers are pressed as a percentage
BYTE GamePad::XBoxController::LeftTriggerLocation()
{
	float leftTrigger = (float)State.Gamepad.bLeftTrigger / 255;	//range is 0-255, this converts to percentage (unsure if percentage is what we want though)
	return (BYTE) round(leftTrigger);
}

BYTE GamePad::XBoxController::RightTriggerLocation()
{
	float rightTrigger = (float)State.Gamepad.bRightTrigger / 255;
	return (BYTE) round(rightTrigger);
}



//The following function definitions calculate the thumb stick locations accounting for deadzone and return a coordinate object
GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{
	float normLX = max(-1, (float)State.Gamepad.sThumbLX / 32767);	//Returns Thumb LX position normalised from -1 to 1
	float normLY = max(-1, (float)State.Gamepad.sThumbLY / 32767);	//As above for LY

	int deadzone = GetRadius();
	deadzone = max(-1, deadzone / 32767);							//Does this make sense as a way to normalise the value? Unsure of what they should look like
	
	float leftStickX = (abs(normLX) < deadzone ? 0 : normLX);		//takes absolute version of normalised value and compares to deadzone
	float leftStickY = (abs(normLY) < deadzone ? 0 : normLY);		//then sets normLX/Y to zero if less than the deadzone value

	if (deadzone > 0) leftStickX *= 1 / (1 - deadzone);				//If eg. the deadzone is 80% of the entire zone, this causes the remaining 20% to act
	if (deadzone > 0) leftStickY *= 1 / (1 - deadzone);				//as if it is actually 0%-100% instead of causing a sudden jump in sensitivity

	return GamePad::Coordinate((short) round(leftStickX), (short) round(leftStickY));
}

GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	float normRX = max(-1, (float)State.Gamepad.sThumbRX / 32767);
	float normRY = max(-1, (float)State.Gamepad.sThumbRY / 32767);

	int deadzone = GetRadius();
	deadzone = max(-1, deadzone / 32767);					
	
	float rightStickX = (abs(normRX) < deadzone ? 0 : normRX);
	float rightStickY = (abs(normRY) < deadzone ? 0 : normRY);

	if (deadzone > 0) rightStickX *= 1 / (1 - deadzone);
	if (deadzone > 0) rightStickY *= 1 / (1 - deadzone);	
	
	return GamePad::Coordinate((short)round(rightStickX), (short)round(rightStickY));
}



//Creates a vibration struct and assigns it the values supplied in the declaration
void GamePad::XBoxController::Vibrate(WORD left, WORD right)
{
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));				//Clears memory for vibration state

	int left_motor = int(left * 65535.0f);							//Normalises values given
	int right_motor = int(right * 65535.0f);

	Vibration.wLeftMotorSpeed = left_motor;							//This struct was already created up top of file. Simply setting values here
	Vibration.wRightMotorSpeed = right_motor;

	XInputSetState(ControllerID, &Vibration);						//Apply vibration to controller object
}



//Simple Getter and Setter functions
void GamePad::XBoxController::SetDeadzone(unsigned int radius)
{
	Radius = radius;
}

int GamePad::XBoxController::GetRadius()
{
	return Radius;
}

