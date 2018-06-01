#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

struct BITMAPFILEHEADER{
    int8_t  b1, b2;
    int32_t bfSize;
    int32_t  bfReserved1;
    int32_t  bfReserved2;
    int32_t  padding;
    int32_t  bfOffBits;
};

struct BITMAPINFOHEADER{
    int32_t infoSize;
    int32_t width;
    int32_t depth;
    int16_t biPlanes;
    int16_t bits;
    int32_t biCompression;
    int32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    int32_t biClrImportant;
};


struct PIXELDATA{
    uint8_t r;
    uint8_t b;
    uint8_t g;
    PIXELDATA(){
        r = 0;
        g = 0;
        b = 0;
    };
    PIXELDATA(int a, int p, int c){
        r = a;
        g = p;
        b = c;
    };

};


int byte_per_line(int);
void create(string,int,int,vector<vector<PIXELDATA>>);