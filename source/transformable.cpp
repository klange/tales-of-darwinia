#include "transformable.h"

#include <nds.h>
#include <vector3.h>

void Transformable::translate(Vector3<s16> translationComponents) {
	position += translationComponents;
}

void Transformable::rotate(s16 rotValue) {
	rotation += rotValue;
}

void Transformable::translateRotationAnchor(Vector3<s16> anchorPos) {
	anchor = anchorPos;
}

void Transformable::setPosition(Vector3<s16> newPosition) {
	position = newPosition;
}

void Transformable::setRotation(s16 rotValue) {
	rotation = rotValue;
}

void Transformable::getBoundingBox(BoundingBox<s16>& bbOut)
{
	bbOut.mTopLeft = position + anchor;
	bbOut.mBottomRight = position + size + anchor;
}

