#pragma once

#include "ofMain.h"

class Sequence {

public:

	vector<ofImage> frames;
	int currentFrame;
	int totalFrames;

	Sequence(string folder, int _totalFrames) {
		currentFrame = 0;
		totalFrames = _totalFrames;
		for (int i = 0; i < totalFrames; i++){
			frames.push_back(ofImage(folder+"/"+ofToString(i+1)+".jpg"));
		}

		//frames[0].
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