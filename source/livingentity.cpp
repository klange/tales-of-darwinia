#include "livingentity.h"
#include "vector3.h"
#include "math.h"
#include <stdio.h>


void LivingEntity::Update(void) {
	directionVector = targetPosition - position;
	u32 magnitude = directionVector.magnitude();

	if (magnitude < 2) {
		return;	
	}

	s16 newx = position.x() + floor(directionVector.x() * speed / magnitude);
	s16 newy = position.y() + floor(directionVector.y() * speed / magnitude);

	Vector3<s16> nextPosition = Vector3<s16>(newx, newy, 1);
	setPosition(nextPosition);
}

void LivingEntity::setTargetPosition(Vector3<s16> tar) {
	targetPosition = tar;
}

Vector3<s16> LivingEntity::getTargetPosition(void) {
	return targetPosition;
}
