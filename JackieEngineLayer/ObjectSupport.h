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

		// 3 // bottom-left
		vertices.emplace_back(
			Vertex(
				Vec3(-side, -side, -side),
				Vec2(0.0f, 1.0f)
			)
		);

		// 4 // top-left(far)
		vertices.emplace_back(
			Vertex(
				Vec3(-side, side, side),
				Vec2(0.0f, 0.0f)
			)
		);

		// 5 // top-right(far)
		vertices.emplace_back(
			Vertex(
				Vec3(side, side, side),
				Vec2(1.0f, 0.0f)
			)
		);

		// 6 // bottom-right(far)
		vertices.emplace_back(
			Vertex(
				Vec3(side, -side, side),
				Vec2(1.0f, 1.0f)
			)
		);

		// 7 // bottom-left(far)
		vertices.emplace_back(
			Vertex(
				Vec3(-side, -side, side),
				Vec2(0.0f, 1.0f)
			)
		);
	}
	IndexedLineList GetLines() const
	{
		return {
			vertices,
			{
				0,1, 1,2, 2,3, 3,0,
				4,5, 5,6, 6,7, 7,4,
				0,4, 1,5, 2,6, 3,7
			}
		};
	}

	IndexedTriangleList GetTriangles() const
	{
		return{
			vertices,
			{
				0,1,2, 2,3,0
			}
		};
	}
private:
	std::vector<Vertex> vertices;
};

#endif
