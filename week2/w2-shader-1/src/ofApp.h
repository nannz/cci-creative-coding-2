#pragma once

#include "ofMain.h"
#include "ofxShader.h"
#include "ofxShaderFilter.h"

class ofApp : public ofBaseApp{

	public:
        bool bFullscreen = false;
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
  ofxShader shader;
  
  //ofxShaderFilter is a more distilled version of ofxShader
    //ofxShader needs begin() and end(), + can play around vertex shader
    //shaderfilter is mainly used for fragment shader
  ofxShaderFilter shaderFilter;
    
};
