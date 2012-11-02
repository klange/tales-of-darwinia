#include "transformable.h"

#include <nds.h>
#include <vector3.h>

void Transformable::translate(Vector3<u16> translationComponents) {
	position += translationComponents;
}

void Transformable::rotate(u16 rotValue) {
	rotation += rotValue;
}

void Transformable::translateRotationAnchor(Vector3<u16> rotAnchorPos) {
	/* how would this even work? */
}

void Transformable::setPosition(Vector3<u16> newPosition) {
	position = newPosition;
}

//TODO: Make stuff use pointers instead later
Vector3<u16>* Transformable::getPosition() {
	return &position;
}

void Transformable::setRotation(u16 rotValue) {
	rotation = rotValue;
}

void Transformable::getBoundingBox(BoundingBox<u16>& bbOut)
{
	bbOut.mTopLeft = position;
	bbOut.mBottomRight = position + size;
}
