#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include <vector>


class ObjectHolder {
public:
	// Original Object
	std::vector<Vertex> vec_o;
	std::vector<int> triAi_o, triBi_o, triCi_o;

	// Temporal Duplication for Transformation Purposes
	std::vector<Vertex> vec;
	std::vector<int> triAi, triBi, triCi;

	void Duplicate() {
		vec = vec_o;
		triAi = triAi_o;
		triBi = triBi_o;
		triCi = triCi_o;
	}
};

#endif
