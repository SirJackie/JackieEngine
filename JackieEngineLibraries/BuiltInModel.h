#pragma once

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__
#include "LinearAlgebra.h"
#endif

#ifndef __MEST_STRUCTURE_H__
#define __MEST_STRUCTURE_H__
#include "MeshStructure.h"
#endif


/*
** Built-in Models
*/

Mesh4D CubeMesh[12] = {
  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f)),  //near
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f, -1.0f,  1.0f)),  //near
  CreateMesh4D(CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f)),  //far
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f,  1.0f,  1.0f)),  //far
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f)),  //left
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f)),  //left
  CreateMesh4D(CreateVector4D(1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f, -1.0f,  1.0f)),  //right
  CreateMesh4D(CreateVector4D(1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f, -1.0f,  1.0f)),  //right
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f,  1.0f,  1.0f)),  //up
  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f,  1.0f,  1.0f,  1.0f)),  //up
  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f,  1.0f,  1.0f)),  //down
  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(1.0f, -1.0f,  1.0f,  1.0f))   //down
};


/*
** Model Operation Functions
*/

void AddMesh4DArrayToMeshList4D(MeshList4D* MeshList, Mesh4D* Mesh4DArray) {
	for (int i = 0; i < 12; i++) {
		MeshList->list[MeshList->next + i] = Mesh4DArray[i];
	}
	MeshList->next += 12;
}
