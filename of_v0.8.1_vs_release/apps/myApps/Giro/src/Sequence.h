#pragma once

#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class Sequence {

public:
	
	ofxThreadedImageLoader loader;
	vector<ofImage> frames;
	int currentFrame;
	int totalFrames;

	Sequence(string folder, int _totalFrames) {
		currentFrame = 0;
		totalFrames = _totalFrames;
		frames.resize(totalFrames);
		for (int i = 0; i < totalFrames; i++){
			loader.loadFromDisk(frames[i], folder+"/"+ofToString(i+1)+".jpg");
		}
	}

	void update() {
		currentFrame++;
		if (currentFrame >= totalFrames) {
			currentFrame = 0;
		}
	}

	void draw(float x, float y) {
		frames[currentFrame].draw(x,y);
	}
		
};