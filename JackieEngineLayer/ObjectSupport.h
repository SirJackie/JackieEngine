#ifndef __JKEG_ObjectSupport__
#define __JKEG_ObjectSupport__

#include "MathSupport.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include <vector>

struct IndexedLineList
{
	std::vector<Vertex> vertices;
	std::vector<size_t> indices;
};

struct IndexedTriangleList
{
	std::vector<Vertex> vertices;
	std::vector<size_t> indices;
};

class Cube
{
public:
	Cube(float size)
	{
		const float side = size / 2.0f;

		// 0 // top-left
		vertices.emplace_back(
			Vertex(
				Vec3(-side, side, -side),
				Vec2(0.0f, 0.0f)
			)
		); 

		// 1 // top-right
		vertices.emplace_back(
			Vertex(
				Vec3(side, side, -side),
				Vec2(1.0f, 0.0f)
			)
		);

		// 2 // bottom-right
		vertices.emplace_back(
			Vertex(
				Vec3(side, -side, -side),
				Vec2(1.0f, 1.0f)
			)
		);
	}
	IndexedLineList GetLines() const
	{
		return {
			vertices,
			{
				0,1,  1,3,  3,2,  2,0,
				0,4,  1,5,	3,7,  2,6,
				4,5,  5,7,	7,6,  6,4
			}
		};
	}

	IndexedTriangleList GetTriangles() const
	{
		return{
			vertices,
			{
				0, 1, 2
			}
		};
	}
private:
	std::vector<Vertex> vertices;
};

#endif
