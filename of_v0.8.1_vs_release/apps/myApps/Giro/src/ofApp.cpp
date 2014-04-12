#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(0);
	ofSetFrameRate(60);
	//ofHideCursor();
	//ofToggleFullscreen();

	myFbo.allocate(1024, 768);
	myGlitch.setup(&myFbo);

	//disable all initial effects
	myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
	myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
	myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
	myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
	myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
	myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
	myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
	myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
	myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
	myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
	
	myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
	myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
	

	//gui.setup(); // most of the time you don't need a name
	/*
	gui.add(filled.setup("fill", true));
	gui.add(radius.setup( "radius", 140, 10, 300 ));
	gui.add(circleResolution.setup("circle res", 5, 3, 90));
	gui.add(twoCircles.setup("two circles"));
	gui.add(ringButton.setup("ring"));
	gui.add(screenSize.setup("screen size", ""));
	*/

	buffer = "";
	serial.setup(0, 9600);
	
	sequences.push_back(new Sequence("bison", 16));
	sequences.push_back(new Sequence("cachorro", 12));
	sequences.push_back(new Sequence("macaco", 19));
	sequences.push_back(new Sequence("op_circle", 15));
	sequences.push_back(new Sequence("op_cylinder", 8));
	sequences.push_back(new Sequence("op_triangle", 15));

			
	changeSequence(0);
	
	resetChangeSequenceTimer();

	framesToChangeColor = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

	int byte = serial.readByte();
	while (byte != OF_SERIAL_NO_DATA && byte != OF_SERIAL_ERROR && byte != 0) {
		switch(byte) {
			case '\n':
			case '\r':
				if (buffer != "") {
					onReceiveSerial(buffer);
					buffer = "";
				}
				break;
			default:
				buffer += (char)byte;
		}
		byte = serial.readByte();
	}

	if (ofGetElapsedTimeMillis() > millisToChangeSequence) {
		changeSequenceRandom();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	myFbo.begin();
		sequences[current]->draw(0,0);
	myFbo.end();

	myGlitch.generateFx();

	ofSetColor(255);
	myFbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
		case 'F':
			ofToggleFullscreen();
			break;

		case ' ':
			nextFrame();
			break;

		case 'z':
		case 'Z':
			changeSequenceRandom();
			break;
	}

	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);

	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}





//--------------------------------------------------------------
void ofApp::onReceiveSerial(string data) {
	if (lastBuffer == "0" && data == "1") {
		nextFrame();
	}
	lastBuffer = data;
}

//--------------------------------------------------------------
void ofApp::changeSequenceRandom() {
	int total = sequences.size();
	if (total > 1) {
		int newIndex;
		do {
			newIndex = int(ofRandom(total));
		} while(newIndex == current);
		changeSequence(newIndex); 
	}
}

//--------------------------------------------------------------
void ofApp::changeSequence(int newIndex) {
	current = newIndex;

	resetChangeSequenceTimer();
}

//--------------------------------------------------------------
void ofApp::nextFrame() {
	sequences[current]->update();

	resetChangeSequenceTimer();
	
	framesToChangeColor++;
	if (framesToChangeColor == 3) {
		framesToChangeColor = 0;
		changeColor();
	}

	/*
	if (ofGetElapsedTimeMillis() - millisToGlitch < 250) {
		//glitchValue += 50;
		if (glitchValue > 768/2.f) { 
			//glitchValue = 768/2.f;
		}
	} else {
		//glitchValue -= 100;
		if (glitchValue < 0) { 
			//glitchValue = 0;
		}
	}
	millisToGlitch = ofGetElapsedTimeMillis();
	*/
}

//--------------------------------------------------------------
void ofApp::resetChangeSequenceTimer() {
	millisToChangeSequence = ofGetElapsedTimeMillis() + 2000;
}

//--------------------------------------------------------------
void ofApp::changeColor() {
	switch(int(ofRandom(4))) {
		case 0:
			color.set(255,255,255);
			break;
		case 1:
			color.set(255,0,0);
			break;
		case 2:
			color.set(0,255,0);
			break;
		case 3:
			color.set(0,0,255);
			break;
	}
}