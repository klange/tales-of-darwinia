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

//TODO: Let speed be controlled by a variable, right now it's clamped
touchPosition* InputManager::moveToPosition(Vector3<u16>* currentPosition){
	s16 from_x = currentPosition->x();
	s16 from_y = currentPosition->y();

	touchPosition heldPosition;
	touchPosition* moveToPosition = new touchPosition();

	if(keysHeld() & KEY_TOUCH){
		touchRead(&heldPosition);
		s16 to_x = heldPosition.px;
		s16 to_y = heldPosition.py;

		s16 diff_x = clamp(to_x - from_x);
		s16 diff_y = clamp(to_y - from_y);

		moveToPosition->px = (u16)(from_x + diff_x);
		moveToPosition->py = (u16)(from_y + diff_y);
		return moveToPosition;
	}

	return NULL;
}

// This is really shitty...figure out a way to move once per X frames w/o clamping
s16 InputManager::clamp(s16 value){
	if (value > 1){
		return 1;
	}

	if (value < -1){
		return -1;
	}

	return value;
}

InputManager::InputManager(void){
}
