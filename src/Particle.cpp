#include "Particle.h"

//------------------------------------------------------------------
Particle::Particle(){}

//------------------------------------------------------------------
void Particle::reset() {
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	frc   = ofPoint(0,0,0);
	scale = ofRandom(0.5, 1.0);
	drag  = ofRandom(0.95, 0.998);
	rotation = ofRandom(0, 180);
}

//------------------------------------------------------------------
void Particle::update(int posX, int posY) {

	ofPoint attractPt(posX, posY);
	frc = attractPt - pos;
	//let get the distance and only repel points close to the mouse
	float dist = frc.length();
	frc.normalize();
	vel *= drag;
	if (dist < 500) {
		vel += -frc * 2; //notice the frc is negative
	}
	else {
		//if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
		frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
		frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
		vel += frc * 0.04;
	}


	// update particle position
	pos += vel;

	// keep particle on screen
	if (pos.x > ofGetWidth()) {
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}
	else if (pos.x < 0) {
		pos.x = 0;
		vel.x *= -1.0;
	}

	if (pos.y > ofGetHeight()) {
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if (pos.y < 0) {
		pos.y = 0;
		vel.y *= -1.0;
	}
}

//------------------------------------------------------------------
void Particle::draw(ofImage img) {
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofRotate(rotation);
	img.draw(0, 0);
	ofPopMatrix();
}
