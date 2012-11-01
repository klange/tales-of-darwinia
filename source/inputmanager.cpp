#include <nds.h>
#include "inputmanager.h"

/**
 * Handles only touch input correctly for now
 */
void InputManager::handleInput(void){
	touchPosition tap;
	// Get the input params
	if (keysHeld() & KEY_TOUCH){
		touchRead(&tap);
	}


	// Find the right entity to call onTap()
	
}

InputManager::InputManager(void){
	// Probably want to initialize with a given EntityManager in here
	// TODO: Add args to accept an EntityManager
}
