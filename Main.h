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
	ss << ";";
	ss << cosd(60.0f);
	ss << ";";
	ss << tand(45.0f);
	ss << ";";

	ss << asind(0.5f);
	ss << ";";
	ss << acosd(0.5f);
	ss << ";";
	ss << atand(1.0f);
	ss << ";";

	ss << "\n";



	// Clamp Testing
	ss << "Clamp Testing: ";

	ss << clamp(3, 4, 5);
	ss << clamp(3, 2, 5);
	ss << clamp(3, 6, 5);


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
