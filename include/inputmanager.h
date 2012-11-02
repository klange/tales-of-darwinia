#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <nds.h>
#include <vector3.h>

#define NO_POSITION_FOUND 1000
/**
 * InputManager class that manages inputs and delegates to appropriate entities.
 */

class InputManager{
	private:
		s16 clamp(s16 value);

	public:
		// Constructor
		InputManager();

		// Gets the current position for a tap
		touchPosition* getCurrentTouchPosition();

		// Gets the position to update to if you want to move
		touchPosition* moveToPosition(Vector3<u16>* currentPosition);

};

#endif
