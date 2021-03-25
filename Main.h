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

Object4D obj;

/*
** Setup()
*/

void Setup(FrameBuffer& fb, Keyboard kb, int deltaTime, vector<FrameBuffer*>& fbLoadingQueue) {
	obj.add(Vector4D(-1.0, -1.0,  1.0, 1.0));
	obj.add(Vector4D( 1.0, -1.0,  1.0, 1.0));
	obj.add(Vector4D( 1.0,  1.0,  1.0, 1.0));
	obj.add(Vector4D(-1.0,  1.0,  1.0, 1.0));
	obj.add(Vector4D(-1.0, -1.0, -1.0, 1.0));
	obj.add(Vector4D( 1.0, -1.0, -1.0, 1.0));
	obj.add(Vector4D( 1.0,  1.0, -1.0, 1.0));
	obj.add(Vector4D(-1.0,  1.0, -1.0, 1.0));

}


FPSCalculator fps;

/*
** Update()
*/

void Update(FrameBuffer& fb, Keyboard kb, int deltaTime, vector<FrameBuffer*>& fbLoadingQueue) {
	fps.Count(deltaTime);
	fps.ShowOnScreen(fb);


	stringstream ss;
	ss << "\n";

	// Camera4D Testing
	ss << "Camera4D Testing: \n";
	Camera4D cam(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.Width, fb.Height
	);

	ss << cam.str();

	// Object4D Testing
	ss << obj.vecs.size();
	ss << "\n";
	Object4D obj2 = obj;
	cam.ProjectObject(obj2);

	for (int i = 0; i < obj2.vecs.size(); i++) {
		ss << obj2.vecs[i].str();
		ss << "\n";
		SetPixel(fb, (int)obj2.vecs[i].x, (int)obj2.vecs[i].y, CreateColor(255, 255, 255));
		
	}

	fb.Draw(ss.str().c_str());
}










