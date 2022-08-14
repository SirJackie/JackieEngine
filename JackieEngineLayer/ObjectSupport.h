#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include <vector>

struct IndexedLineList
{
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
};

class Cube
{
public:
	Cube(float size)
	{
		const float side = size / 2.0f;
		vertices.emplace_back(-side, side, -side); // 0 // top-left
		vertices.emplace_back(side, side, -side);  // 1 // top-right
		vertices.emplace_back(side, -side, -side); // 2 // bottom-right
	}
	IndexedLineList GetLines() const
	{
		return{
			vertices,{
				0,1,  1,3,  3,2,  2,0,
				0,4,  1,5,	3,7,  2,6,
				4,5,  5,7,	7,6,  6,4 }
		};
	}
private:
	std::vector<Vec3> vertices;
};

#endif
