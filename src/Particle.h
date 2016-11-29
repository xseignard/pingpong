#pragma once
#include "ofMain.h"

class Particle {

	public:
		Particle();

		void reset();
		void update(int posX, int posY);
		void draw(ofImage img);

		ofPoint pos;
		ofPoint vel;
		ofPoint frc;

		float drag;
		float uniqueVal;
		float scale;
		float rotation;
};
