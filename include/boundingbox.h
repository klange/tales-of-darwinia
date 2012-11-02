#ifndef BOUNDING_BOX_H_
#define BOUNDING_BOX_H_

#include "vector3.h"

/**
 * A bounding box class for collision detection
 */
template <typename T>
class BoundingBox {
public:
	BoundingBox() {}
	BoundingBox(T left, T top, T right, T bottom);
	BoundingBox(const Vector3<T>& topLeft, const Vector3<T>& bottomRight);

	bool PointInside(const Vector3<T>& point) const;
	bool Intersects(const BoundingBox<T>& other) const;

	Vector3<T> mTopLeft;
	Vector3<T> mBottomRight;
};

/* Methods */

template <typename T>
BoundingBox<T>::BoundingBox(T left, T top, T right, T bottom)
: mTopLeft(left, top, 0), mBottomRight(right, bottom)
{
}

template <typename T>
BoundingBox<T>::BoundingBox(const Vector3<T>& topLeft, const Vector3<T>& bottomRight)
: mTopLeft(topLeft), mBottomRight(bottomRight)
{
}

template <typename T>
bool BoundingBox<T>::PointInside(const Vector3<T>& point) const
{
	return ( (point.x() >= mTopLeft.x()) &&
			 (point.x() <= mBottomRight.x()) &&
			 (point.y() >= mTopLeft.y()) &&
			 (point.y() <= mBottomRight.y()) );
}

template <typename T>
bool BoundingBox<T>::Intersects(const BoundingBox<T>& other) const
{
	// note this will only work if T is a signed type
	Vector3<T> mid = (mTopLeft + mBottomRight) / 2;
	Vector3<T> otherMid = (other.mTopLeft + other.mBottomRight) / 2;
	
	Vector3<T> halfExtent = (mBottomRight - mTopLeft) / 2;
	Vector3<T> otherHalfExtent = (other.mBottomRight - other.mTopLeft) / 2;

	return (abs(mid.x() - otherMid.x()) < (halfExtent.x() + otherHalfExtent.x())) &&
		(abs(mid.y() - otherMid.y()) < (halfExtent.y() + otherHalfExtent.y()));
}

#endif // BOUNDING_BOX_H_
