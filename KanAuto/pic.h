#ifndef _PIC_H
#define _PIC_H

void down(CImage &image, int x, int y, int w, int h, char filename[]);
void copy(CImage &image, CImage &newImage);
double picCompare(CImage &image, CImage &image2, int xS, int yS, int Xn, int Yn);



#endif