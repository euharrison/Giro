#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	buffer = "";
	serial.setup(0, 9600);
	
	TCP.setup(11999);
	TCP.setMessageDelimiter("\n");
}

//--------------------------------------------------------------
void ofApp::update(){

	//serial
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

}

//--------------------------------------------------------------
void ofApp::onReceiveSerial(string data) {

	cout << data << endl;

	for(int i = 0; i < TCP.getLastID(); i++){
		if( !TCP.isClientConnected(i) )continue;
	
		TCP.send(i, data);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
