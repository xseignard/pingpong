#pragma once

#include "ofMain.h"
#include "const.h"
#include "ofxCv.h"
#include "ofxDatGui.h"
#include "ofxOsc.h"

class Gui : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
		void sendOsc(ofVec2f center, float radius);
		void finderSetup();
		void guiSetup();

		// stored values
		float prevX;
		float prevY;
		ofColor targetColor;
		float threshold;
		float minArea;
		float maxArea;
		int persistence;
		float maxDistance;

		// video capture stuff
		ofVideoGrabber cam;
		ofxCv::ContourFinder contourFinder;

		// osc stuff
		ofxOscSender sender;

		// gui stuff
		ofxDatGui* gui;
		ofxDatGuiColorPicker* colorPicker;
		ofxDatGuiSlider* thresholdSlider;
		ofxDatGuiSlider* minAreaSlider;
		ofxDatGuiSlider* maxAreaSlider;
		ofxDatGuiSlider* persistenceSlider;
		ofxDatGuiSlider* maxDistanceSlider;
		ofxDatGuiToggle* trackColor;
		ofxDatGuiToggle* trackMouse;
		ofxDatGuiTextInput* ps3Fps;
		void onSliderEvent(ofxDatGuiSliderEvent e);
		void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
		void onToggleEvent(ofxDatGuiToggleEvent e);
};
