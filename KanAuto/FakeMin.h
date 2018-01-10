#ifndef _FAKEMIN_H
#define _FAKEMIN_H

void fakeMinOn();
void fakeMinOff();
UINT FakeMin(LPVOID lpParam);
void shiftOut();
void shiftIn();
bool isInDes();

extern int win_x, win_y, win_w, win_h;
extern int ScrWidth, ScrHeight;
extern int WinState;//0 正常 1 最小化

#endif