#include "ObjectSupport.h"

FObject::FObject() {
	;
}

void FObject::Add(const FVector4D& vec) {
	vl.push_back(vec);
}

string FObject::ToString(){
	stringstream ss;
	ss << "FObject: " << endl;

	for(i32 i = 0; i < vl.size(); i++){
		ss << vl[i].ToString();
	}

	return ss.str();
}
