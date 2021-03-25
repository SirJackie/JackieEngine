#include "./CrossBufferLayer/CrossBuffer.h"
#include "./JackieEngineLayer/JackieEngine.h"
#include <vector>
#include <sstream>
using std::vector;
using std::stringstream;


/* Define Window Class Properties */
#define WindowClassName   L"Jackie Engine Class"
#define WindowTitle       L"Jackie Engine"
#define BitmapRootAddress "..\\"


/*
** Setup()
*/

void Setup(FrameBuffer& fb, Keyboard kb, int deltaTime, vector<FrameBuffer*>& fbLoadingQueue) {
	;
}


FPSCalculator fps;

/*
** Update()
*/

void Update(FrameBuffer& fb, Keyboard kb, int deltaTime, vector<FrameBuffer*>& fbLoadingQueue) {
	fps.Count(deltaTime);
	fps.ShowOnScreen(fb);


	stringstream ss;

	// Trigonometric Function Testing
	ss << "Trigonometric Function Testing: ";

	ss << sind(30.0f);
	ss << "; ";
	ss << cosd(60.0f);
	ss << "; ";
	ss << tand(45.0f);
	ss << "; ";

	ss << asind(0.5f);
	ss << "; ";
	ss << acosd(0.5f);
	ss << "; ";
	ss << atand(1.0f);
	ss << "; ";

	ss << "\n";

	// Clamp Testing
	ss << "Clamp Testing: ";

	ss << clamp(3, 4, 5);
	ss << "; ";
	ss << clamp(3, 2, 5);
	ss << "; ";
	ss << clamp(3, 6, 5);
	ss << "; ";

	ss << fclamp(3.0f, 4.0f, 5.0f);
	ss << "; ";
	ss << fclamp(3.0f, 2.0f, 5.0f);
	ss << "; ";
	ss << fclamp(3.0f, 6.0f, 5.0f);
	ss << "; ";

	ss << "\n";

	// Min3 & Max3 Testing Testing
	ss << "Min3 & Max3 Testing: ";

	ss << min3(3, 4, 5);
	ss << "; ";
	ss << min3(5, 3, 4);
	ss << "; ";
	ss << min3(4, 5, 3);
	ss << "; ";

	ss << max3(3, 4, 5);
	ss << "; ";
	ss << max3(5, 3, 4);
	ss << "; ";
	ss << max3(4, 5, 3);
	ss << "; ";

	ss << fmin3(3.0f, 4.0f, 5.0f);
	ss << "; ";
	ss << fmin3(5.0f, 3.0f, 4.0f);
	ss << "; ";
	ss << fmin3(4.0f, 5.0f, 3.0f);
	ss << "; ";

	ss << fmax3(3.0f, 4.0f, 5.0f);
	ss << "; ";
	ss << fmax3(5.0f, 3.0f, 4.0f);
	ss << "; ";
	ss << fmax3(4.0f, 5.0f, 3.0f);
	ss << "; ";

	ss << "\n";
	ss << "\n";


	// Vector4D Testing
	ss << "Vector4D Testing: ";
	ss << "\n";

	Vector4D vec(1.0f, 2.0f, 0.0f, 2.0f);
	ss << vec.str();
	ss << "\n";

	ss << "Length Of the Vector: ";
	ss << vec.length();
	ss << "\n";

	ss << "If Normalized: ";
	ss << vec.normalized().str();
	ss << "\n";

	ss << "After vec.DevideByW(): ";
	vec.DevideByW();
	ss << vec.str();
	ss << "\n";
	ss << "\n";

	ss << "vec + vec: ";
	Vector4D vec1(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D vec2(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D vec3(1.0f, 2.0f, 3.0f, 1.0f);
	ss << (vec1 + vec2 + vec3).str();
	ss << "\n";

	ss << "vec - vec: ";
	Vector4D vec4(3.0f, 3.0f, 3.0f, 1.0f);
	Vector4D vec5(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D vec6(-1.0f, -1.0f, -1.0f, 1.0f);
	ss << (vec4 - vec5 - vec6).str();
	ss << "\n";

	ss << "vec dot vec: ";
	Vector4D vec7(1.0f, 2.0f, 3.0f, 1.0f);
	Vector4D vec8(1.0f, 2.0f, 3.0f, 1.0f);
	ss << (vec7 * vec8);
	ss << "\n";

	ss << "vec cross vec: ";
	Vector4D vec9 (1.0f, 0.0f, 0.0f, 1.0f);
	Vector4D vec10(0.0f, 0.0f, 1.0f, 1.0f);
	ss << (vec9 % vec10).str();
	ss << "\n";
	ss << "\n";


	// Matrix4D Testing
	ss << "Matrix4D Testing: \n";
	Matrix4D mat(
		 1.0f,  2.0f,  3.0f,  4.0f,
		 5.0f,  6.0f,  7.0f,  8.0f,
		 9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	);
	ss << mat.str();
	ss << mat.str();
	ss << "\n";


	fb.Draw(ss.str().c_str());
}










	//vecs[0] = CreateVector4D(-1.0, -1.0,  1.0, 1.0);
	//vecs[1] = CreateVector4D( 1.0, -1.0,  1.0, 1.0);
	//vecs[2] = CreateVector4D( 1.0,  1.0,  1.0, 1.0);
	//vecs[3] = CreateVector4D(-1.0,  1.0,  1.0, 1.0);
	//vecs[4] = CreateVector4D(-1.0, -1.0, -1.0, 1.0);
	//vecs[5] = CreateVector4D( 1.0, -1.0, -1.0, 1.0);
	//vecs[6] = CreateVector4D( 1.0,  1.0, -1.0, 1.0);
	//vecs[7] = CreateVector4D(-1.0,  1.0, -1.0, 1.0);
