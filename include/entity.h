#ifndef ENTITY_H_
#define ENTITY_H_

typedef enum _EntityType{
	LIVINGENTITY,
	OTHER,
} EntityType;

/**
 * Represents an entity we can interact with. All game objects inherit from this
 */
class Entity {
	public:
		bool hidden;
		bool shouldBeRemoved;
		EntityType type;

		virtual ~Entity(void) {};
		
		virtual void Init();
		virtual void Destroy();

		virtual void Update() {};

		virtual void Render() {};
		virtual void nextFrame() {};
		virtual EntityType getType();
};

#endif
