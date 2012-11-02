#include <nds.h>
#include "inputmanager.h"

// Singleton
InputManager gInputManager;

void InputManager::Update()
{
}

touchPosition* InputManager::getCurrentTouchPosition(){
	
	touchPosition* tap = new touchPosition();

	if(keysDown() & KEY_TOUCH){
		touchRead(tap);
		return tap;
	}
	return NULL;
}

bool InputManager::moveToPosition(Vector3<s16>* currentPosition, float32 speed, Vector3<s16>& destinationOut)
{
	s16 from_x = currentPosition->x();
	s16 from_y = currentPosition->y();

	touchPosition heldPosition;

	if(keysHeld() & KEY_TOUCH){
		touchRead(&heldPosition);
		s16 diff_x = (heldPosition.px - from_x);
		s16 diff_y = (heldPosition.py - from_y);

		u32 magnitude = sqrt32(diff_x * diff_x + diff_y * diff_y);

		if (magnitude < 2)
			return NULL;

		diff_x = round(diff_x * speed / magnitude);
		diff_y = round(diff_y * speed / magnitude);

		destinationOut.setX((u16)(from_x + diff_x));
		destinationOut.setY((u16)(from_y + diff_y));

		return true;
	}
	else
	{
		destinationOut = *currentPosition;
		return false;
	}
}

// This is really shitty...figure out a way to move once per X frames w/o clamping
s16 InputManager::round(float32 input){
	s16 value = 0;
	if(input >= 0){
		value = (int)(input + .5);
	}
	else {
		value = (int)(input - .5);
	}
	return value;
}

InputManager::InputManager(void){
}
