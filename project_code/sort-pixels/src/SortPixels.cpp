#include "SortPixels.h"

//--------------------------------------------------------------
void SortPixels::setup(){
    ofBackground(0);
    
    mode = 1;
    blobSize = 0;

    vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(640, 480);

    width = vidGrabber.getWidth();
    height = vidGrabber.getHeight();

    source.loadImage("el.jpg");
    output.allocate(width, height, OF_IMAGE_COLOR);
    finder.setup(width, height);
    blackColor.set(70, 105, 128);
}

//--------------------------------------------------------------
void SortPixels::update(){
    vidGrabber.update();
    
    output.setFromPixels(vidGrabber.getPixels(), width, height, OF_IMAGE_COLOR);
    output.mirror(false, true);
    finder.update(output);

    //output.setFromPixels(source.getPixels(), source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
    output.updateSort(blackColor, mode);
    if(blobSize != finder.getBlobs().size()) {
        //changeMode();
    }
    blobSize = finder.getBlobs().size();
}

//--------------------------------------------------------------
void SortPixels::draw(){
    glPushMatrix();
        glScalef((float)ofGetWidth()/width, (float)ofGetHeight()/height, 1);
        ofFill();
        output.draw(0, 0);

        ofNoFill();
        for(unsigned int i = 0; i < finder.getBlobs().size(); i++) {
            ofRectangle cur = finder.getBlobs()[i].boundingRect;
            ofRect(cur.x, cur.y, cur.width, cur.height);
        }
    glPopMatrix();
}

void SortPixels::changeMode() {
    if(mode == 1) {
        mode = 2;
    } else if(mode == 2) {
        mode = 1;
    }
}

//--------------------------------------------------------------
void SortPixels::keyPressed(int key){
    mode = key - 48;
    
    if(mode < 1) {
        mode = 1;
    } else if(mode > 2) {
        mode = 2;
    }
}

//--------------------------------------------------------------
void SortPixels::keyReleased(int key){

}

//--------------------------------------------------------------
void SortPixels::mouseMoved(int x, int y){
    blackColor.set(int((float)x/ofGetWidth() * 255), int((float)y/ofGetHeight() * 255), 128);
    ofLogNotice() << "x - " << int((float)x/ofGetWidth() * 255) << ", y - " << int((float)y/ofGetHeight() * 255);
}

//--------------------------------------------------------------
void SortPixels::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void SortPixels::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void SortPixels::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void SortPixels::windowResized(int w, int h){

}

//--------------------------------------------------------------
void SortPixels::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void SortPixels::dragEvent(ofDragInfo dragInfo){ 

}