#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostGlitch.h"
#include "Sequence.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		
		ofFbo			myFbo;
		ofxPostGlitch	myGlitch;

		vector<Sequence*>	sequences;
		int					current;
		
		int		millis;
		float	velocity; //[0,1]

		int frameCount;
		
		void	changeSequence();
		void	nextFrame();
		void	resetGlitch();


		//serial

		ofSerial	serial;
		string		buffer;
		string		lastBuffer;

		void onReceiveSerial(string data);


		//gui

		bool			showGui;
		ofxPanel		gui;
		
		ofxFloatSlider	secondsToChangeSequence;
		ofxFloatSlider	velocityToColor;
		ofxIntSlider	framesPerColor;
		ofxFloatSlider	velocityToGlitch;
};
