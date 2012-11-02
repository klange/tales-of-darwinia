#include "entity.h"
#include "entitymanager.h"

void Entity::Init()
{
	gEntityManager.Add(this);
	shouldBeRemoved = false;
}
void Entity::Destroy()
{
	gEntityManager.Remove(this);
}

