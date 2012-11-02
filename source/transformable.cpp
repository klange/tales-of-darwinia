#include "transformable.h"

#include <nds.h>
#include <vector3.h>

void Transformable::translate(Vector3<s16> translationComponents) {
	position += translationComponents;
}

void Transformable::rotate(s16 rotValue) {
	rotation += rotValue;
}

void Transformable::translateRotationAnchor(Vector3<s16> rotAnchorPos) {
	/* how would this even work? */
}

void Transformable::setPosition(Vector3<s16> newPosition) {
	position = newPosition;
}

//TODO: Make stuff use pointers instead later
Vector3<s16>* Transformable::getPosition() {
	return &position;
}
Vector3<s16>* Transformable::getDirection() {
	return &directionVector;
}

void Transformable::setRotation(s16 rotValue) {
	rotation = rotValue;
}

void Transformable::getBoundingBox(BoundingBox<s16>& bbOut)
{
	bbOut.mTopLeft = position;
	bbOut.mBottomRight = position + size;
}

