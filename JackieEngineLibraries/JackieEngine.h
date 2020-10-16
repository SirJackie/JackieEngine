#pragma once

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

#include "LinearAlgebra.h"

#define MESHLIST_MAX_LENGTH 128

#define MESH4D_BUFFER_LENGTH 512


/*
** Mesh4D
*/

struct Mesh4D {
	Vector4D  a;
	Vector4D  b;
	Vector4D  c;
	int       red;
	int       green;
	int       blue;
	int       alpha;
};

Mesh4D CreateMesh4D(Vector4D a, Vector4D b, Vector4D c) {
	Mesh4D NewMesh;
	NewMesh.a = a;
	NewMesh.b = b;
	NewMesh.c = c;
	return NewMesh;
}

void SetMeshColor(Mesh4D* Mesh, int r, int g, int b, int a) {
	Mesh->red   = r;
	Mesh->green = g;
	Mesh->blue  = b;
	Mesh->alpha = a;
}

void OutputMesh4D(Mesh4D* Mesh) {
	char* buffer = (char*)malloc(MESH4D_BUFFER_LENGTH * sizeof(char));

	char* VectorABuffer = OutputVector4D(&(Mesh->a));
	char* VectorBBuffer = OutputVector4D(&(Mesh->b));
	char* VectorCBuffer = OutputVector4D(&(Mesh->c));

	sprintf_s(
		buffer, MESH4D_BUFFER_LENGTH, "Mesh4D[%s,\n         %s,\n         %s]",
		VectorABuffer, VectorBBuffer, VectorCBuffer
	);

	free(VectorABuffer);
	free(VectorBBuffer);
	free(VectorCBuffer);
}


/*
** MeshList4D
*/

struct MeshList4D {
	Mesh4D*  list;
	int      next;
	int      length;
};

MeshList4D CreateMeshList4D(int length) {
	MeshList4D NewMeshList;
	NewMeshList.list   = (Mesh4D*)malloc(length * sizeof(Mesh4D));
	NewMeshList.next   = 0;
	NewMeshList.length = length;
	return NewMeshList;
}

void DestroyMeshList4D(MeshList4D* TheMeshList) {
	free(TheMeshList->list);
}






//Mesh4D CubeMesh[12] = {
//  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f)),  //near
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f, -1.0f,  1.0f)),  //near
//  CreateMesh4D(CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f)),  //far
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f,  1.0f,  1.0f)),  //far
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f)),  //left
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f)),  //left
//  CreateMesh4D(CreateVector4D( 1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f, -1.0f,  1.0f)),  //right
//  CreateMesh4D(CreateVector4D( 1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f, -1.0f,  1.0f)),  //right
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f,  1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f,  1.0f,  1.0f)),  //up
//  CreateMesh4D(CreateVector4D(-1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f,  1.0f,  1.0f,  1.0f)),  //up
//  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D(-1.0f, -1.0f,  1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f,  1.0f,  1.0f)),  //down
//  CreateMesh4D(CreateVector4D(-1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f, -1.0f,  1.0f),  CreateVector4D( 1.0f, -1.0f,  1.0f,  1.0f))   //down
//};
//
//BOOL PlaceACube(MeshList4D* MeshList, int x, int y, int z) {
//	for (int i = 0; i < 12; i++) {
//		if (MeshList->MeshListNext + i >= MeshList->MeshListMaxLength) {
//			return FALSE;
//		}
//
//		MeshList->MeshList[MeshList->MeshListNext + i].a.x = CubeMesh[i].a.x + x;
//		MeshList->MeshList[MeshList->MeshListNext + i].a.y = CubeMesh[i].a.y + y;
//		MeshList->MeshList[MeshList->MeshListNext + i].a.z = CubeMesh[i].a.z + z;
//		MeshList->MeshList[MeshList->MeshListNext + i].a.w = CubeMesh[i].a.w;
//
//		MeshList->MeshList[MeshList->MeshListNext + i].b.x = CubeMesh[i].b.x + x;
//		MeshList->MeshList[MeshList->MeshListNext + i].b.y = CubeMesh[i].b.y + y;
//		MeshList->MeshList[MeshList->MeshListNext + i].b.z = CubeMesh[i].b.z + z;
//		MeshList->MeshList[MeshList->MeshListNext + i].b.w = CubeMesh[i].b.w;
//
//		MeshList->MeshList[MeshList->MeshListNext + i].c.x = CubeMesh[i].c.x + x;
//		MeshList->MeshList[MeshList->MeshListNext + i].c.y = CubeMesh[i].c.y + y;
//		MeshList->MeshList[MeshList->MeshListNext + i].c.z = CubeMesh[i].c.z + z;
//		MeshList->MeshList[MeshList->MeshListNext + i].c.w = CubeMesh[i].c.w;
//	}
//	return TRUE;
//}
