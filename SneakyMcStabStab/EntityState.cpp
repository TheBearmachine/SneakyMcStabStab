#include "EntityState.h"
#include "Entity.h"

void EntityState::transition(EntityState * from, EntityState * to)
{
	from->exit();
	to->entry();
	mOwner->setCurrentState(to);
}
