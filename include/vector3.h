#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <stdlib.h>

/**
 * A 3-vector class that with a parameterized container type
 */
template <typename T>
class Vector3 {
	public:
		T* data;

		Vector3(void);
		Vector3(T, T, T);
		Vector3(const Vector3<T> &);
		~Vector3(void);

		T x(void) const;
		T y(void) const;
		T w(void) const;
		void setX(T);
		void setY(T);
		void setW(T);

		virtual void normalize(void);

		virtual Vector3<T>& operator=(const Vector3<T> &);	

		virtual Vector3<T> &operator+=(const Vector3<T> &);
		virtual const Vector3<T> operator+(const Vector3<T> &) const;

		virtual Vector3<T> &operator-=(const Vector3<T> &);
		virtual const Vector3<T> operator-(const Vector3<T> &) const;

		/* todo: dot product */
		/* todo: scalar product */
};

template <typename T>
Vector3<T>::Vector3(void) {
	data = new T[3];
}

template <typename T>
Vector3<T>::Vector3(T x, T y, T w) {
	data = new T[3];
	data[0] = x;
	data[1] = y;
	data[2] = w;
}

template <typename T>
Vector3<T>::Vector3(const Vector3<T>& other) {
	data = new T[3];
	memcpy(data, other.data, 3 * sizeof(T));
}

template <typename T>
Vector3<T>::~Vector3(void) {
	delete data;
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
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& other) {
	if (this == &other) {
		return *this;
	}
	memcpy(data, other.data, 3 * sizeof(T));
	return *this;
}

template <typename T>
Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other) {
	for (int lcv = 0; lcv < 3; lcv++) {
		data[lcv] = data[lcv] + other.data[lcv];
	}
	return *this;
}

template <typename T>
const Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const {
	Vector3<T> result = *this;
	result += other;
	return result;
}

template <typename T>
Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other) {
	for (int lcv = 0; lcv < 3; lcv++) {
		data[lcv] = data[lcv] - other.data[lcv];
	}
	return *this;
}

template <typename T>
const Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const {
	Vector3<T> result = *this;
	result -= other;
	return result;
}

#endif