#include "ObjectSupport.h"

Object4D::Object4D() {
	;
}

void Object4D::add(FVector4D vec) {
	vecs.push_back(vec);
}
