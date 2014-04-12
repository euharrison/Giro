#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetBackgroundColor(0);
	ofSetFrameRate(60);
	//ofHideCursor();
	//ofToggleFullscreen();

	buffer = "";
	serial.setup(0, 9600);
	
	//sequences.push_back(new Sequence("bison", 16));
	//sequences.push_back(new Sequence("cachorro", 12));
	//sequences.push_back(new Sequence("macaco", 19));
	//sequences.push_back(new Sequence("op_circle", 15));
	sequences.push_back(new Sequence("op_cylinder", 8));
	//sequences.push_back(new Sequence("op_triangle", 15));
			
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

	ofSetColor(color);

	if (glitchValue > 0) {
		sequences[current]->draw(0, glitchValue);
		sequences[current]->draw(0, glitchValue-768);
	} else {
		sequences[current]->draw(0,0);
	}
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
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
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