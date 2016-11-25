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
		void checkOsc();
		void finderSetup();
		void cameraSetup();
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
		float offsetX;
		float offsetY;

		int gain;
		int exposure;
		int sharpness;
		int contrast;
		int brightness;
		int hue;
		int redBalance;
		int blueBalance;
		int greenBalance;

		ofSoundPlayer pan;
		ofSoundPlayer boum;

		// video capture stuff
		ofVideoGrabber cam;
		ofxCv::ContourFinder contourFinder;

		// osc stuff
		ofxOscSender sender;
		ofxOscReceiver receiver;

		// gui stuff
		ofxDatGui* gui;
		ofxDatGuiColorPicker* colorPicker;
		ofxDatGuiSlider* thresholdSlider;
		ofxDatGuiSlider* minAreaSlider;
		ofxDatGuiSlider* maxAreaSlider;
		ofxDatGuiSlider* persistenceSlider;
		ofxDatGuiSlider* maxDistanceSlider;
		ofxDatGuiSlider* offsetXSlider;
		ofxDatGuiSlider* offsetYSlider;
		ofxDatGuiToggle* trackColor;
		ofxDatGuiToggle* trackMouse;
		ofxDatGuiSlider* gainSlider;
		ofxDatGuiSlider* exposureSlider;
		ofxDatGuiSlider* sharpnessSlider;
		ofxDatGuiSlider* contrastSlider;
		ofxDatGuiSlider* brightnessSlider;
		ofxDatGuiSlider* hueSlider;
		ofxDatGuiSlider* redBalanceSlider;
		ofxDatGuiSlider* blueBalanceSlider;
		ofxDatGuiSlider* greenBalanceSlider;
		ofxDatGuiTextInput* ps3Fps;
		void onSliderEvent(ofxDatGuiSliderEvent e);
		void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
		void onToggleEvent(ofxDatGuiToggleEvent e);
};
