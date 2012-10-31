#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include <nds.h>
#include "vector3.h"

class Transformable {
	public:
		Vector3<u16> position;
		Vector3<u16> directionVector;
		Vector3<u16> rotationAnchor;
		u16 rotation;

		void translate(Vector3<u16>);
		void rotate(u16 rotValue);
		void translateRotationAnchor(Vector3<u16>);
		void setPosition(Vector3<u16>);
		void setRotation(u16 rotValue);
};
#endif
