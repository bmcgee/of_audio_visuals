//
//  soundanalysis.hpp
//  audio_visuals
//
//  Created by Brian McGee on 10/2/18.
//

#ifndef soundanalysis_hpp
#define soundanalysis_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxEasyFft.h"
#include "ofxSoundPlayerObject.h"



class FFTVis {
	public:
	
	void setup();
	void draw();
	void update();
	
	void plot();
	
	//ofSoundPlayer song;
	ofSoundStream stream;
	ofxSoundOutput output;
	
	ofxSoundPlayerObject song;
	
	
	
	
	static constexpr size_t nBandsToGet = 128;
	std::array<float, nBandsToGet> fftSmoothed{{0}};
	std::array<float, nBandsToGet> fftFall{{0}};

	bool visible;

	void plot(vector<float>& bufffer, float scale);
	ofxEasyFft fft2;

	FFTVis();
};

#endif /* soundanalysis_hpp */
