#pragma once

#include "ofMain.h"
//#include "ofxGui.h"
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
		

		vector<Sequence*>	sequences;
		int					current;
		
		void	changeSequenceRandom();
		void	changeSequence(int newIndex);
		void	nextFrame();

		int		millisToChangeSequence;
		void	resetChangeSequenceTimer();

		ofColor color;
		int		framesToChangeColor;
		void	changeColor();

		ofFbo			myFbo;
		ofxPostGlitch	myGlitch;


		//serial

		ofSerial	serial;
		string		buffer;
		string		lastBuffer;

		void onReceiveSerial(string data);


		//gui

		//ofxPanel gui;

		/*
		ofxFloatSlider radius;
		ofxColorSlider color;
		ofxVec2Slider center;
		ofxIntSlider circleResolution;
		ofxToggle filled;
		ofxButton twoCircles;
		ofxButton ringButton;
		ofxLabel screenSize;
		*/
};
