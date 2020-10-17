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

Mesh4D CubeMesh4DArray[12] = {
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

MeshList4D CubeModel;

void InitBuiltInModels() {
	CubeModel.list = CubeMesh4DArray;
	CubeModel.next = 12;
	CubeModel.length = 12;
}

void AddModelToMeshList4D(MeshList4D* MeshList, MeshList4D* Model, float x, float y, float z) {
	MeshList4D TmpMeshList = CloneMeshList4D(Model);

	for (int i = 0; i < TmpMeshList.next; i++) {
		TmpMeshList.list[i].a.x += x;
		TmpMeshList.list[i].a.y += y;
		TmpMeshList.list[i].a.z += z;

		TmpMeshList.list[i].b.x += x;
		TmpMeshList.list[i].b.y += y;
		TmpMeshList.list[i].b.z += z;
		
		TmpMeshList.list[i].c.x += x;
		TmpMeshList.list[i].c.y += y;
		TmpMeshList.list[i].c.z += z;
	}

	AddMeshList4DToMeshList4D(MeshList, &TmpMeshList);

	DestroyMeshList4D(&TmpMeshList);
}
