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
		// Constructor
		InputManager();

		// Gets the current position for a tap
		bool getCurrentTouchPosition(Vector3<s16>& posOut);

		// Gets the position to update to if you want to move
		bool moveToPosition(Vector3<s16>* currentPosition, float32 speed, Vector3<s16>& destinationOut);

		// Called once a frame
		void Update();
};

// Singleton
extern InputManager gInputManager;

#endif
