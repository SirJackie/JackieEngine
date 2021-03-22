#include "MathSupport.h"

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
