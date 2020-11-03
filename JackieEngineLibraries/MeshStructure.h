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

#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif


/*
** Define Buffer Default Length
*/

#define MESH4D_BUFFER_LENGTH 2048
#define MESH4DLIST_BUFFER_LENGTH 262140


/*
** Define MeshList4D Default Length
*/

#define MESHLIST4D_MAX_LENGTH 128


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
	Mesh->red = r;
	Mesh->green = g;
	Mesh->blue = b;
	Mesh->alpha = a;
}

char* OutputMesh4D(Mesh4D* Mesh) {
	char* buffer = (char*)malloc(MESH4D_BUFFER_LENGTH * sizeof(char));

	char* VectorABuffer = OutputVector4D(&(Mesh->a));
	char* VectorBBuffer = OutputVector4D(&(Mesh->b));
	char* VectorCBuffer = OutputVector4D(&(Mesh->c));

	sprintf_s(
		buffer, MESH4D_BUFFER_LENGTH, "Mesh4D[ %s,\n        %s,\n        %s ]",
		VectorABuffer, VectorBBuffer, VectorCBuffer
	);

	free(VectorABuffer);
	free(VectorBBuffer);
	free(VectorCBuffer);

	return buffer;
}

char* OutputMesh4DWithMore28Spaces(Mesh4D* Mesh) {
	char* buffer = (char*)malloc(MESH4D_BUFFER_LENGTH * sizeof(char));

	char* VectorABuffer = OutputVector4D(&(Mesh->a));
	char* VectorBBuffer = OutputVector4D(&(Mesh->b));
	char* VectorCBuffer = OutputVector4D(&(Mesh->c));
	sprintf_s(
		buffer, MESH4D_BUFFER_LENGTH, "Mesh4D[ %s,\n                                    %s,\n                                    %s ]\n                            ",
		VectorABuffer, VectorBBuffer, VectorCBuffer
	);

	free(VectorABuffer);
	free(VectorBBuffer);
	free(VectorCBuffer);

	return buffer;
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
	NewMeshList.list = (Mesh4D*)malloc(length * sizeof(Mesh4D));
	NewMeshList.next = 0;
	NewMeshList.length = length;
	return NewMeshList;
}

void DestroyMeshList4D(MeshList4D* MeshList) {
	free(MeshList->list);
	MeshList->list = nullptr;
}

MeshList4D CloneMeshList4D(MeshList4D* MeshList) {
	MeshList4D NewMeshList = CreateMeshList4D(MeshList->length);
	for (int i = 0; i < MeshList->next; i++) {
		NewMeshList.list[i] = MeshList->list[i];
	}
	NewMeshList.next = MeshList->next;
	return NewMeshList;
}

BOOL AddMesh4DToMeshList4D(MeshList4D* MeshList, Mesh4D* Mesh) {
	if (MeshList->next >= MeshList->length) {
		return FALSE;
	}
	else {
		MeshList->list[MeshList->next] = *Mesh;
		MeshList->next += 1;
		return TRUE;
	}
}

void AddMeshList4DToMeshList4D(MeshList4D* MeshList, MeshList4D* ListToAdd) {
	for (int i = 0; i < ListToAdd->next; i++) {
		MeshList->list[MeshList->next + i] = ListToAdd->list[i];
	}
	MeshList->next += ListToAdd->next;
}

char* OutputMeshList4D(MeshList4D* MeshList, int from, int to) {
	char* buffer = (char*)malloc(MESH4DLIST_BUFFER_LENGTH * sizeof(char));

	ZeroMemory(buffer, MESH4DLIST_BUFFER_LENGTH * sizeof(char));

	sprintf_s(
		buffer, MESH4DLIST_BUFFER_LENGTH,
		"MeshList4D (%5d, %5d) [ ",
		from, to
	);

	char* MeshStringOutput;

	for (int i = from; i < to; i++) {
		MeshStringOutput = OutputMesh4DWithMore28Spaces(&((MeshList->list)[i]));
		strcat_s(buffer, MESH4DLIST_BUFFER_LENGTH, MeshStringOutput);
		free(MeshStringOutput);
	}

	//strcat_s(buffer, MESH4DLIST_BUFFER_LENGTH, "]");

	return buffer;
}
