#ifndef _LINE
#define _LINE

#include "ofMain.h"

class Line {

	public:
		Line();
		void setup();
		void draw(int mouseX, int mouseY);

	private:
		ofVec2f start;
		ofVec2f end;
		ofVec2f center;
		float offset;
};
#endif
