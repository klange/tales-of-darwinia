#include "entity.h"
#include "entitymanager.h"

void Entity::Init()
{
	gEntityManager.Add(this);
	shouldBeRemoved = false;
	hidden = false;
}
void Entity::Destroy()
{
	gEntityManager.Remove(this);
}

