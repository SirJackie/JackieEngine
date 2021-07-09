#include "ObjectSupport.h"

FObject::FObject() {
	;
}

void FObject::Add(const FVector4D& vec) {
	vl.push_back(vec);
}
