//
//  soundanalysis.cpp
//  audio_visuals
//
//  Created by Brian McGee on 10/2/18.
//

#include "soundanalysis.h"

FFTVis::FFTVis() {
	
}

void FFTVis::setup(){
	//nBandsToGet = 128;
	visible = false;

	//load sound
	ofFileDialogResult result = ofSystemLoadDialog();
	if (result.bSuccess) {
		song.load(result.getPath());
		cout << result.getPath();
		//song.load("coldblood.mp3");
		
		//soundstreamsetup
		ofSoundStreamSettings soundSettings;
		soundSettings.numInputChannels = 0;
		soundSettings.numOutputChannels = 2;
		soundSettings.sampleRate = song.getSoundFile().getSampleRate();
		soundSettings.bufferSize = 512;
		soundSettings.numBuffers = 1;
		stream.setup(soundSettings); //stream setup
		
		song.connectTo(output);
		stream.setOutput(output);
		
		song.play();
		
		fft2.setup(soundSettings.bufferSize);
		//ff2.setInput(stream);
	}

}

void FFTVis::update() {
	//song.setVolume(1);

	float * val = ofSoundGetSpectrum(nBandsToGet); 	//get 128 values of fft
	
	for (int i=0; i < nBandsToGet; i++) {
		//let vals sink to zero
		fftSmoothed[i] *= .85f;
		//get smoothed or incoming;
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
		
		//let vals sink to zero
		fftFall[i] *= .92f;
		//get smoothed or incoming;
		if (fftFall[i] < val[i]) fftFall[i] = val[i];
		
	}
	//ofSoundUpdate();
}

void FFTVis::draw() {
	ofPushMatrix();
	ofTranslate(16,16);
	ofSetColor(255);
	ofDrawBitmapString("freq domain", 0, 0);
	
	plot(fft2.getBins(), 128);
	ofPopMatrix();
	
	
	ofSetColor(100);
	ofDrawBitmapString((int)ofGetFrameRate(), 10, 20);
	ofDrawBitmapString("p for play", 10, 30);
	ofDrawBitmapString("v for viz", 10, 40);
	
	if (visible) {
		float width = (float)(ofGetWidth() / nBandsToGet);
		for (int i=0; i < nBandsToGet; i++) {
			ofColor c;
			c.setHsb(ofMap(i, 0, nBandsToGet, 0, 255), 150, 255);
			ofSetColor(c);
			float amp = fftSmoothed[i];
			int h = ofMap(amp, 0, 1, 0, (ofGetHeight()/2));
			ofDrawRectangle(i*width,ofGetHeight(),width,-(h));
			
			float h2 = ofMap(fftFall[i], 0, 1, 0, (ofGetHeight()/2));
			ofDrawRectangle(i*width,((ofGetHeight()-h2)+2),width,-2);
		}
	} else { return; }

	
}

void FFTVis::plot(vector<float>& buffer, float scale) {
	ofNoFill();
	int n = MIN(1024, buffer.size());
	ofDrawRectangle(0, 0, n, scale);
	ofPushMatrix();
	ofTranslate(0, scale);
	ofScale(1, -scale);
	ofBeginShape();
	for (int i = 0; i < n; i++) {
		ofVertex(i, buffer[i]);
	}
	ofEndShape();
	ofPopMatrix();
}

