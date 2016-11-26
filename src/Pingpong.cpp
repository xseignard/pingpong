#include "Pingpong.h"

//--------------------------------------------------------------
void Pingpong::setup() {
	ofHideCursor();
	ofSetVerticalSync(true);
	ofSetBackgroundAuto(false);
	ofBackground(0);
	ofEnableSmoothing();

	setupWarp();

	timeElapsed = 0;
	step = 0;
	font.loadFont("bodoni.ttf", 48);
	lemap.load("lemap.jpg");
	// pictos setup
	for (int i = 0; i < NUMBER_OF_PICTOS; i++) {
		pictos[i].load("pictos/picto_" + ofToString(i) + ".png");
	}
	currentPicto = pictos[(int) ofRandom(0, 8)];
	// lines setup
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		lines[i].setup();
	}
	// points for line setup
	points.assign(50, ofPoint())
	// particles setup
	particles.assign(20, Particle());
	for (int i = 0; i < particles.size(); i++) {
		particles[i].reset();
	}
}

//--------------------------------------------------------------
void Pingpong::setupWarp() {
	warpFbo.allocate(WIDTH, HEIGHT, GL_LUMINANCE);
	warper.setSourceRect(ofRectangle(0, 0, WIDTH, HEIGHT));
	warper.setTopLeftCornerPosition(ofPoint(0, 0));
	warper.setTopRightCornerPosition(ofPoint(WIDTH, 0));
	warper.setBottomLeftCornerPosition(ofPoint(0, HEIGHT));
	warper.setBottomRightCornerPosition(ofPoint(WIDTH, HEIGHT));
	warper.setup();
	warper.load();
}

//--------------------------------------------------------------
void Pingpong::update() {
	// update position from camera
	if (gui->trackColor->getChecked()) {
		prevPosX = posX;
		prevPosY = posY;
		posX = ofMap(gui->prevX, 0, CAM_WIDTH, 0, WIDTH);
		posY = ofMap(gui->prevY, 0, CAM_HEIGHT, 0, HEIGHT);
	}
	// keep track of time
	int currentTime = ofGetElapsedTimeMillis();
	if (currentTime - timeElapsed > INTERVAL) {
		step++;
		// prevent overflow
		if (step >= NUMBER_OF_SKETCHES) step = 0;
		// clear the background
		ofBackground(0);
		// clear the background inside the warp fbo
		warpFbo.begin();
			ofSetColor(255);
			ofDrawRectangle(0, 0, WIDTH, HEIGHT);
		warpFbo.end();
		timeElapsed = currentTime;
		// specific updates when a scene changes
		if (step == 7 || step == 8) currentPicto = pictos[(int) ofRandom(0, 8)];
	}
}

//--------------------------------------------------------------
void Pingpong::draw() {
	warpFbo.begin();
	{
		switch (6) {
			case 0:
				eyemap();
				break;
			case 1:
				flipflop();
				break;
			case 2:
				textmap();
				break;
			case 3:
				maskmap();
				break;
			case 4:
				linemap();
				break;
			case 5:
				circlesmap();
				break;
			case 6:
				linesmap();
				break;
			case 7:
				pictomap();
				break;
			case 8:
				particlesmap();
				break;
		}
	}
	warpFbo.end();

	// paint it white
	ofSetColor(255);
	// transform image to match the warp
	ofMatrix4x4 mat = warper.getMatrix();
	ofPushMatrix();
	ofMultMatrix(mat);
	warpFbo.draw(0, 0);
	ofPopMatrix();

	// draw warp handlers
	drawWarpHandlers();
}

//--------------------------------------------------------------
void Pingpong::drawWarpHandlers() {
	ofSetColor(red);
	warper.drawQuadOutline();
	warper.drawCorners();
	warper.drawHighlightedCorner();
	warper.drawSelectedCorner();
}

//--------------------------------------------------------------
void Pingpong::exit() {
	warper.save();
}

//--------------------------------------------------------------
void Pingpong::particlesmap() {
	ofBackground(255);
	for(int i = 0; i < particles.size(); i++) {
		particles[i].update(posX, posY);
		particles[i].draw(currentPicto);
	}
}

//--------------------------------------------------------------
void Pingpong::pictomap() {
	ofBackground(255);
	ofPushMatrix();
	ofTranslate(posX, posY);
	ofRotate((sin(ofGetFrameNum() * 0.02) * 0.5 + 0.5) * 360);
	currentPicto.draw(-currentPicto.getWidth()/2, -currentPicto.getHeight()/2);
	ofPopMatrix();
}

//--------------------------------------------------------------
void Pingpong::circlesmap() {
	int d = ofMap((sin(ofGetFrameNum() * 0.1) * 0.5 + 0.5), 0, 1, 100, 200);
	ofSetColor(black);
	ofDrawEllipse(posX, posY, d, d);
	ofSetColor(255);
	ofDrawEllipse(posX, posY, d - 5, d - 5);
}

//--------------------------------------------------------------
void Pingpong::linesmap() {
	// ofSetColor(black);
	// ofSetLineWidth(15);
	// ofDrawLine(prevPosX, prevPosY, posX, posY);

}

//--------------------------------------------------------------
void Pingpong::eyemap() {
	ofBackground(255);
	for (int x = 60; x < 1900; x = x+100) {
		for (int y = 90; y < 1000; y = y+100) {
			//draw a lot of eyes
			ofSetColor(0);
			ofDrawEllipse(x, y, 60, 60);
			//Eye balls
			int pX = (int) ofMap(posX, 0, WIDTH, -10, 10);
			int pY = (int) ofMap(posY, 0, HEIGHT, -10, 10);
			//to limit posX and posY
			ofSetColor(255);
			ofDrawEllipse(x + pX, y + pY, 20, 20);
			//Iris
		}
	}
}

//--------------------------------------------------------------
void Pingpong::flipflop() {
	ofBackground(255);
	ofSetColor(0);
	if ((posX <= WIDTH / 2) && (posY <= HEIGHT / 2)) {
		ofDrawRectangle(0, 0, WIDTH / 2, HEIGHT / 2); // Upper-left
	}
	else if ((posX <= WIDTH / 2) && (posY > HEIGHT / 2)) {
		ofDrawRectangle(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2); // Lower-left
	}
	else if ((posX > WIDTH / 2) && (posY < HEIGHT / 2)) {
		ofDrawRectangle(WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2); // Upper-right
	}
	else {
		ofDrawRectangle(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2); // Lower-right
	}
}

//--------------------------------------------------------------
void Pingpong::textmap() {
	// fade previous text
	ofSetColor(255, 255, 255, 20);
	ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	string s = "LE MAP";
	ofRectangle r = font.getStringBoundingBox(s, 0, 0);
	ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f));
	// translate coords system so the center of the text is the (0, 0) coord
	ofPushMatrix();
	ofTranslate(posX, posY);
	// -10° to 10°
	ofRotate(ofRandomf() * 10);
	ofSetColor(0);
	// textSize(random(100));
	font.drawString(s, offset.x, offset.y);
	ofPopMatrix();
}

//--------------------------------------------------------------
void Pingpong::maskmap() {
	lemap.drawSubsection(posX, posY, 200, 200, posX, posY);
}

//--------------------------------------------------------------
void Pingpong::linemap() {
	// fade previous text
	ofSetColor(255, 255, 255, 20);
	ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		lines[i].draw(posX, posY);
	}
}

//--------------------------------------------------------------
void Pingpong::keyPressed(int key) {
	if (key == ' ') ofToggleFullscreen();
	else if (key == 's') warper.toggleShow();
}

//--------------------------------------------------------------
void Pingpong::keyReleased(int key) {

}

//--------------------------------------------------------------
void Pingpong::mouseMoved(int x, int y) {
	if (gui->trackMouse->getChecked()) {
		prevPosX = posX;
		prevPosY = posY;
		posX = x;
		posY = y;
	}
}

//--------------------------------------------------------------
void Pingpong::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void Pingpong::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void Pingpong::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void Pingpong::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void Pingpong::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void Pingpong::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void Pingpong::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void Pingpong::dragEvent(ofDragInfo dragInfo) {

}
