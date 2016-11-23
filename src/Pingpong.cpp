#include "Pingpong.h"

//--------------------------------------------------------------
void Pingpong::setup(){
	ofHideCursor();
	ofSetVerticalSync(true);
	ofSetBackgroundAuto(false);
	ofBackground(0);
	timeElapsed = 0;
	step = 0;
	font.loadFont("bodoni.ttf", 48);
	lemap.load("lemap.jpg");
	fbo.allocate(WIDTH, HEIGHT, GL_LUMINANCE);
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		lines[i].setup();
	}
}

//--------------------------------------------------------------
void Pingpong::update(){
	if (gui->trackColor->getChecked()) {
		// update position from camera
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
		// clear the fbo before using back the maskmap
		if (step == 3) {
			fbo.begin();
				ofSetColor(0);
				ofDrawRectangle(0, 0, WIDTH, HEIGHT);
			fbo.end();
		}
		timeElapsed = currentTime;
	}
}

//--------------------------------------------------------------
void Pingpong::draw(){
	switch (step) {
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
	}
}

//--------------------------------------------------------------
void Pingpong::eyemap(){
	ofBackground(0);
	for (int x = 60; x < 1900; x = x+100) {
		for (int y = 90; y < 1000; y = y+100) {
			//draw a lot of eyes
			ofSetColor(255);
			ofDrawEllipse(x, y, 60, 60);
			//Eye balls
			int pX = (int) ofMap(posX, 0, WIDTH, -10, 10);
			int pY = (int) ofMap(posY, 0, HEIGHT, -10, 10);
			//to limit posX and posY
			ofSetColor(0);
			ofDrawEllipse(x + pX, y + pY, 20, 20);
			//Iris
		}
	}
}

//--------------------------------------------------------------
void Pingpong::flipflop(){
	ofBackground(0);
	ofSetColor(255);
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
void Pingpong::textmap(){
	// fade previous text
	ofSetColor(0, 0, 0, 20);
	ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	string s = "LE MAP";
	ofRectangle r = font.getStringBoundingBox(s, 0, 0);
	ofVec2f offset = ofVec2f(floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f));
	// translate coords system so the center of the text is the (0, 0) coord
	ofPushMatrix();
	ofTranslate(posX, posY);
	ofRotate(ofRandomf() * 10); // -10° to 10°
	ofSetColor(255);
	// textSize(random(100));
	font.drawString(s, offset.x, offset.y);
	ofPopMatrix();
}

//--------------------------------------------------------------
void Pingpong::maskmap(){
	// update the draw in the buffer
	fbo.begin();
		ofDrawEllipse(posX, posY, 200, 200);
	fbo.end();
	// use the buffered drawing as a mask
	lemap.getTexture().setAlphaMask(fbo.getTexture());
	lemap.draw(0, 0);
}

//--------------------------------------------------------------
void Pingpong::linemap(){
	// fade previous text
	ofSetColor(0, 0, 0, 20);
	ofDrawRectangle(0, 0, WIDTH, HEIGHT);
	for (int i = 0; i < NUMBER_OF_LINES; i++) {
		lines[i].draw(posX, posY);
	}
}

//--------------------------------------------------------------
void Pingpong::keyPressed(int key){
	if (key == ' ') ofToggleFullscreen();
}

//--------------------------------------------------------------
void Pingpong::keyReleased(int key){

}

//--------------------------------------------------------------
void Pingpong::mouseMoved(int x, int y ){
	if (gui->trackMouse->getChecked()) {
		posX = x;
		posY = y;
	}
}

//--------------------------------------------------------------
void Pingpong::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Pingpong::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Pingpong::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Pingpong::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Pingpong::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Pingpong::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Pingpong::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Pingpong::dragEvent(ofDragInfo dragInfo){

}
