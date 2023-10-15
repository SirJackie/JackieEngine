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


class Clipper {
public:
	float zNear;
	ObjectHolder& objH;

	Clipper(float _zNear, ObjectHolder& _objH) :
		zNear(_zNear),
		objH(_objH)
	{
		;
	}

	void ClipOneIn(int in, int out1, int out2) {
		Vertex& vA = objH.vec[in];
		Vertex& vB = objH.vec[out1];
		Vertex& vC = objH.vec[out2];

		float alphaD = (1.0f - vA.pos.z) / (vB.pos.z - vA.pos.z);
		objH.vec.emplace_back(vA * (1 - alphaD) + vB * alphaD);
		int iD = objH.vec.size() - 1;

		float alphaE = (1.0f - vA.pos.z) / (vC.pos.z - vA.pos.z);
		objH.vec.emplace_back(vA * (1 - alphaE) + vC * alphaE);
		int iE = objH.vec.size() - 1;

		objH.triAi.emplace_back(in);
		objH.triBi.emplace_back(iD);
		objH.triCi.emplace_back(iE);
	}

	void ClipOneOut(int out, int in1, int in2) {
		Vertex& vA = objH.vec[out];
		Vertex& vB = objH.vec[in1];
		Vertex& vC = objH.vec[in2];

		float alphaD = (1.0f - vB.pos.z) / (vA.pos.z - vB.pos.z);
		objH.vec.emplace_back(vB * (1 - alphaD) + vA * alphaD);
		int iD = objH.vec.size() - 1;

		float alphaE = (1.0f - vC.pos.z) / (vA.pos.z - vC.pos.z);
		objH.vec.emplace_back(vC * (1 - alphaE) + vA * alphaE);
		int iE = objH.vec.size() - 1;

		objH.triAi.emplace_back(iD);
		objH.triBi.emplace_back(in1);
		objH.triCi.emplace_back(in2);

		objH.triAi.emplace_back(iD);
		objH.triBi.emplace_back(iE);
		objH.triCi.emplace_back(in2);
	}

	void ClipTriangle(int index) {
		int& iA = objH.triAi[index];
		int& iB = objH.triBi[index];
		int& iC = objH.triCi[index];

		Vertex& vA = objH.vec[iA];
		Vertex& vB = objH.vec[iB];
		Vertex& vC = objH.vec[iC];

		int inVecs[3] = { -1, -1, -1 };
		int outVecs[3] = { -1, -1, -1 };
		int inCount = 0;
		int outCount = 0;

		// vA
		if (vA.pos.z < 1) {
			inVecs[inCount] = iA;
			inCount++;
		}
		else {
			outVecs[outCount] = iA;
			outCount++;
		}

		// vB
		if (vB.pos.z < 1) {
			inVecs[inCount] = iB;
			inCount++;
		}
		else {
			outVecs[outCount] = iB;
			outCount++;
		}

		// vC
		if (vC.pos.z < 1) {
			inVecs[inCount] = iC;
			inCount++;
		}
		else {
			outVecs[outCount] = iC;
			outCount++;
		}

		// Perform Clipping Judgements
		if (inCount == 3) {
			return;
		}
		if (inCount == 0) {
			iA = -1; iB = -1; iC = -1;
			return;
		}
		if (inCount == 1) {
			ClipOneIn(inVecs[0], outVecs[0], outVecs[1]);
			iA = -1; iB = -1; iC = -1;
			return;
		}
		if (outCount == 1) {
			ClipOneOut(outVecs[0], inVecs[0], inVecs[1]);
			iA = -1; iB = -1; iC = -1;
			return;
		}
		return;
	}
};


#endif
