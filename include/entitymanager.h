#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include <nds.h>
#include <stdint.h>

// Forward declations
class Entity;

/**
 * Contains all the entities, allows us to iterate over them, etc.
 */
class EntityManager
{
public:
	void Init();
	void Destroy();

	void Update();
	void Render();

	/**
	 * Invoke nextFrame on all applicable entities
	 */
	void NextFrame();

private:
	// private data
	u32 mNumEntities;
	DynamicArray mEntities;

	friend class Entity;
	// methods for Entity to add itself to the manager
	void Add(Entity* entity);
	void Remove(Entity* entity);

};

// Singleton
extern EntityManager gEntityManager;

#endif // ENTITY_MANAGER_H_
