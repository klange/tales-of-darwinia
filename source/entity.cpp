#include "entity.h"
#include "entitymanager.h"

void Entity::Init()
{
	gEntityManager.Add(this);
}
void Entity::Destroy()
{
	gEntityManager.Remove(this);
}

