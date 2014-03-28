#pragma once

#include "ofMain.h"
#include "SortedPixelImage.h"
#include "FaceFinder.h"

class SortPixels : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    void changeMode();
    
    int width, height;
    ofImage source;
    SortedPixelImage output;
    ofColor blackColor;
    FaceFinder finder;
    
    ofVideoGrabber vidGrabber;
    
    int mode;
    int blobSize;
    bool onlyFace;
};
