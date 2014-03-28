//
//  SortedPixelImage.cpp
//  SortPixels
//
//  Created by subicura on 2014. 3. 22..
//
//

#include "SortedPixelImage.h"

SortedPixelImage::SortedPixelImage() {
//    black.set(103, 105, 128);
//    white.set(164, 114, 128);
    
    colorCount = 3;
    mode = 1;
}

void SortedPixelImage::updateSort(ofColor black, int mode) {
    this->mode = mode;
    
    blackValue = ( ((255 << 8) | black.r) << 8 | black.g) << 8 | black.b;

    pixels = this->getPixels();
    
    if(mode == SORTED_PIXEL_HORIZONTAL) {
        for(int x = 0; x < this->getWidth(); x++) {
            sortColumn(x);
        }
        for(int y = 0; y < this->getHeight(); y++) {
            sortRow(y);
        }
    } else if(mode == SORTED_PIXEL_VERTICAL) {
        for(int y = 0; y < this->getHeight(); y++) {
            sortRow(y);
        }
        for(int x = 0; x < this->getWidth(); x++) {
            sortColumn(x);
        }
    }
    this->update();
}

void SortedPixelImage::sortColumn(int x) {
    int y1 = 0;
    int y2 = 0;
    
    while(y2 < this->getHeight() - 1) {
        y1 = getFirstNotBlackY(x, y1);
        y2 = getNextBlackY(x, y1);
        
        if (y1 < 0) break;
        
        int sortLength = y2 - y1;
        
        if (sortLength < 0) break;
        
        int unsorted[sortLength];
        for(int i=0; i<sortLength; i++) {
            unsorted[i] = getPixelValue(x, y1 + i);
        }
        
        std::vector<int> sorted(unsorted, unsorted+sortLength);
        std::sort (sorted.begin(), sorted.begin()+sortLength);
        
        for(int i=0; i<sortLength; i++) {
            setPixelValue(x, y1 + i, sorted.at(i));
        }
        
        y1 = y2 + 1;
    }
}

void SortedPixelImage::sortRow(int y) {
    int x1 = 0;
    int x2 = 0;
    
    while(x2 < this->getWidth() - 1) {
        x1 = getFirstNotBlackX(x1, y);
        x2 = getNextBlackX(x1, y);
        
        if (x1 < 0) break;
        
        int sortLength = x2 - x1;

        if (sortLength < 0) break;

        int unsorted[sortLength];
        for(int i=0; i<sortLength; i++) {
            unsorted[i] = getPixelValue(x1 + i, y);
        }
        
        std::vector<int> sorted(unsorted, unsorted+sortLength);
        std::sort (sorted.begin(), sorted.begin()+sortLength);
        
        for(int i=0; i<sortLength; i++) {
            setPixelValue(x1 + i, y, sorted.at(i));
        }

        x1 = x2 + 1;
    }
}

void SortedPixelImage::setPixelValue(int x, int y, int val) {
    int offset = (x + y * this->getWidth()) * colorCount;
    int r = (val >> 16) & 255;
    int g = (val >> 8) & 255;
    int b = val & 255;
    pixels[offset] = r;
    pixels[offset+1] = g;
    pixels[offset+2] = b;
}

int SortedPixelImage::getPixelValue(int x, int y) {
    int offset = (x + y * this->getWidth()) * colorCount;
    int r = pixels[offset];
    int g = pixels[offset + 1];
    int b = pixels[offset + 2];
    
    return ( ((255 << 8) | r) << 8 | g) << 8 | b;
}

int SortedPixelImage::getFirstNotBlackX(int x, int y) {
    while(getPixelValue(x, y) < blackValue) {
        x++;
        if(x >= width) return -1;
    }
    return x;
}

int SortedPixelImage::getNextBlackX(int x, int y) {
    while(getPixelValue(x, y) > blackValue) {
        x++;
        if(x >= width) return width-1;
    }
    return x-1;
}

int SortedPixelImage::getFirstNotBlackY(int x, int y) {
    while(getPixelValue(x, y) < blackValue) {
        y++;
        if(y >= height) return -1;
    }
    return y;
}

int SortedPixelImage::getNextBlackY(int x, int y) {
    while(getPixelValue(x, y) > blackValue) {
        y++;
        if(y >= height) return height-1;
    }
    return y-1;
}
