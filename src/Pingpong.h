#pragma once

#include "ofMain.h"
#include "const.h"
#include "Line.h"
#include "Gui.h"

class Pingpong : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void eyemap();
		void flipflop();
		void textmap();
		void maskmap();
		void linemap();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		shared_ptr<Gui> gui;

	private:
		int posX;
		int posY;
		uint64_t timeElapsed;
		int step;
		ofTrueTypeFont font;
		ofImage lemap;
		ofFbo fbo;
		Line lines[NUMBER_OF_LINES];
};
