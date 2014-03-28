//
//  FaceFinder.cpp
//  SortPixels
//
//  Created by subicura on 2014. 3. 22..
//
//

#include "FaceFinder.h"

void FaceFinder::setup(int width, int height) {
    this->width = width;
    this->height = height;
    isLoad = false;
	finder.setup("haarcascade_frontalface_default.xml");
    image.allocate(width, height, OF_IMAGE_COLOR);
    gray.setUseTexture(false);
    gray.allocate(image.width, image.height);
    color.setUseTexture(false);
    color.allocate(image.width, image.height);
    blobs.clear();
    
    startThread(false, false);
}

void FaceFinder::update(ofImage source) {
    if(!isLoad) {
        image.setFromPixels(source.getPixels(), width, height, OF_IMAGE_COLOR);
        isLoad = true;
    }
}

void FaceFinder::threadedFunction() {
    while(true) {
        if(isLoad) {
            color = image.getPixels();
            gray = color;
            finder.findHaarObjects(gray);
            blobs.clear();
            for(vector<ofxCvBlob>::iterator it = finder.blobs.begin(); it != finder.blobs.end(); ++it) {
                blobs.push_back(*it);
            }
                
            isLoad = false;
        }
    }
}
