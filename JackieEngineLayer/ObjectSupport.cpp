#include "ObjectSupport.h"

FObject::FObject() {
	;
}

void FObject::Add(const FVector4D& vec) {
	vl.push_back(vec);
}

void FObject::Translate(f32 x_, f32 y_, f32 z_){
	for(i32 i = 0; i < vl.size(); i++){
		FMatrix4D transmat = FMatrix4D::GenerateTranslationMatrix(-x_, -y_, -z_);
		vl[i] = vl[i] * transmat;
	}
}

void FObject::Rotate(f32 x_, f32 y_, f32 z_){
	for(i32 i = 0; i < vl.size(); i++){
		FMatrix4D rotmat = FMatrix4D::GenerateRotationMatrix(x_, y_, z_);
		vl[i] = vl[i] * rotmat;
	}
}

string FObject::ToString(){
	stringstream ss;
	ss << "FObject: " << endl;

	for(i32 i = 0; i < vl.size(); i++){
		ss << tmpVl[i].ToString();
	}

	return ss.str();
}
