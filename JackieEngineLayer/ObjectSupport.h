#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"

typedef vector<FVector4D> Veclist;


class FObject {
public:
	Veclist vl;
	Veclist tmpVl;

	FObject();
	void Add(const FVector4D& vec);
};

#endif
