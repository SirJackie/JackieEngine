#include "MathSupport.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

int min3(int a, int b, int c) {
	int min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

int max3(int a, int b, int c) {
	int max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
}

float fmin3(float a, float b, float c) {
	float min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

float fmax3(float a, float b, float c) {
	float max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
}

Vector4D::Vector4D(float x_, float y_, float z_, float w_) {
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

string Vector4D::str(){
	stringstream ss;

	ss << "Vector4D[";
	ss << this->x;
	ss << ", ";
	ss << this->y;
	ss << ", ";
	ss << this->z;
	ss << ", ";
	ss << this->w;
	ss << "]";

	return ss.str();
}
