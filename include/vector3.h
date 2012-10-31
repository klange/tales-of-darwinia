#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <stdlib.h>

template <class T>
class Vector3 {
	public:
		T* data;

		Vector3(void);
		Vector3(T, T, T);
		Vector3(const Vector3<T> &);
		~Vector3(void);

		T x(void);
		T y(void);
		T w(void);
		void setX(T);
		void setY(T);
		void setW(T);

		void normalize(void);

		Vector3<T>& operator=(const Vector3<T>&);	
		Vector3<T>& operator+=(const Vector3<T>&);
		const Vector3<T> operator+(const Vector3<T>&) const;
};

template <class T>
Vector3<T>::Vector3(void) {
	data = new T[3];
}

template <class T>
Vector3<T>::Vector3(T x, T y, T w) {
	data = new T[3];
	data[0] = x;
	data[1] = y;
	data[2] = w;
}

template <class T>
Vector3<T>::Vector3(const Vector3<T>& other) {
	data = new T[3];
	data[0] = other.x();
	data[1] = other.y();
	data[2] = other.w();
}

template <class T>
Vector3<T>::~Vector3(void) {
	delete data;
}

template <class T>
T Vector3<T>::x(void) {
	return data[0];
}

template <class T>
T Vector3<T>::y(void) {
	return data[1];
}

template <class T>
T Vector3<T>::w(void) {
	return data[2];
}

template <class T>
void Vector3<T>::setX(T x) {
	data[0] = x;
}

template <class T>
void Vector3<T>::setY(T y) {
	data[1] = y;
}

template <class T>
void Vector3<T>::setW(T w) {
	data[2] = w;
}

template <class T>
void Vector3<T>::normalize(void) {
	data[0] = x()/w();
	data[1] = y()/w();
	data[2] = w()/w();
}

template <class T>
Vector3<T>& Vector3<T>::operator=(const Vector3<T>& other) {
	if (this == &other) {
		return *this;
	}

	delete data;
	data = new T[3];
	data[0] = other.x();
	data[1] = other.y();
	data[2] = other.w();

	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& other) {
	data[0] = x() + other.x();
	data[1] = y() + other.y();
	data[2] = w() + other.y();

	return *this;
}

template <class T>
const Vector3<T> Vector3<T>::operator+(const Vector3<T>& other) const {
	return Vector3<T>(*this) += other;
}

#endif