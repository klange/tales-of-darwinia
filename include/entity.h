#ifndef ENTITY_H_
#define ENTITY_H_

/**
 * Represents an entity we can interact with. All game objects inherit from this
 */
class Entity {
	public:
		bool shouldBeRemoved;
		virtual ~Entity(void) {};
		
		virtual void Init();
		virtual void Destroy();

		virtual void Update() {};
		virtual void Render() {};

		virtual void nextFrame() {};
};

#endif
