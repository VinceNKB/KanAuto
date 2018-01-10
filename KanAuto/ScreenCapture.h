#ifndef _SCREENCAPTURE_H
#define _SCREENCAPTURE_H

void getImage();
void SCapture(HWND hwnd);
void getImageWhole(HWND hwnd);
HBITMAP CopyDCToBitmap(HDC hScrDC, LPRECT lpRect);
bool inRightPos(char picname[], HBITMAP &hbmp, int xS, int yS, int Xn, int Yn, double d = 0.7);
bool getHWND();
HBITMAP getScreen(HWND hwnd);
BOOL CALLBACK FindChildWnd(HWND hWnd, LPARAM lParam);
#endif