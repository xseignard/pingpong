#include "Line.h"

Line::Line(){}

void Line::setup(){
	float s1 = ofRandomWidth();
	float s2 = ofRandomWidth();
	float t = ofRandomWidth();
	if (ofRandom(1) < 0.5) {
		start = ofVec2f(s1, t);
		end = ofVec2f(s2, t);
	}
	else {
		start = ofVec2f(t, s1);
		end = ofVec2f(t, s2);
	}
	center = (start + end) / 2;
	offset = ofRandom(5);
}

void Line::draw(int mouseX, int mouseY){
	ofVec2f mouse = ofVec2f(mouseX, mouseY);
	float dist = mouse.distance(center);
	if (dist < 100) {
		ofSetLineWidth(2);
		float alpha = fabs(ofMap(sin(ofGetFrameNum() * 0.1 + offset), 0, 1, 0, 255));
		ofSetColor(0, 0, 0, alpha);
		ofDrawLine(start.x, start.y, end.x, end.y);
	}
}
