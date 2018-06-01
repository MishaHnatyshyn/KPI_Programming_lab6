#include "bmp.h"

int byte_per_line(int width){
    int result;
    result = width * 3;
    if (result & 0x0003)
    {
        result |= 0x0003;
        ++result;
    }
    return result;
}

PIXELDATA get_interpolated_pixel(PIXELDATA Fx0, PIXELDATA Fx1, double x0, double x1, int x){
    PIXELDATA pixel;
    pixel.r = (int) floor(Fx0.r + ((Fx1.r - Fx0.r) / (x1 - x0)) * (x - x0));
    pixel.g = (int) floor(Fx0.g + ((Fx1.g - Fx0.g) / (x1 - x0)) * (x - x0));
    pixel.b = (int) floor(Fx0.b + ((Fx1.b - Fx0.b) / (x1 - x0)) * (x - x0));
    return pixel;
}

void create(string output_path, int width, int depth,vector<vector<PIXELDATA>> map){
    const char null_byte = ' ';
    BITMAPFILEHEADER bm;
    BITMAPINFOHEADER bm2;

    FILE * file;
    file = fopen("bmp.bmp","rb");

    fread(&bm, 1, 14, file);
    fread(&bm2, 1, 40, file);

    int bytesPerLine = byte_per_line(width);
    /*bm.b1 = 'B';
    bm.b2 = 'M';
    bm.bfSize = 54+bytesPerLine*depth;
    bm.bfReserved1 = 3538944;
    bm.bfReserved2 = 0;
    bm.padding = 6303208;
    bm.bfOffBits = 0;

    bm2.infoSize = 40;
    bm2.width = width;
    bm2.depth = depth;
    bm2.biPlanes = 1;
    bm2.bits = 24;
    bm2.biCompression=  0;
    bm2.biSizeImage=12742;
    bm2.biXPelsPerMeter=  2834;
    bm2.biYPelsPerMeter=  2834;
    bm2.biClrUsed=  0;
    bm2. biClrImportant=  0;
*/
    bm.bfSize = 54+bytesPerLine*depth;
    bm2.depth = depth;
    bm2.width = width;
/*
    PIXELDATA map[depth][width];

    for(int y = 0; y <depth ; y++) {
        for (int x = 0; x < width; x++) {
            if (data[y][x] == 0) {
                map[y][x].r = 255;
                map[y][x].b = 255;
                map[y][x].g = 255;
            }else{
                map[y][x].r = 0;
                map[y][x].b = 0;
                map[y][x].g = 0;
            }
        }
    }*/
    const char* path = output_path.c_str();
    FILE * output;
    output = fopen(path,"wb");

    fwrite(&bm, 1, 14, output);
    fwrite(&bm2, 1, 40, output);

    int output_padding = bytesPerLine - bm2.width*3; // count of null byte at the end of each row
    for (int y = bm2.depth-1; y >= 0; y--) {
        for (int x = 0; x < bm2.width; x++) {
            fwrite(&map[y][x],1,3,output);
        }
        if(output_padding != 0) fwrite(&null_byte,1,output_padding,output);
    }
    
    fclose(output);
}