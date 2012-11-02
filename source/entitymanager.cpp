#include "entity.h"
#include "entitymanager.h"

// Singleton
EntityManager gEntityManager;

void EntityManager::Init()
{
	DynamicArrayInit(&mEntities, 16); // initial size
}

void EntityManager::Update()
{
	for(u32 i=0; i<mNumEntities; i++)
	{
		Entity* current = (Entity*) DynamicArrayGet(&mEntities, i);
		if(current->shouldBeRemoved){
			Remove(current);
			current->Render();
		}
		else {
			current->Update();
		}
	}
}

void EntityManager::Render()
{
	for(u32 i=0; i<mNumEntities; i++)
	{
		Entity* current = (Entity*) DynamicArrayGet(&mEntities, i);
		current->Render();
	}
}

void EntityManager::Destroy()
{
	DynamicArrayDelete(&mEntities);
}

void EntityManager::Add(Entity* entity)
{
	DynamicArraySet(&mEntities, mNumEntities++, entity);
}

void EntityManager::Remove(Entity* entity)
{
	for(u32 i=0; i<mNumEntities; i++)
	{
		Entity* current = (Entity*) DynamicArrayGet(&mEntities, i);
		if(current == entity)
		{
			void* last = DynamicArrayGet(&mEntities, mNumEntities - 1);
			DynamicArraySet(&mEntities, i, last); // note that this is fast, but does not maintain order of entities
			mNumEntities--;
			delete current;
			break;
		}
	}
}
