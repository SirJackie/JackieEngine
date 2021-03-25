#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"
#include <vector>
using std::vector;

typedef vector<Vector4D> VectorList;

class Object4D {
public:
	vector<Vector4D> vecs;

	Object4D();
	void add(Vector4D vec);
};

#endif
