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
		touchPosition* getCurrentTouchPosition();
		touchPosition* moveToPosition(Vector3<u16>* currentPosition);
		InputManager();

};

#endif
