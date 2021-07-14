#include "ObjectSupport.h"

FObject::FObject() {
	vl.clear();
	tmpVl.clear();
	il.clear();
}

FObject::FObject(string textureFileName) {
	texture.LoadFromBMP(textureFileName);
}

void FObject::Add(const FVectorTex& vec) {
	FVectorTex& veccpy = *(new FVectorTex(vec));
	vl.push_back(veccpy);
}

void FObject::Add(i32 index1, i32 index2, i32 index3){
	il.push_back(index1);
	il.push_back(index2);
	il.push_back(index3);
}

void FObject::Translate(f32 x_, f32 y_, f32 z_){
	for(i32 i = 0; i < vl.size(); i++){
		FMatrix4D transmat = FMatrix4D::GenerateTranslationMatrix(-x_, -y_, -z_);
		vl[i].pos = vl[i].pos * transmat;
	}
}

void FObject::Rotate(f32 x_, f32 y_, f32 z_){
	for(i32 i = 0; i < vl.size(); i++){
		FMatrix4D rotmat = FMatrix4D::GenerateRotationMatrix(x_, y_, z_);
		vl[i].pos = vl[i].pos * rotmat;
	}
}

string FObject::ToString(){
	stringstream ss;
	ss << "FObject: Vector=" << vl.size() << "; Index=" << il.size() << endl;

	for(i32 i = 0; i < vl.size(); i++){
		ss << tmpVl[i].pos.ToString();
	}

	for(i32 i = 0; i < vl.size(); i++){
		ss << tmpVl[i].tex.ToString();
	}

	return ss.str();
}
