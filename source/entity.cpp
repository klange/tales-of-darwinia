#include "entity.h"
#include "entitymanager.h"

void Entity::Init()
{
	gEntityManager.Add(this);
	shouldBeRemoved = false;
	hidden = false;
	type = OTHER;
}
void Entity::Destroy()
{
	gEntityManager.Remove(this);
}

EntityType Entity::getType(){
	return OTHER;
}

