#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"

typedef vector<FVector4D> Veclist;
typedef vector<i32>       Indexlist;


class FObject {
public:
	Veclist vl;
	Veclist tmpVl;
	Indexlist il;

	FObject();
	void    Add(const FVector4D& vec);
	void    Add(i32 index1, i32 index2, i32 index3);
	void    Translate(f32 x_, f32 y_, f32 z_);
	void    Rotate(f32 x_, f32 y_, f32 z_);
	string  ToString();
};

#endif
