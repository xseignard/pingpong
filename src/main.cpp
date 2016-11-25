#include "ofMain.h"
#include "Pingpong.h"
#include "Gui.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;

	settings.width = 1920;
	settings.height = 1080;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = true;
	settings.windowMode = OF_WINDOW;
	settings.decorated = true;
	settings.title = "Ping Pong";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 910;
	settings.height = 720;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = false;
	settings.windowMode = OF_WINDOW;
	settings.decorated = true;
	settings.title = "GUI";
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<Pingpong> mainApp(new Pingpong);
	shared_ptr<Gui> gui(new Gui);
	mainApp->gui = gui;

	ofRunApp(mainWindow, mainApp);
	ofRunApp(guiWindow, gui);
	ofRunMainLoop();
	// ofSetupOpenGL(WIDTH, HEIGHT, OF_GAME_MODE);
	// ofRunApp(new Pingpong());
}
