#include "entity.h"
#include "entitymanager.h"
#include "sprite.h"
#include "transformable.h"
#include "boundingbox.h"
#include "maps.h"
#include <vector3.h>
#include <stdio.h>

// Singleton
EntityManager gEntityManager;

void EntityManager::Init()
{
	mEntities = NULL;
}

void EntityManager::Update()
{
	for(LinkedList* node = mEntities; node != NULL; node = node->next)
	{
		Entity* current = (Entity*) node->data;
		if(current->shouldBeRemoved){
			//Remove(current);
		}
		else {
			current->Update();
		}
	}
}

bool EntityManager::IsMoveLegal(Entity* input)
{
	Sprite* entity = static_cast<Sprite*>(input);
	BoundingBox<s16> entitybb;
	entity->getBoundingBox(entitybb);

	// Make player walk through everything
	if( input->getType() != PLAYERENTITY)
	{
		for(LinkedList* node = mEntities; node != NULL; node = node->next)
		{
			Entity* entity_to_check = (Entity*) node->data;

			// Ugly casting but it's needed...
			if(entity_to_check->getType() != LIVINGENTITY || input == entity_to_check || entity_to_check->hidden)
				continue;

			Sprite* current = static_cast<Sprite*>(entity_to_check);

			BoundingBox<s16> bb;
			current->getBoundingBox(bb);
			if(entitybb.Intersects(bb))
				return false;
		}
	}

	/* Check the map walk/nowalk flag */
	return (gpMapEngine->collisionAbsolute(entity->position.x(), entity->position.y()));
}

void EntityManager::Render()
{
	for(LinkedList* node = mEntities; node != NULL; node = node->next)
	{
		Entity* current = (Entity*) node->data;
		current->Render();
	}
}

void EntityManager::Destroy()
{
	for(LinkedList* node = mEntities; node != NULL; node = node->next)
	{
		// Delete data too?
		Entity* entity = (Entity*) node->data;
		printf("deleting %d (%d)\n", entity, entity->getType());
		delete entity;
		delete node;
	}
}

void EntityManager::NextFrame()
{
	for(LinkedList* node = mEntities; node != NULL; node = node->next)
	{
		Entity* current = (Entity*) node->data;
		current->nextFrame();
	}

}

void EntityManager::Add(Entity* entity)
{
	mEntities = linkedlistAdd(&mEntities, entity); 
}

void EntityManager::Remove(Entity* entity)
{
	for(LinkedList* node = mEntities; node != NULL; node = node->next)
	{
		Entity* current = (Entity*) node->data;
		if(current == entity)
		{
			mNumEntities--;
			delete current;
			linkedlistRemove(node);
			return;
		}
	}
}
