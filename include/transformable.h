#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include <nds.h>
#include "vector3.h"
#include "boundingbox.h"

/**
 * A class representing a transformable object. The object can move in the four cardinal directions,
 * and can be rotated or scaled.
 */
class Transformable {

	// TODO: Convert to use pointers/references
	public:
		Vector3<u16> position;
		Vector3<u16> size;
		Vector3<u16> directionVector;
		Vector3<u16> rotationAnchor;
		u16 rotation;

		void translate(Vector3<u16>);
		void rotate(u16 rotValue);
		void translateRotationAnchor(Vector3<u16>);
		void setPosition(Vector3<u16>);
		Vector3<u16>* getPosition();
		void setRotation(u16);
		void setScale(u16);

		void getBoundingBox(BoundingBox<u16>& bbOut);
};
#endif
