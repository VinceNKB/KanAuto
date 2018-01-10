#ifndef _ROBO_H
#define _ROBO_H
#include <windows.h>
#include "Resource.h"
#include "KanAutoDlg.h"
#include "KanAtk.h"
extern int MarchTime[];
extern bool MarchON1;
extern bool MarchON2;
extern bool MarchON3;

extern time_t t_clock1;
extern time_t t_clock2;
extern time_t t_clock3;

struct threadStartMarch
{
	CKanAutoDlg *dlgHd;
	KanAtk *atkHd;
	int time;
	int waitTime;
	int marchNo;
	int shipNo;
	int area1;
	int area2;
	int zhenxing;
	int atkCount;
	int atkTimes;
	int supplyType;
};

void MouseMove(int x, int y);

void MouseLeftClick(int x, int y);

int waitTime(long wt, double exp = 0.5);

void getPos(int &x, int &y, int xstart, int ystart, int xLength, int yLength);

UINT p_StartMarch(LPVOID lpParam);

//UINT p_GetSupply(int ShipNo);

UINT getSupply(int ShipNo);

UINT p_MarchReturn(LPVOID lpParam);

void getMarchAreaPos(int marchNo, int &pos_x, int &pos_y);

void getAttackArea2Pos(int area2, int &pos_x, int &pos_y);

void getAttackAreaExPos(int area2, int &pos_x, int &pos_y);

void getMarchNumPos(int marchNo, int &pos_x, int &pos_y);

bool getMarchShipPos(int shipNo, int &pos_x, int &pos_y);

bool getSupplyShipPos(int shipNo, int &pos_x, int &pos_y);

UINT p_Attck(LPVOID lpParam);

void getZhenXingPos(int zhenxing, int &pos_x, int &pos_y, HBITMAP &hbmp);

void getAttackAreaPos(int area1, int &pos_x, int &pos_y);

#endif