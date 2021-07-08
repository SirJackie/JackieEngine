#include "ObjectSupport.h"

FObject4D::FObject4D() {
	;
}

void FObject4D::Add(const FVector4D& vec) {
	vl.push_back(vec);
}
