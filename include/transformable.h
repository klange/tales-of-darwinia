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
	protected:
		Vector3<s16> directionVector;
		Vector3<s16> anchor;
		u8 frameCounter;

	// TODO: make these thing
	public:
		Vector3<s16> position;
		Vector3<s16> size;
		u16 rotation;

		void translate(Vector3<s16>);
		void rotate(s16 rotValue);
		void translateRotationAnchor(Vector3<s16>);
		void setPosition(Vector3<s16>);
		void setRotation(s16);
		void setScale(s16);

		void getBoundingBox(BoundingBox<s16>& bbOut, u16 scalingFactor);
		void getBoundingBox(BoundingBox<s16>& bbOut);
};
#endif
