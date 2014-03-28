//
//  SortedPixelImage.h
//  SortPixels
//
//  Created by subicura on 2014. 3. 22..
//
//

#ifndef __SortPixels__SortedPixelImage__
#define __SortPixels__SortedPixelImage__

#define SORTED_PIXEL_HORIZONTAL         1
#define SORTED_PIXEL_VERTICAL           2

#include "ofImage.h"

class SortedPixelImage : public ofImage {
public:
    SortedPixelImage();
    void updateSort(ofColor black, int mode);
    void sortColumn(int x);
    void sortRow(int y);
    
private:
    int mode;
    
    void setPixelValue(int x, int y, int val);
    int getPixelValue(int x, int y);
    int getFirstNotBlackX(int x, int y);
    int getNextBlackX(int x, int y);
    int getFirstNotBlackY(int x, int y);
    int getNextBlackY(int x, int y);
    
    unsigned char* pixels;
    int blackValue;
    int whiteValue;
    
    int colorCount;
};

#endif /* defined(__SortPixels__SortedPixelImage__) */
