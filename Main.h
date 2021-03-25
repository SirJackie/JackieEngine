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

	// Camera4D Testing
	ss << "Camera4D Testing: \n";
	Camera4D(
		0.0f, 0.0f, 4.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.Width, fb.Height
	);

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
