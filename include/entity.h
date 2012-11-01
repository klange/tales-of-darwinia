#ifndef ENTITY_H_
#define ENTITY_H_

#include "inputmanager.h"

/**
 * Represents an entity we can interact with. All game objects inherit from this
 */
class Entity {
	public:
		virtual ~Entity(void) {};
		
		virtual void Init();
		virtual void Update(InputManager* inputManager) {};
		virtual void Destroy();
};

#endif
