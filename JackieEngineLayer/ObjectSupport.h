#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"
#include <vector>
using std::vector;

typedef vector<Vector4D> Vector4DList;

class Object4D {
public:
	Vector4DList vecs;

	Object4D();
	void add(Vector4D vec);
};

#endif
