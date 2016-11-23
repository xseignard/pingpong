#include "Gui.h"
#include "ofxPS3EyeGrabber.h"

using namespace ofxCv;
using namespace cv;

void Gui::setup() {
	// camera setup
	cam.setGrabber(std::make_shared<ofxPS3EyeGrabber>());
	cam.setDesiredFrameRate(60);
	cam.setup(640, 480);
	cam.getGrabber<ofxPS3EyeGrabber>()->setAutogain(true);
	cam.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(true);

	// previous ball values
	prevX = 0.0;
	prevY = 0.0;

	// ping pong ball color
	targetColor = ofColor(193, 110, 133);
	// threshold
	threshold = 15.0;
	// min and max area
	minArea = 10.0;
	maxArea = 150.0;
	// how many frames without seeing the object
	persistence = 30; // e.g. 0.5 seconds, since the camera is 60 fps
	// how many pixels the object can move between frames
	maxDistance = 50;

	// opencv setup
	contourFinder.setMinAreaRadius(minArea);
	contourFinder.setMaxAreaRadius(maxArea);
	contourFinder.setThreshold(threshold);
	// wait for half a frame before forgetting something
	contourFinder.getTracker().setPersistence(persistence);
	// an object can move up to 32 pixels per frame
	contourFinder.getTracker().setMaximumDistance(maxDistance);

	// osc messaging
	sender.setup(HOST, PORT);

	// gui setup
	guiSetup();
}

void Gui::update() {
	cam.update();
	if(cam.isFrameNew()) {
		ps3Fps->setText(ofToString(cam.getGrabber<ofxPS3EyeGrabber>()->getActualFPS()));
		// blur the image for better tracking
		blur(cam, 10);
		// setup the finder/tracker with updated values from gui
		finderSetup();
		contourFinder.findContours(cam);
	}
}

void Gui::draw() {
	ofSetColor(255);
	cam.draw(0, 0);

	int n = contourFinder.size();
	if (n >= 1) {
		ofSetColor(red);
		float circleRadius;
		ofVec2f circleCenter = toOf(contourFinder.getMinEnclosingCircle(0, circleRadius));
		if (circleCenter.x != prevX || circleCenter.y != prevY) {
			prevX = circleCenter.x;
			prevY = circleCenter.y;
			// ofLog(OF_LOG_NOTICE, "x: " + ofToString(prevX) + ", y: " + ofToString(prevY));
			// sendOsc(circleCenter, circleRadius);
		}
		ofDrawCircle(circleCenter, circleRadius);
		ofSetColor(black);
		ofDrawBitmapString(ofToString(circleRadius), circleCenter.x, circleCenter.y);
	}
}

void Gui::mousePressed(int x, int y, int button) {
	if (x <= 640) {
		targetColor = cam.getPixels().getColor(x, y);
		colorPicker->setColor(targetColor);
	}
}

void Gui::sendOsc(ofVec2f center, float radius) {
	ofxOscMessage m;
	m.setAddress("/ball/position");
	m.addFloatArg(ofMap(center.x, 0, 640, 0.f, 1.f, true));
	m.addFloatArg(ofMap(center.y, 0, 480, 0.f, 1.f, true));
	m.addFloatArg(ofMap(radius, 10, 150, 0.f, 1.f, true));
	sender.sendMessage(m, false);
}

void Gui::finderSetup() {
	// set the color we want to track
	contourFinder.setTargetColor(targetColor, TRACK_COLOR_HSV);
	// set the threshold of color difference
	contourFinder.setThreshold(threshold);
	// set the minimum radius of the tracked color
	contourFinder.setMinAreaRadius(minArea);
	// set the maximum radius of the tracked color
	contourFinder.setMaxAreaRadius(maxArea);
	// wait for some frames before forgetting the tracked object
	contourFinder.getTracker().setPersistence(persistence);
	// an object can move up to some pixels per frame
	contourFinder.getTracker().setMaximumDistance(maxDistance);
}

void Gui::guiSetup() {
	// gui stuff
	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	// threshold
	thresholdSlider = gui->addSlider("Threshold", 0, 255);
	thresholdSlider->setValue(threshold);
	// min area
	minAreaSlider = gui->addSlider("Min Area", 1, 100);
	minAreaSlider->setValue(minArea);
	// max area
	maxAreaSlider = gui->addSlider("Max Area", 1, 500);
	maxAreaSlider->setValue(maxArea);
	// persistence
	persistenceSlider = gui->addSlider("Persistence", 1, 180);
	persistenceSlider->setValue(persistence);
	// max distance
	maxDistanceSlider = gui->addSlider("Max Distance", 1, 300);
	maxDistanceSlider->setValue(maxDistance);
	// color picker
	colorPicker = gui->addColorPicker("Tracked color", targetColor);
	// track color
	trackColor = gui->addToggle("Track color", true);
	// track mouse
	trackMouse = gui->addToggle("Track mouse", false);
	// app fps
	gui->addFRM();
	// ps3 eye fps
	ps3Fps = gui->addTextInput("PS3 Eye FPS", "");
	// event handlers
	gui->onSliderEvent(this, &Gui::onSliderEvent);
	gui->onColorPickerEvent(this, &Gui::onColorPickerEvent);
	gui->onToggleEvent(this, &Gui::onToggleEvent);
}

void Gui::onSliderEvent(ofxDatGuiSliderEvent e) {
	if (e.target->is("Threshold")) threshold = e.value;
	else if (e.target->is("Min Area")) minArea = e.value;
	else if(e.target->is("Max Area")) maxArea = e.value;
	else if (e.target->is("Persistence")) persistence = e.value;
	else if(e.target->is("Max Distance")) maxDistance = e.value;
}

void Gui::onColorPickerEvent(ofxDatGuiColorPickerEvent e) {
	targetColor = e.color;
}

void Gui::onToggleEvent(ofxDatGuiToggleEvent e) {
	if (e.target->is("Track color")) {
		if (e.checked) trackMouse->setChecked(false);
		else trackMouse->setChecked(true);
	}
	else if (e.target->is("Track mouse")) {
		if (e.checked) trackColor->setChecked(false);
		else trackColor->setChecked(true);
	}
}
