#include "livingentity.h"

void LivingEntity::Update(void) {
	directionVector = targetPos - position;
}
