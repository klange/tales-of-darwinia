#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <nds.h>
#include <vector3.h>

/**
 * InputManager class that manages inputs and delegates to appropriate entities.
 */

class InputManager{
	private:
		s16 round(float32 input);

	public:
		// Gets the current position for a tap
		touchPosition* getCurrentTouchPosition();

		// Gets the position to update to if you want to move
		touchPosition* moveToPosition(Vector3<s16>* currentPosition, float32 speed);
		InputManager();

};

#endif