//
//  FaceFinder.h
//  SortPixels
//
//  Created by subicura on 2014. 3. 22..
//
//

#ifndef __SortPixels__FaceFinder__
#define __SortPixels__FaceFinder__

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

class FaceFinder : public ofThread {
public:
    void setup(int width, int height);
    void update(ofImage source);
    void threadedFunction();
    const vector<ofxCvBlob> &getBlobs() const { return blobs; };
    
private:
    ofxCvHaarFinder finder;
    ofImage image;
    ofxCvGrayscaleImage gray;
    ofxCvColorImage color;
    vector<ofxCvBlob> blobs;

    int width, height;
    bool isLoad;
};

#endif /* defined(__SortPixels__FaceFinder__) */
