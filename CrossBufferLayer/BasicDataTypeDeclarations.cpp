#include "BasicDataTypeDeclarations.h"

i32 CS_iclamp(i32 min, i32 x, i32 max)
{
	if (x < min) {
		int a = 0;
	}
	return (x < min ? min : (x >= max ? (max - 1) : x));
}

f32 CS_fclamp(f32 min, f32 x, f32 max)
{
	return (x < min ? min : (x > max ? max : x));
}
