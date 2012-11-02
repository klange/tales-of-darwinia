#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <stdlib.h>

/**
 * A 3-vector class that with a parameterized container type
 */
template <typename T>
class Vector3 {
	public:
		T data[3];

		Vector3(void);
		Vector3(T, T, T);

		// copy constructor
		Vector3(const Vector3<T> &);

		T x(void) const;
		T y(void) const;
		T w(void) const;
		void setX(T);
		void setY(T);
		void setW(T);

		void normalize(void);

		// assignment operator
		Vector3<T>& operator=(const Vector3<T> &);


		Vector3<T> &operator+=(const Vector3<T> &);
		const Vector3<T> operator+(const Vector3<T> &) const;

		Vector3<T> &operator-=(const Vector3<T> &);
		const Vector3<T> operator-(const Vector3<T> &) const;

		/* todo: dot product */
		/* todo: scalar product */
};

template <typename T>
Vector3<T>::Vector3(void) {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

template <typename T>
Vector3<T>::Vector3(T x, T y, T w) {
	data[0] = x;
	data[1] = y;
	data[2] = w;
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T>& other)
{
	data[0] = other.data[0];
	data[1] = other.data[1];
	data[2] = other.data[2];
}

template <typename T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& other) {
	data[0] = other.data[0];
	data[1] = other.data[1];
	data[2] = other.data[2];
	return *this;
}

template <typename T>
T Vector3<T>::x(void) const {
	return data[0];
}

template <typename T>
T Vector3<T>::y(void) const {
	return data[1];
}

template <typename T>
T Vector3<T>::w(void) const {
	return data[2];
}

template <typename T>
void Vector3<T>::setX(T x) {
	data[0] = x;
}

template <typename T>
void Vector3<T>::setY(T y) {
	data[1] = y;
}

template <typename T>
void Vector3<T>::setW(T w) {
	data[2] = w;
}

template <typename T>
void Vector3<T>::normalize(void) {
	data[0] = x()/w();
	data[1] = y()/w();
	data[2] = w()/w();
}

template <typename T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
	data[0] += other.data[0];
	data[1] += other.data[1];
	data[2] += other.data[2];
	return *this;
}

template <typename T>
const Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const {
	return Vector3<T>(data[0] + other.data[0], data[1] + other.data[1], data[2] + other.data[2]);
}

template <typename T>
Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	data[2] -= other.data[2];
	return *this;
}

template <typename T>
const Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const {
	return Vector3<T>(data[0] - other.data[0], data[1] - other.data[1], data[2] - other.data[2]);
}

#endif
