#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "const.h"
#include "Line.h"
#include "Particle.h"
#include "Gui.h"

class Pingpong : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void gogglesmap();
		void videomap();
		void particlesmap();
		void pictomap();
		void circlesmap();
		void linesmap();
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
		void setupWarp();
		void drawWarpHandlers();

	private:
		int posX;
		int posY;
		int prevPosX;
		int prevPosY;
		uint64_t timeElapsed;
		int step;
		ofTrueTypeFont font;
		ofImage lemap;
		ofImage goggles;
		ofImage iris;
		ofImage pictos[9];
		ofImage currentPicto;
		Line lines[NUMBER_OF_LINES];
		vector <Particle> particles;

		ofFbo warpFbo;
		ofxQuadWarp warper;

		ofVideoPlayer video;

};
