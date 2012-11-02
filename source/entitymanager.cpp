#include "entity.h"
#include "entitymanager.h"

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
