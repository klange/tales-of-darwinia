#include "transformable.h"

#include <nds.h>
#include <vector3.h>

void Transformable::translate(Vector3<u16> translationComponents) {
	position += translationComponents;
}
