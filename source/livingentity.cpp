#include "livingentity.h"
#include "vector3.h"

#define speed 3

s16 round(float32 input){
	s16 value = 0;
	if(input >= 0){
		value = (int)(input + .5);
	}
	else {
		value = (int)(input - .5);
	}
	return value;
}

void LivingEntity::Update(void) {
	directionVector = targetPosition - position;

	u32 magnitude = directionVector.magnitude();
	
	if (magnitude < 2) {
		return;
	}

	s16 newx = position.x() + round(directionVector.x() * speed / magnitude);
	s16 newy = position.y() + round(directionVector.y() * speed / magnitude);

	Vector3<s16> nextPosition = Vector3<s16>(newx, newy, 1);
	setPosition(nextPosition);
}

void LivingEntity::setTargetPosition(Vector3<s16> tar) {
	targetPosition = tar;
}
