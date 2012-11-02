#include <nds.h>
#include "inputmanager.h"

touchPosition* InputManager::getCurrentTouchPosition(){
	
	touchPosition* tap = new touchPosition();

	if(keysDown() & KEY_TOUCH){
		touchRead(tap);
		return tap;
	}
	return NULL;
}

touchPosition* InputManager::moveToPosition(Vector3<s16>* currentPosition, float32 speed){
	s16 from_x = currentPosition->x();
	s16 from_y = currentPosition->y();

	touchPosition heldPosition;
	touchPosition* moveToPosition = new touchPosition();

	if(keysHeld() & KEY_TOUCH){
		touchRead(&heldPosition);
		s16 to_x = heldPosition.px;
		s16 to_y = heldPosition.py;

		s16 diff_x = (to_x - from_x);
		s16 diff_y = (to_y - from_y);

		u32 magnitude = sqrt32(diff_x*diff_x + diff_y*diff_y);

		diff_x = round(diff_x * speed / magnitude);
		diff_y = round(diff_y * speed / magnitude);

		moveToPosition->px = (u16)(from_x + diff_x);
		moveToPosition->py = (u16)(from_y + diff_y);
		return moveToPosition;
	}

	return NULL;
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
