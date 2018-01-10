#include "stdafx.h"
#include "global.h"
#include "robo.h"
#include "ScreenCapture.h"
#include "conio.h"
#include "KanAutoDlg.h"
#include "KanAtk.h"

using namespace std;

int MarchTime[40] = { 15,30,20,50,90,40,60,180,240,90,300,480,240,360,720,900,45,300,360,120,140,
180,240,0,2400,4800,1200,1500,1440,2880,120,0,15,30,420,540,165,175,1800,0 };

bool MarchON1 = false;
bool MarchON2 = false;
bool MarchON3 = false;
static int marchbutton_Check = 0;
static int marchgoconfirm_Check = 0;
static int marchreturn_Check = 0;
static int foodfleetCheck = 0;
static int attackbutton_Check = 0;
static int attackarea_Check = 0;
static int atkNext_Check = 0;
static int atkNext2_Check = 0;
static int marchgo_Check1 = 0;
static int marchgo_Check2 = 0;
static int marchgo_Check3 = 0;
static int marchison = 0;

void MouseMove(int x, int y)
{
	PostMessage(IESHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
}

void MouseLeftClick(int x, int y)
{
//	PostMessage(hwnd, WM_MOUSEMOVE, NULL, MAKELPARAM(0, 0));
	PostMessage(IESHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(x, y));
	srand((unsigned)time(NULL));
	int sleepTime = 80 + (rand()%40);
	Sleep(sleepTime);
	PostMessage(IESHwnd, WM_LBUTTONUP, NULL, MAKELPARAM(x, y));
}


int waitTime(long wt, double exp)
{
	srand((unsigned)time(NULL));
	//long l = wt - (long)(wt * exp / 2) + rand() % (long)(wt * exp);
	//cout << l << endl;
	long time = wt - (long)(wt * exp / 2) + rand() % (long)(wt * exp);
	Sleep(time);
	return time;
}


void getPos(int &x, int &y, int xstart, int ystart, int xLength, int yLength)
{
	srand((unsigned)time(NULL));
	x = rand() % xLength + xstart;
	y = rand() % yLength + ystart;
}

UINT p_StartMarch(LPVOID lpParam)
{
//	_cprintf("sm lock1\n");
	critical_section.Lock();
//	_cprintf("sm lock2\n");
	threadStartMarch* pInfo = (threadStartMarch*)lpParam;
	int marchNo = pInfo->marchNo;
	int shipNo = pInfo->shipNo;
	CKanAutoDlg *hd = pInfo->dlgHd;
	int matchTime = pInfo->time;
	int supplyType = pInfo->supplyType;

	int pos_x = 0, pos_y = 0;
	int flag = 10;
//	_cprintf("in sm\n");

	volatile bool *run;
	if (shipNo == 2)
		run = &march1Run;
	else if (shipNo == 3)
		run = &march2Run;
	else if (shipNo == 4)
		run = &march3Run;
	else return 0;

	marchbutton_Check = 0;
	marchgoconfirm_Check = 0;
	marchreturn_Check = 0;
	marchgo_Check1 = 0;
	marchgo_Check2 = 0;
	marchgo_Check3 = 0;
	marchison = 0;

	while (*run)
	{
		_cprintf("in sm while\n");
		waitTime(300);
		HBITMAP hBitmap = getScreen(IESHwnd);
		switch (flag)
		{
		case 10://是否已经在远征界面
			_cprintf("case 10\n");
			if (inRightPos("marchgoconfirm", hBitmap, MARCH_GO_CONFIRM_X, MARCH_GO_CONFIRM_Y, 10, 10, 0.5))
				flag = 2;
			else flag = 0;
			break;
		case 0:
			//检查是否在初始界面
			_cprintf("case 0\n");
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				//单击任意一处
				waitTime(500);
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(2000);
				flag = 101;
				_cprintf("case 01\n");
			}
			else if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))//是否在初始界面
			{
				//尝试进入初始界面
				waitTime(500);
				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
				waitTime(500);
				flag = 102;
				_cprintf("case 02\n");
			}
			else
			{
				//单击出击按钮
				getPos(pos_x, pos_y, HOME_ATTACK_X, HOME_ATTACK_Y, HOME_ATTACK_W, HOME_ATTACK_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 1;
				_cprintf("case 03\n");
			}
			break;
		case 101:
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 101;
				//_cprintf("case 101 1\n");
			}
			else{
				flag = 11;
				//_cprintf("case 101 2\n");
			}
			break;
		case 102:
			if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))//是否在初始界面
			{
				//尝试进入初始界面
				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
				waitTime(500);
				flag = 102;
				//_cprintf("case 102 1\n");
			}
			else
			{
				flag = 0;
				//_cprintf("case 102 2\n");
			}
			break;
		case 11:
			_cprintf("case 11\n");
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				marchreturn_Check = 0;
				//_cprintf("case 11 1\n");
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 12;
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 11 2\n");
				
				if (marchreturn_Check < 5){
					flag = 11;
					waitTime(1000);
					marchreturn_Check++;
				}
				else{
					waitTime(1000);
					flag = 0;
					marchreturn_Check = 0;
				}
				
			}
			break;
		case 12:
			//_cprintf("case 12\n");
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				//_cprintf("case 12 1\n");
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 0;//处理完远征归来
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 12 2\n");
				flag = 12;
				waitTime(500);
			}
			break;
		case 1:
			//检出是否在出击三选一界面
			//_cprintf("case 1\n");

			if (!inRightPos("marchbutton", hBitmap, MARCH_CHOOSE_X, MARCH_CHOOSE_Y, 10, 10))
			{
				//尝试进入初始界面
				if (marchbutton_Check < 10){
					flag = 1;
					marchbutton_Check++;
					//	cout << "case 11" << endl;
					waitTime(500);
					marchbutton_Check++;

				}
				else
				{
					flag = 0;
					marchbutton_Check = 0;
				}
				//_cprintf("case 11\n");
			}
			else
			{
				marchbutton_Check = 0;
				//单击远征按钮
				getPos(pos_x, pos_y, MARCH_CHOOSE_X, MARCH_CHOOSE_Y, MARCH_CHOOSE_W, MARCH_CHOOSE_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 2;
				//_cprintf("case 12\n");
			}
			break;
		case 2:
			//选择进行哪个远征
			//_cprintf("case 2\n");

			if (!inRightPos("marchgoconfirm", hBitmap, MARCH_GO_CONFIRM_X, MARCH_GO_CONFIRM_Y, 10, 10))
			{
				
				//尝试进入初始界面
				if (marchgoconfirm_Check < 10){
					//_cprintf("marchgoconfirm_Check\n");
					flag = 2;
					marchgoconfirm_Check++;
				}
				else{
					flag = 1;
					marchgoconfirm_Check = 0;
				}
				//_cprintf("case 21\n");

				waitTime(1000);
			}
			else
			{
				marchgoconfirm_Check = 0;
				//单击海域
				getMarchAreaPos(marchNo, pos_x, pos_y);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				//	cout << pos_x << "," << pos_y << endl;
				//单击远征号
				getMarchNumPos(marchNo, pos_x, pos_y);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				//	cout << pos_x << "," << pos_y << endl;
				flag = 3;
				//_cprintf("case 22\n");
			}
			break;
		case 3:
			//检出上一步是否选好远征以及远征是不是在进行中
			//_cprintf("case 3\n");
			if (inRightPos("marchgo", hBitmap, MARCH_GO_X, MARCH_GO_Y, 10, 10))//正确的
			{
				marchgo_Check3 = 0;
				getPos(pos_x, pos_y, MARCH_GO_X, MARCH_GO_Y, MARCH_GO_W, MARCH_GO_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 4;
				//_cprintf("case 31\n");
			}
			else if (inRightPos("marchgo2", hBitmap, MARCH_GO_X, MARCH_GO_Y, 10, 10))//所选的远征号正在进行， 返回远征界面， 取消任务
			{
				marchgo_Check3 = 0;
				if (marchison == 0)
				{
					marchison++;
					waitTime(500);
					flag = 0;
				}
				else{
					marchison = 0;
					//_cprintf("case 32\n");
					if (shipNo == 2){
						t_clock1 = matchTime + time(NULL);
					}
					else if (shipNo == 3){
						t_clock2 = matchTime + time(NULL);
					}
					else{
						t_clock3 = matchTime + time(NULL);
					}
					hd->SetTimer(shipNo - 1, 500, NULL);
					critical_section.Unlock();
					return 1;
				}
			//	cout << "case 32" << endl;
			}
			else if (inRightPos("marchgo6", hBitmap, MARCH_GO6_X, MARCH_GO6_Y, 20, 10))
			{
				marchgo_Check3 = 0;
				//_cprintf("case 34\n");
				waitTime(1000);
				flag = 0;
			}
			else//没有到这个界面，返回上一个界面
			{
				//使用函数回到初始界面！！！！！
				if (marchgo_Check3 < 10)
				{
					marchgo_Check3++;
					waitTime(1000);
					flag = 2;
					//_cprintf("case 33\n");
					//	cout << "case 33" << endl;
				}
				else{
					marchgo_Check3 = 0;
					//_cprintf("sm unlock\n");
					critical_section.Unlock();
					return 1;
				}
			}
			break;
		case 4:
			//检出上一步是否选好远征以及选择远征舰队
			//_cprintf("case 4\n");
			//cout << "case 4" << endl;
			if (!inRightPos("marchgo5", hBitmap, MARCH_GO5_X, MARCH_GO5_Y, 10, 10))
			{
				//不在预定界面
				flag = 3;
				//_cprintf("case 41\n");
			//	cout << "case 41" << endl;
			}
			else
			{
				//选择舰队
				if (getMarchShipPos(shipNo, pos_x, pos_y))
				{
					MouseLeftClick(pos_x, pos_y);
					waitTime(1000);
					//_cprintf("case 42\n");
			//		cout << "case 42" << endl;
					flag = 13;
				}
				else{
					//_cprintf("case 43\n");
					//使用函数回到初始界面！！！！！
					//_cprintf("sm unlock\n");
					critical_section.Unlock();
					return 1;
				}
			}
			break;
		case 13://分三种情况搞
			//_cprintf("case 13\n");
			if ((shipNo == 2 && !inRightPos("marchshipnocheck2", hBitmap, MARCH_SHIP_NO_CHECK2_X, MARCH_SHIP_NO_CHECK2_Y, 10, 10)) ||
				(shipNo == 3 && !inRightPos("marchshipnocheck3", hBitmap, MARCH_SHIP_NO_CHECK3_X, MARCH_SHIP_NO_CHECK3_Y, 10, 10)) ||
				(shipNo == 4 && !inRightPos("marchshipnocheck4", hBitmap, MARCH_SHIP_NO_CHECK4_X, MARCH_SHIP_NO_CHECK4_Y, 10, 10)))
			{
				//_cprintf("case 13 1\n");
				flag = 4;
			}
			else
			{
				//_cprintf("case 13 2\n");
				if (inRightPos("you", hBitmap, MARCH_NEED_YOU1_X, MARCH_NEED_YOU1_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_YOU2_X, MARCH_NEED_YOU2_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_YOU3_X, MARCH_NEED_YOU3_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_YOU4_X, MARCH_NEED_YOU4_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_YOU5_X, MARCH_NEED_YOU5_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_YOU6_X, MARCH_NEED_YOU6_Y, 8, 9) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN1_X, MARCH_NEED_DAN1_Y, 2, 10) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN2_X, MARCH_NEED_DAN2_Y, 2, 10) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN3_X, MARCH_NEED_DAN3_Y, 2, 10) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN4_X, MARCH_NEED_DAN4_Y, 2, 10) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN5_X, MARCH_NEED_DAN5_Y, 2, 10) ||
					inRightPos("you", hBitmap, MARCH_NEED_DAN6_X, MARCH_NEED_DAN6_Y, 2, 10))
				{
					//_cprintf("case 13 3\n");
					if(supplyType == 1)
						getSupply(0);
					else
						getSupply(shipNo);

					flag = 10;
					break;
				}
				//_cprintf("case 13 4\n");
				if (inRightPos("marchgo4", hBitmap, MARCH_GO3_X, MARCH_GO3_Y, 10, 10))
				{
					//_cprintf("case 13 5\n");
					marchgo_Check1 = 0;
					marchgo_Check2 = 0;
					getPos(pos_x, pos_y, MARCH_GO3_X, MARCH_GO3_Y, MARCH_GO3_W, MARCH_GO3_H);
					MouseLeftClick(pos_x, pos_y);
					waitTime(2000);
					flag = 5;
					//_cprintf("case 13 1\n");
				//	cout << "case 13 1" << endl;
	/*				hd->SetTimer(shipNo-1, 500, NULL);
					_cprintf("sm unlock\n");
					critical_section.Unlock();
					return 0;*/
				}
				//else if (inRightPos("marchgo3", hBitmap, MARCH_GO3_X, MARCH_GO3_Y, 10, 10))//预定舰队已经出击
				//{
				//	//使用函数回到初始界面！！！！！
				//	waitTime(1500);
				//	flag = 0;
				//	cout << "case 13 2" << endl;
				//}
				else{
					marchgo_Check1++;
					if (marchgo_Check1 > 10)
					{
						//_cprintf("case 13 3\n");
						if (shipNo == 2){
							t_clock1 = matchTime + time(NULL);
						}
						else if (shipNo == 3){
							t_clock2 = matchTime + time(NULL);
						}
						else{
							t_clock3 = matchTime + time(NULL);
						}
						hd->SetTimer(shipNo - 1, 500, NULL);
						//_cprintf("sm unlock\n");
						critical_section.Unlock();
						return 1;
					}
					else{
						waitTime(1000);
						flag = 13;
					}
				//	cout << "case 13 3" << endl;
					//使用函数回到初始界面！！！！！
					
				}
			}
			break;
		case 5:
			if (inRightPos("marchgo4", hBitmap, MARCH_GO3_X, MARCH_GO3_Y, 10, 10))
			{
				marchgo_Check2++;
				if (marchgo_Check2 > 10)
				{
					//_cprintf("case 5 1\n");
					if (shipNo == 2){
						t_clock1 = matchTime + time(NULL);
					}
					else if (shipNo == 3){
						t_clock2 = matchTime + time(NULL);
					}
					else{
						t_clock3 = matchTime + time(NULL);
					}
					hd->SetTimer(shipNo - 1, 500, NULL);
					//_cprintf("sm unlock\n");
					critical_section.Unlock();
					return 1;
				}
				getPos(pos_x, pos_y, MARCH_GO3_X, MARCH_GO3_Y, MARCH_GO3_W, MARCH_GO3_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
			}
			else{
				marchgo_Check2 = 0;
				if (shipNo == 2){
					t_clock1 = matchTime + time(NULL);
				}
				else if (shipNo == 3){
					t_clock2 = matchTime + time(NULL);
				}
				else{
					t_clock3 = matchTime + time(NULL);
				}
				hd->SetTimer(shipNo - 1, 500, NULL);
				//_cprintf("sm unlock\n");
				critical_section.Unlock();
				return 0;
			}
			break;
			//case 5:
			//	cout << "case 5" << endl;
			//	if (!inRightPos("marchgoconfirm2", hBitmap, MARCH_GO_CONFIRM2_X, MARCH_GO_CONFIRM2_Y, 10, 10, 0.2))
			//	{
			//		//点击回到港口界面
			//		cout << "case 51" << endl;
			//		getPos(pos_x, pos_y, BACK_X, BACK_Y, BACK_W, BACK_H);
			//		MouseLeftClick(pos_x, pos_y);
			//		waitTime(1000);
			//		flag = 6;
			//	}
			//	else{
			//		cout << "case 52" << endl;
			//		flag = 5;
			//		waitTime(500);
			//	}
			//	break;
			//case 6:
			//	//检查自己是不是在港口
			//	cout << "case 6" << endl;
			//	if (inRightPos("home_attack", hBitmap, HOME_ATTACK_X, HOME_ATTACK_Y, 10, 10))
			//		return TRUE;
			//	else {
			//		flag = 6;
			//		waitTime(1000);
			//	}
			//	break;
		}
	}
	//_cprintf("sm unlock\n");
	critical_section.Unlock();
	return 0;
}

void getMarchAreaPos(int marchNo, int &pos_x, int &pos_y)
{
	if (marchNo >= 1 && marchNo <= 8)
		getPos(pos_x, pos_y, 113, 442, 44, 8);
	else if (marchNo >= 9 && marchNo <= 16)
		getPos(pos_x, pos_y, 175, 442, 44, 8);
	else if (marchNo >= 17 && marchNo <= 24)
		getPos(pos_x, pos_y, 238, 442, 44, 8);
	else if (marchNo >= 25 && marchNo <= 32)
		getPos(pos_x, pos_y, 287, 442, 44, 8);
	else
		getPos(pos_x, pos_y, 346, 442, 44, 8);
}


void getMarchNumPos(int marchNo, int &pos_x, int &pos_y)
{
	marchNo = (marchNo - 1) % 8;
	//cout << "marchNo " << marchNo << endl;
	getPos(pos_x, pos_y, 130, 160 + marchNo * 30, 350, 25);
}

bool getMarchShipPos(int shipNo, int &pos_x, int &pos_y)
{
	if (shipNo == 2)
	{
		getPos(pos_x, pos_y, 387, 112, 15, 15);
		return true;
	}
	else if (shipNo == 3)
	{
		getPos(pos_x, pos_y, 411, 109, 15, 15);
		return true;
	}
	else if (shipNo == 4)
	{
		getPos(pos_x, pos_y, 441, 109, 15, 15);
		return true;
	}
	else return false;
}

UINT getSupply(int ShipNo)
{
	if (ShipNo < 0 || ShipNo > 4)
		return FALSE;
	int supplyArray[4] = { 0, 0, 0, 0 };

	if (ShipNo == 0)
	{
		supplyArray[0] = 1;
		supplyArray[1] = 1;
		supplyArray[2] = 1;
		supplyArray[3] = 1;
	}
	else
	{
		supplyArray[ShipNo - 1] = 1;
	}
	int shipCount = 0;
	int pos_x = 0, pos_y = 0;
	int flag = 0;
	while (1)
	{
		waitTime(200);
		HBITMAP hBitmap = getScreen(IESHwnd);
		switch (flag)
		{
		case 0://是否已经在补给界面
		//	cout << "scase 0" << endl;
			if (inRightPos("supplycheck", hBitmap, SUPPLY_CHECK_X, SUPPLY_CHECK_Y, 10, 10))
				flag = 5;
			else flag = 1;
			break;
		case 1:
			//检查是否在初始界面
		//	cout << "scase 1" << endl;
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				//单击任意一处
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(4000);
				flag = 2;
			//	cout << "scase 11" << endl;
			}
			else if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))//是否在初始界面
			{
				//尝试进入初始界面
				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
				waitTime(1000);
				flag = 0;
		//		cout << "scase 12" << endl;
			}
			else
			{
				//单击补给按钮
				getPos(pos_x, pos_y, HOME_FOOD_X, HOME_FOOD_Y, HOME_FOOD_W, HOME_FOOD_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 4;
		//		cout << "scase 13" << endl;
			}
			break;
		case 2:
	//		cout << "scase 2" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
		//		cout << "scase 21" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 3;
				waitTime(1000);
			}
			else
			{
		//		cout << "scase 22" << endl;
				flag = 2;
				waitTime(1000);
			}
			break;
		case 3:
		//	cout << "scase 3" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
		//		cout << "scase 31" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 0;//处理完远征归来
				waitTime(1000);
			}
			else
			{
		//		cout << "scase 32" << endl;
				flag = 3;
				waitTime(1000);
			}
			break;
		case 4:
			//检出是否在补给界面
		//	cout << "scase 4" << endl;

			if (inRightPos("supplycheck", hBitmap, SUPPLY_CHECK_X, SUPPLY_CHECK_Y, 10, 10))
			{
				flag = 5;
		//		cout << "scase 41" << endl;
			//	waitTime(1000);
			}
			else
			{
				//重来
				flag = 0;
				waitTime(1000);
		//		cout << "scase 42" << endl;
			}
			break;
		case 5:
		//	cout << "scase 5" << endl;
			while (shipCount < 4)
			{
		//		cout << "scase 51" << endl;
				if (supplyArray[shipCount] != 1)
					shipCount++;
				else
					break;
			}
			if (shipCount == 4)
			{
		//		cout << "scase 52" << endl;
				//要不要回到港口界面？
				return 0;
			}
			if (getSupplyShipPos(shipCount + 1, pos_x, pos_y))
			{
		//		cout << "scase 53" << endl;
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 6;
			}
			break;
		case 6:
		//	cout << "scase 6" << endl;
			if ((shipCount == 0 && !inRightPos("supplyshipnocheck1", hBitmap, SUPPLY_SHIP_NO_CHECK1_X, SUPPLY_SHIP_NO_CHECK1_Y, 10, 10))
				|| (shipCount == 1 && !inRightPos("supplyshipnocheck2", hBitmap, SUPPLY_SHIP_NO_CHECK2_X, SUPPLY_SHIP_NO_CHECK2_Y, 10, 10))
				|| (shipCount == 2 && !inRightPos("supplyshipnocheck3", hBitmap, SUPPLY_SHIP_NO_CHECK3_X, SUPPLY_SHIP_NO_CHECK3_Y, 10, 10))
				|| (shipCount == 3 && !inRightPos("supplyshipnocheck4", hBitmap, SUPPLY_SHIP_NO_CHECK4_X, SUPPLY_SHIP_NO_CHECK4_Y, 10, 10)))
			{
	//			cout << "scase 61" << endl;
				flag = 5;
			}
			else
			{
				if (inRightPos("food_fleet_all_enable", hBitmap, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, 10, 10))//界面中的第一条船需要补给
				{//点下全部补给的选项
	//				cout << "scase 62" << endl;
					getPos(pos_x, pos_y, 111, 113, 15, 15); 
					MouseMove(pos_x, pos_y);
					waitTime(1000);
					MouseLeftClick(pos_x, pos_y);
					waitTime(1000);
					flag = 7;
				}
				else
				{
	//				cout << "scase 62" << endl;
					//已经补给过了，顺利返回
					shipCount++;
					flag = 5;
				}
			}
			break;
		case 7:
	//		cout << "scase 7" << endl;
			if (inRightPos("food_fleet_all_disable", hBitmap, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, 10, 10))//点补给
			{
	//			cout << "scase 71" << endl;
				shipCount++;
				flag = 5;
			}
			else
			{
	//			cout << "scase 72" << endl;
				//这应该是不可能的
				waitTime(1000);
				flag = 6;
			}
			break;
		}
	}
}



//UINT p_GetSupply(int ShipNo)
//{
//	critical_section.Lock();
//	if (ShipNo < 0 || ShipNo > 4)
//		return FALSE;
//	int supplyArray[4] = { 0, 0, 0, 0 };
//
//	if (ShipNo == 0)
//	{
//		supplyArray[0] = 1;
//		supplyArray[1] = 1;
//		supplyArray[2] = 1;
//		supplyArray[3] = 1;
//	}
//	else
//	{
//		supplyArray[ShipNo - 1] = 1;
//	}
//	int shipCount = 0;
//	int pos_x = 0, pos_y = 0;
//	int flag = 0;
//	while (1)
//	{
//		waitTime(200);
//		HBITMAP hBitmap = getScreen(IESHwnd);
//		switch (flag)
//		{
//		case 0://是否已经在补给界面
//			cout << "scase 0" << endl;
//			if (inRightPos("supplycheck", hBitmap, SUPPLY_CHECK_X, SUPPLY_CHECK_Y, 10, 10))
//				flag = 5;
//			else flag = 1;
//			break;
//		case 1:
//			//检查是否在初始界面
//			cout << "scase 1" << endl;
//			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
//			{
//				//单击任意一处
//				getPos(pos_x, pos_y, 50, 50, 600, 300);
//				MouseLeftClick(pos_x, pos_y);
//				waitTime(4000);
//				flag = 2;
//				cout << "scase 11" << endl;
//			}
//			else if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10))//是否在初始界面
//			{
//				//尝试进入初始界面
//				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
//				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
//				waitTime(1000);
//				flag = 0;
//				cout << "scase 12" << endl;
//			}
//			else
//			{
//				//单击补给按钮
//				getPos(pos_x, pos_y, HOME_FOOD_X, HOME_FOOD_Y, HOME_FOOD_W, HOME_FOOD_H);
//				MouseLeftClick(pos_x, pos_y);
//				waitTime(1000);
//				flag = 4;
//				cout << "scase 13" << endl;
//			}
//			break;
//		case 2:
//			cout << "scase 2" << endl;
//			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
//			{
//				cout << "scase 21" << endl;
//				//点击“次”
//				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
//				MouseLeftClick(pos_x, pos_y);
//				flag = 3;
//				waitTime(500);
//			}
//			else
//			{
//				cout << "scase 22" << endl;
//				flag = 2;
//				waitTime(500);
//			}
//			break;
//		case 3:
//			cout << "scase 3" << endl;
//			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
//			{
//				cout << "scase 31" << endl;
//				//点击“次”
//				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
//				MouseLeftClick(pos_x, pos_y);
//				flag = 0;//处理完远征归来
//				waitTime(500);
//			}
//			else
//			{
//				cout << "scase 32" << endl;
//				flag = 3;
//				waitTime(500);
//			}
//			break;
//		case 4:
//			//检出是否在补给界面
//			cout << "scase 4" << endl;
//			if (inRightPos("supplycheck", hBitmap, SUPPLY_CHECK_X, SUPPLY_CHECK_Y, 10, 10))
//			{
//				flag = 5;
//				cout << "scase 41" << endl;
//				waitTime(500);
//			}
//			else
//			{
//				//重来
//				flag = 0;
//				waitTime(500);
//				cout << "scase 42" << endl;
//			}
//			break;
//		case 5:
//			cout << "scase 5" << endl;
//			while (shipCount < 4)
//			{
//				cout << "scase 51" << endl;
//				if (supplyArray[shipCount] != 1)
//					shipCount++;
//				else
//					break;
//			}
//			if (shipCount == 4)
//			{
//				cout << "scase 52" << endl;
//				//要不要回到港口界面？
//				return 0;
//			}
//			if (getSupplyShipPos(shipCount + 1, pos_x, pos_y))
//			{
//				cout << "scase 53" << endl;
//				MouseLeftClick(pos_x, pos_y);
//				waitTime(500);
//				flag = 6;
//			}
//			break;
//		case 6:
//			cout << "scase 6" << endl;
//			if ((shipCount == 0 && !inRightPos("supplyshipnocheck1", hBitmap, SUPPLY_SHIP_NO_CHECK1_X, SUPPLY_SHIP_NO_CHECK1_Y, 10, 10))
//				|| (shipCount == 1 && !inRightPos("supplyshipnocheck2", hBitmap, SUPPLY_SHIP_NO_CHECK2_X, SUPPLY_SHIP_NO_CHECK2_Y, 10, 10))
//				|| (shipCount == 2 && !inRightPos("supplyshipnocheck3", hBitmap, SUPPLY_SHIP_NO_CHECK3_X, SUPPLY_SHIP_NO_CHECK3_Y, 10, 10))
//				|| (shipCount == 3 && !inRightPos("supplyshipnocheck4", hBitmap, SUPPLY_SHIP_NO_CHECK4_X, SUPPLY_SHIP_NO_CHECK4_Y, 10, 10)))
//			{
//				cout << "scase 61" << endl;
//				flag = 5;
//			}
//			else
//			{
//				if (inRightPos("food_fleet_all_enable", hBitmap, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, 10, 10))
//				{//点下全部补给的选项
//					cout << "scase 62" << endl;
//					getPos(pos_x, pos_y, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, FOOD_FLEET_ALL_W, FOOD_FLEET_ALL_H);
//					MouseLeftClick(pos_x, pos_y);
//					waitTime(500);
//					flag = 7;
//				}
//				else
//				{
//					cout << "scase 62" << endl;
//					//已经补给过了，顺利返回
//					shipCount++;
//					flag = 5;
//				}
//			}
//			break;
//		case 7:
//			cout << "scase 7" << endl;
//			if (inRightPos("food_fleet_button_enable", hBitmap, FOOD_FLEET_BUTTON_X, FOOD_FLEET_BUTTON_Y, 10, 10))//点补给
//			{
//				cout << "scase 71" << endl;
//				getPos(pos_x, pos_y, FOOD_FLEET_BUTTON_X, FOOD_FLEET_BUTTON_Y, FOOD_FLEET_BUTTON_W, FOOD_FLEET_BUTTON_H);
//				MouseLeftClick(pos_x, pos_y);
//				waitTime(1000);
//				flag = 8;
//			}
//			else
//			{
//				cout << "scase 72" << endl;
//				//这应该是不可能的
//				flag = 6;
//			}
//			break;
//		case 8:
//			cout << "scase 8" << endl;
//			if (inRightPos("food_fleet_button_disable", hBitmap, FOOD_FLEET_BUTTON_X, FOOD_FLEET_BUTTON_Y, 10, 10))//点补给
//			{
//				cout << "scase 81" << endl;
//				//ok
//				shipCount++;
//				flag = 5;
//			}
//			else
//			{
//				cout << "scase 82" << endl;
//				waitTime(500);
//				flag = 8;
//			}
//			break;
//		}
//	}
//	critical_section.Unlock();
//}


bool getSupplyShipPos(int shipNo, int &pos_x, int &pos_y)
{
	if (shipNo == 1)
	{
		getPos(pos_x, pos_y, 140, 114, 14, 12);
		return true;
	}
	else if (shipNo == 2)
	{
		getPos(pos_x, pos_y, 173, 114, 12, 14);
		return true;
	}
	else if (shipNo == 3)
	{
		getPos(pos_x, pos_y, 202, 113, 12, 15);
		return true;
	}
	else if (shipNo == 4)
	{
		getPos(pos_x, pos_y, 223, 114, 13, 14);
		return true;
	}
	else return false;
}


UINT p_MarchReturn(LPVOID lpParam)
{
	//_cprintf("mr lock1\n");
	critical_section.Lock();
	//_cprintf("mr lock2\n");
	threadStartMarch* pInfo = (threadStartMarch*)lpParam;
	int ShipNo = pInfo->shipNo;
	if (ShipNo < 0 || ShipNo > 4)
		return FALSE;
	int supplyArray[4] = { 0, 0, 0, 0 };

	if (ShipNo == 0)
	{
		supplyArray[0] = 1;
		supplyArray[1] = 1;
		supplyArray[2] = 1;
		supplyArray[3] = 1;
	}
	else
	{
		supplyArray[ShipNo - 1] = 1;
	}
	int shipCount = 0;
	int pos_x = 0, pos_y = 0;
	int flag = 1;
	int waitCount = 0;

	foodfleetCheck = 0;

	while (1)
	{
		waitTime(200);
		HBITMAP hBitmap = getScreen(IESHwnd);
		switch (flag)
		{
		case 1:
			//检查是否在初始界面
			//_cprintf("scase 1\n");
			//cout << "scase 1" << endl;
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				//单击任意一处
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(4000);
				flag = 2;
				//_cprintf("scase 11\n");
			//	cout << "scase 11" << endl;
			}
			else if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))//是否在初始界面
			{
				//尝试进入初始界面
				waitCount++;
				if (waitCount > 10)
				{
					//_cprintf("scase 14\n");
					//_cprintf("mr unlock\n");
					critical_section.Unlock();
					return 1;
				}
				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
				waitTime(1000);
				flag = 1;
				//_cprintf("scase 12\n");
				//cout << "scase 12" << endl;
			}
			else
			{
				//单击补给按钮
				getPos(pos_x, pos_y, HOME_FOOD_X, HOME_FOOD_Y, HOME_FOOD_W, HOME_FOOD_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 4;
				//_cprintf("scase 13\n");
				//cout << "scase 13" << endl;
			}
			break;
		case 2:
			//_cprintf("scase 2\n");
			//cout << "scase 2" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				//_cprintf("scase 21\n");
			//	cout << "scase 21" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 3;
				waitTime(500);
			}
			else
			{
				if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10)||inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))
					flag = 1;
				else
					flag = 2;
				//_cprintf("scase 22\n");
				//cout << "scase 22" << endl;
				waitTime(500);
			}
			break;
		case 3:
			//_cprintf("scase 3\n");
			//cout << "scase 3" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				//_cprintf("scase 31\n");
			//	cout << "scase 31" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 1;//处理完远征归来
				waitTime(500);
			}
			else
			{
				//_cprintf("scase 32\n");
			//	cout << "scase 32" << endl;
				flag = 3;
				waitTime(500);
			}
			break;
		case 4:
			//检出是否在补给界面
			//_cprintf("scase 4\n");
			//cout << "scase 4" << endl;
			if (inRightPos("supplycheck", hBitmap, SUPPLY_CHECK_X, SUPPLY_CHECK_Y, 10, 10))
			{
				flag = 5;
				//_cprintf("scase 41\n");
			//	cout << "scase 41" << endl;
				waitTime(500);
			}
			else
			{
				//重来
				flag = 1;
				waitTime(500);
				//_cprintf("scase 42\n");
			//	cout << "scase 42" << endl;
			}
			break;
		case 5:
			//_cprintf("scase 5\n");
			//cout << "scase 5" << endl;
			while (shipCount < 4)
			{
				//_cprintf("scase 51\n");
			//	cout << "scase 51" << endl;
				if (supplyArray[shipCount] != 1)
					shipCount++;
				else
					break;
			}
			if (shipCount == 4)
			{
				//_cprintf("scase 52\n");
			//	cout << "scase 52" << endl;
				//要不要回到港口界面？
				//_cprintf("mr unlock\n");
				critical_section.Unlock();
				return 0;
			}
			if (getSupplyShipPos(shipCount + 1, pos_x, pos_y))
			{
				//_cprintf("scase 53\n");
			//	cout << "scase 53" << endl;
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 6;
			}
			break;
		case 6:
			//_cprintf("scase 6\n");
			//cout << "scase 6" << endl;
			if ((shipCount == 0 && !inRightPos("supplyshipnocheck1", hBitmap, SUPPLY_SHIP_NO_CHECK1_X, SUPPLY_SHIP_NO_CHECK1_Y, 10, 10))
				|| (shipCount == 1 && !inRightPos("supplyshipnocheck2", hBitmap, SUPPLY_SHIP_NO_CHECK2_X, SUPPLY_SHIP_NO_CHECK2_Y, 10, 10))
				|| (shipCount == 2 && !inRightPos("supplyshipnocheck3", hBitmap, SUPPLY_SHIP_NO_CHECK3_X, SUPPLY_SHIP_NO_CHECK3_Y, 10, 10))
				|| (shipCount == 3 && !inRightPos("supplyshipnocheck4", hBitmap, SUPPLY_SHIP_NO_CHECK4_X, SUPPLY_SHIP_NO_CHECK4_Y, 10, 10)))
			{
				//_cprintf("scase 61\n");
			//	cout << "scase 61" << endl;
				flag = 5;
			}
			else
			{
				if (inRightPos("food_fleet_all_enable", hBitmap, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, 10, 10))
				{//点下全部补给的选项
					//_cprintf("scase 62\n");
			//		cout << "scase 62" << endl;
					getPos(pos_x, pos_y, 111, 113, 15, 15);
					MouseMove(pos_x, pos_y);
					waitTime(1000);
					MouseLeftClick(pos_x, pos_y);
					waitTime(1000);
					flag = 7;
				}
				else
				{
					//_cprintf("scase 63\n");
				//	cout << "scase 62" << endl;
					//已经补给过了，顺利返回
					shipCount++;
					flag = 5;
				}
			}
			break;
		case 7:
			//_cprintf("scase 7\n");
			//cout << "scase 7" << endl;
			if (inRightPos("food_fleet_all_disable", hBitmap, FOOD_FLEET_BUTTON_X, FOOD_FLEET_BUTTON_Y, 10, 10))//点补给
			{
				//_cprintf("scase 71\n");
			//	cout << "scase 71" << endl;
				shipCount++;
				flag = 5;
			}
			else
			{
				//_cprintf("scase 72\n");
			//	cout << "scase 72" << endl;
				//这应该是不可能的
				waitTime(1000);
				flag = 6;
			}
			break;
		}
	}
	critical_section.Unlock();
	//_cprintf("mr unlock\n");
}


UINT p_Attck(LPVOID lpParam)
{
	int infi = 3;
	//_cprintf("atk lock1\n");
	critical_section.Lock();
	//_cprintf("atk lock2\n");
	threadStartMarch* pInfo = (threadStartMarch*)lpParam;
	int area1 = pInfo->area1;
	int area2 = pInfo->area2;
	int zhenxing = pInfo->zhenxing;
	int atkCount = pInfo->atkCount;
	int atk_time = pInfo->waitTime;
	KanAtk *atkHd = pInfo->atkHd;
	int atkTimes = pInfo->atkTimes - 1;
	int pos_x = 0, pos_y = 0;
	int flag = 0;
	int atkCountNow = atkCount;


	marchreturn_Check = 0;
	attackbutton_Check = 0;
	attackarea_Check = 0;
	atkNext_Check = 0;
	atkNext2_Check = 0;

	//getImage();

	while (AtkOn)
	{
		//_cprintf("in atk while\n");
		waitTime(300);
		//getImageWhole(IESHwnd);
		//getImage();


		HBITMAP hBitmap = getScreen(IESHwnd);





		switch (flag)
		{
		case 0:
			//检查是否在初始界面
			//_cprintf("case 0\n");
			//waitTime(500);
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				//单击任意一处
				waitTime(500);
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(4000);
				flag = 11;
				//_cprintf("case 01\n");
				//	cout << "case 01" << endl;
			}
			else if (!inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6))//是否在初始界面
			{
				//尝试进入初始界面
				waitTime(500);
				getPos(pos_x, pos_y, HOME_BUTTON_X, HOME_BUTTON_Y, HOME_BUTTON_W, HOME_BUTTON_H);
				MouseLeftClick(pos_x, pos_y);//单击左上角的圆
				waitTime(1500);
				flag = 0;
				//	cout << "case 02" << endl;
				//_cprintf("case 02\n");
			}
			else
			{
				//单击出击按钮
				getPos(pos_x, pos_y, HOME_ATTACK_X, HOME_ATTACK_Y, HOME_ATTACK_W, HOME_ATTACK_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 1;
				//_cprintf("case 03\n");
				//	cout << "case 03" << endl;
			}
			break;
		case 11:
			//_cprintf("case 11\n");
			//	cout << "case 11" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				marchreturn_Check = 0;
				//_cprintf("case 11 1\n");
				//	cout << "case 11 1" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 12;
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 11 2\n");

				//	cout << "case 11 2" << endl;
				if (marchreturn_Check < 5){
					flag = 11;
					waitTime(1000);
					marchreturn_Check++;
				}
				else{
					waitTime(1000);
					flag = 0;
					marchreturn_Check = 0;
				}

			}
			break;
		case 12:
			//_cprintf("case 12\n");
			//cout << "case 12" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				//_cprintf("case 12 1\n");
				//	cout << "case 12 1" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 0;//处理完远征归来
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 12 2\n");
				//	cout << "case 12 2" << endl;
				flag = 12;
				waitTime(500);
			}
			break;
		case 1:
			//检出是否在出击三选一界面
			//_cprintf("case 1\n");
			//cout << "case 1" << endl;

			if (!inRightPos("attackbutton", hBitmap, ATTACK_BUTTON_CHOOSE_X, ATTACK_BUTTON_CHOOSE_Y, 10, 10))
			{
				//尝试进入初始界面
				if (attackbutton_Check < 5){
					flag = 1;
					attackbutton_Check++;
					//	cout << "case 11" << endl;
					waitTime(500);
					attackbutton_Check++;

				}
				else
				{
					flag = 0;
					attackbutton_Check = 0;
				}
				//_cprintf("case 11\n");
			}
			else
			{
				attackbutton_Check = 0;
				//单击远征按钮
				getPos(pos_x, pos_y, ATTACK_BUTTON_CHOOSE_X, ATTACK_BUTTON_CHOOSE_Y, ATTACK_BUTTON_CHOOSE_W, ATTACK_BUTTON_CHOOSE_H);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				flag = 2;
				//_cprintf("case 12\n");
				//	cout << "case 12" << endl;
			}
			break;
		case 2:
			//选择海域
			//_cprintf("case 2\n");
			//cout << "case 2" << endl;

			if (!inRightPos("attackareacheck", hBitmap, ATTACK_AREA_CHECK_X, ATTACK_AREA_CHECK_Y, 20, 10))
			{

				//尝试进入初始界面
				if (attackarea_Check < 10){
					flag = 2;
					attackarea_Check++;
				}
				else{
					flag = 1;
					attackarea_Check = 0;
				}
				//_cprintf("case 21\n");
				//	cout << "case 21" << endl;
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 22\n");
				attackarea_Check = 0;
				//单击海域
				getAttackAreaPos(area1, pos_x, pos_y);
				MouseLeftClick(pos_x, pos_y);
				waitTime(1000);
				//	cout << pos_x << "," << pos_y << endl;
				//单击远征号
				if (area2 <= 4){
					getAttackArea2Pos(area2, pos_x, pos_y);
					MouseLeftClick(pos_x, pos_y);
				}
				else
				{
					getPos(pos_x, pos_y, 693, 249, 38, 55);
					MouseLeftClick(pos_x, pos_y);
					waitTime(1000);
					getAttackAreaExPos(area2, pos_x, pos_y);
					MouseLeftClick(pos_x, pos_y);
				}
				waitTime(1000);
				//	cout << pos_x << "," << pos_y << endl;
				flag = 3;
				//_cprintf("case 22\n");
				//	cout << "case 22" << endl;
			}
			break;
		case 3:
			//_cprintf("case 3\n");
			if (!inRightPos("attackareaconfirm", hBitmap, ATTACK_AREACONFIRM_X, ATTACK_AREACONFIRM_Y, 10, 10))
			{
				//_cprintf("case 31\n");
				flag = 0;
				waitTime(1000);
			}
			else{
				//_cprintf("case 32\n");
				getPos(pos_x, pos_y, ATTACK_AREACONFIRM_X, ATTACK_AREACONFIRM_Y, ATTACK_AREACONFIRM_W, ATTACK_AREACONFIRM_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 4;
				waitTime(1000);
			}

			break; 
		case 4:
			//_cprintf("case 4\n");
			if (!inRightPos("atkok", hBitmap, 543, 445, 10, 10))
			{
				//_cprintf("case 41\n");
				flag = 4;
				waitTime(1000);
			}
			else if (inRightPos("you", hBitmap, MARCH_NEED_YOU1_X, MARCH_NEED_YOU1_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_YOU2_X, MARCH_NEED_YOU2_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_YOU3_X, MARCH_NEED_YOU3_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_YOU4_X, MARCH_NEED_YOU4_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_YOU5_X, MARCH_NEED_YOU5_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_YOU6_X, MARCH_NEED_YOU6_Y, 8, 9) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN1_X, MARCH_NEED_DAN1_Y, 2, 10) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN2_X, MARCH_NEED_DAN2_Y, 2, 10) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN3_X, MARCH_NEED_DAN3_Y, 2, 10) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN4_X, MARCH_NEED_DAN4_Y, 2, 10) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN5_X, MARCH_NEED_DAN5_Y, 2, 10) ||
				inRightPos("you", hBitmap, MARCH_NEED_DAN6_X, MARCH_NEED_DAN6_Y, 2, 10))
			{
				//_cprintf("case 42\n");
				getSupply(1);
				flag = 0;
				break;
			}
			else
			{
				//_cprintf("case 43\n");
				getPos(pos_x, pos_y, ATTACK_OUT_BUTTOM_X, ATTACK_OUT_BUTTOM_Y, ATTACK_OUT_BUTTOM_W, ATTACK_OUT_BUTTOM_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 5;
				waitTime(5000);
			}
			break;

		case 5:
			//_cprintf("case 5\n");
			if (inRightPos("atkok", hBitmap, 563, 445, 10, 10))
			{
				//_cprintf("case 51\n");
				flag = 4;//!!!!!!!!!!!!!!!!
			}
			else
			{
				//_cprintf("case 52\n");
				flag = 6;
			}
			break;

		case 6:
			//_cprintf("case 6\n");
			if (inRightPos("zhenxing1", hBitmap, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, 20, 10))
			{
				//_cprintf("case 61\n");
				getZhenXingPos(zhenxing, pos_x, pos_y, hBitmap);
				MouseLeftClick(pos_x, pos_y);
				flag = 6;
				waitTime(1000);
			}
			else if (inRightPos("luopan", hBitmap, ATK_LUOPAN_X, ATK_LUOPAN_Y, 10, 10)){
				getPos(pos_x, pos_y, 330, 152, 158, 168);
				MouseLeftClick(pos_x, pos_y);
				flag = 6;
				waitTime(1000);
			}
			else if (inRightPos("atkchuiji", hBitmap, ATK_ZHUIJI_X, ATK_ZHUIJI_Y, 10, 10))//入夜选择
			{
				//_cprintf("case 62\n");
				flag = 8;
			}
			else if (inRightPos("atklv2", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5) || inRightPos("atklv3", hBitmap, ATK_LV3_X, ATK_LV3_Y, 10, 10, 0.5) || inRightPos("atklv12", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5)){
				//_cprintf("case 63\n");
				flag = 9;
			}
			else{
				//_cprintf("case 64\n");
				waitTime(1000);
			}
			break;
		//case 7:
		//	//_cprintf("case 7\n");
		//	if (inRightPos("atkchuiji", hBitmap, ATK_ZHUIJI_X, ATK_ZHUIJI_Y, 10, 10))//入夜选择
		//	{
		//		//_cprintf("case 71\n");
		//		flag = 8;
		//	}
		//	else{
		//		//_cprintf("case 72\n");
		//		waitTime(1000);
		//	}
		//	break;
		case 8:
			//_cprintf("case 8\n");
			if (!atkHd->m_Night){
				//_cprintf("case 81\n");
				getPos(pos_x, pos_y, 260, 210, 66, 55);//不入夜
				MouseLeftClick(pos_x, pos_y);
				flag = 101;
			}
			else{
				//_cprintf("case 82\n");
				getPos(pos_x, pos_y, 477, 212, 62, 56);//入夜
				MouseLeftClick(pos_x, pos_y);
				flag = 101;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			waitTime(1000);
			break;
		case 101:
			if (inRightPos("atkchuiji", hBitmap, ATK_ZHUIJI_X, ATK_ZHUIJI_Y, 10, 10))//入夜选择
			{
				//_cprintf("case 101 1\n");
				if (!atkHd->m_Night){
					//_cprintf("case 101 1\n");
					getPos(pos_x, pos_y, 260, 210, 66, 55);//不入夜
					MouseLeftClick(pos_x, pos_y);
					flag = 101;
				}
				else{
					//_cprintf("case 101 2\n");
					getPos(pos_x, pos_y, 477, 212, 62, 56);//入夜
					MouseLeftClick(pos_x, pos_y);
					flag = 101;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
				waitTime(1000);
			}
			else{
				if (!atkHd->m_Night){
					//_cprintf("case 101 3\n");
					flag = 9;
				}
				else{
					//_cprintf("case 101 4\n");
					flag = 6;
				}
			}
			break;
		case 9:
			//_cprintf("case 9\n");
			if (inRightPos("atklv2", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5) || inRightPos("atklv3", hBitmap, ATK_LV3_X, ATK_LV3_Y, 10, 10, 0.5) || inRightPos("atklv12", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5))
			{
				//_cprintf("case 91\n");
				getPos(pos_x, pos_y, ATK_NEXT_X, ATK_NEXT_Y, ATK_NEXT_W, ATK_NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 102;
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 92\n");
				flag = 9;
				waitTime(1000);
			}
			break;
		case 102:
			atkNext2_Check = 0;
			if (inRightPos("atklv2", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5) || inRightPos("atklv3", hBitmap, ATK_LV3_X, ATK_LV3_Y, 10, 10, 0.5) || inRightPos("atklv12", hBitmap, ATK_LV2_X, ATK_LV2_Y, 10, 10, 0.5)){
				getPos(pos_x, pos_y, ATK_NEXT_X, ATK_NEXT_Y, ATK_NEXT_W, ATK_NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 102;
				waitTime(1000);
				//_cprintf("case 102 1\n");
			}
			else
			{
				flag = 10;
				//_cprintf("case 102 2\n");
			}
			break;
		case 10:
			//_cprintf("case 10\n");
			if (inRightPos("atklv", hBitmap, ATK_LV_X, ATK_LV_Y, 10, 10, 0.6))
			{
				//_cprintf("case 10 1\n");
				//分析破损情况！！！！！
				getPos(pos_x, pos_y, ATK_NEXT2_X, ATK_NEXT2_Y, ATK_NEXT2_W, ATK_NEXT2_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 103;
				waitTime(1000);
			}
			else
			{
				if (atkNext2_Check > 10)
				{
					flag = 102;
					atkNext2_Check = 0;
					//_cprintf("case 10 2\n");
				}
				else{
					flag = 10;
					atkNext2_Check++;
					//_cprintf("case 10 3\n");
				}
				waitTime(1000);
			}
			break;
		case 103:
			atkNext_Check = 0;
			if (inRightPos("atklv", hBitmap, ATK_LV_X, ATK_LV_Y, 10, 10, 0.6))
			{
				//_cprintf("case 103 1\n");
				//分析破损情况！！！！！
				getPos(pos_x, pos_y, ATK_NEXT2_X, ATK_NEXT2_Y, ATK_NEXT2_W, ATK_NEXT2_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 103;
				waitTime(1000);
			}
			else{
				//_cprintf("case 103 2\n");
				flag = 14;
			}
			break;
		case 14:
			//_cprintf("case 14\n");
			if (inRightPos("marchreturn", hBitmap, MARCH_RETURN_X, MARCH_RETURN_Y, 10, 10))//检查到有远征归来
			{
				//单击任意一处
				waitTime(500);
				getPos(pos_x, pos_y, 50, 50, 600, 300);
				MouseLeftClick(pos_x, pos_y);
				waitTime(4000);
				flag = 111;
				//_cprintf("case 14 6\n");
				//	cout << "case 01" << endl;
			}
			else if (inRightPos("atkgetship", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5) || inRightPos("atkgetship2", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5) || inRightPos("atkgetship3", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5))
			{
				//_cprintf("case 14 1\n");
				getPos(pos_x, pos_y, ATK_GETSHIP_X, ATK_GETSHIP_Y, ATK_GETSHIP_W, ATK_GETSHIP_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 104;
				waitTime(1000);
			}
			else if (inRightPos("atkcontinue", hBitmap, ATK_CONTINUE_X, ATK_CONTINUE_Y, 10, 10))
			{
				//_cprintf("case 14 2\n");
				flag = 15;
			}
			else if (inRightPos("homeconfirm", hBitmap, HOME_CONFIRM_X, HOME_CONFIRM_Y, 10, 10, 0.6)){
				//_cprintf("case 14 5\n");
				flag = 16;
				waitTime(1000);

			}
			else
			{ 
				if (atkNext_Check > 10){
					//_cprintf("case 14 3\n");
					flag = 103;
					atkNext_Check = 0;
				}
				else{
					flag = 14;
					//_cprintf("case 14 4 %d\n", atkNext_Check);
					atkNext_Check++;
				}
				waitTime(1000);
			}
			break;
		case 111:
			//_cprintf("case 111\n");
			//	cout << "case 11" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				marchreturn_Check = 0;
				//_cprintf("case 111 1\n");
				//	cout << "case 11 1" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 112;
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 111 2\n");

				//	cout << "case 11 2" << endl;
				if (marchreturn_Check < 5){
					flag = 111;
					waitTime(1000);
					marchreturn_Check++;
				}
				else{
					waitTime(1000);
					flag = 14;
					marchreturn_Check = 0;
				}

			}
			break;
		case 112://???????
			//_cprintf("case 112\n");
			//cout << "case 12" << endl;
			if (inRightPos("next", hBitmap, NEXT_X, NEXT_Y, 10, 10) && !inRightPos("marchreturn1", hBitmap, MARCH_RETURN1_X, MARCH_RETURN1_Y, 10, 10))
			{
				//_cprintf("case 112 1\n");
				//	cout << "case 12 1" << endl;
				//点击“次”
				getPos(pos_x, pos_y, NEXT_X, NEXT_Y, NEXT_W, NEXT_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 14;//处理完远征归来
				waitTime(1000);
			}
			else
			{
				//_cprintf("case 112 2\n");
				//	cout << "case 12 2" << endl;
				flag = 112;
				waitTime(500);
			}
			break;
		case 104:
			if (inRightPos("atkgetship", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5) || inRightPos("atkgetship2", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5) || inRightPos("atkgetship3", hBitmap, ATK_GETSHIP_X, ATK_GETSHIP_Y, 10, 10, 0.5))
			{
				//_cprintf("case 14 1\n");
				getPos(pos_x, pos_y, ATK_GETSHIP_X, ATK_GETSHIP_Y, ATK_GETSHIP_W, ATK_GETSHIP_H);
				MouseLeftClick(pos_x, pos_y);
				flag = 104;
				waitTime(1000);
			}
			else{
				flag = 15;
			}
			break;
		case 15:
			//_cprintf("case 15\n");
			atkCountNow--;
			if (atkCountNow > 0)
			{
				//_cprintf("case 15 1\n");
				getPos(pos_x, pos_y, ATK_CONTINUE_X, ATK_CONTINUE_Y, ATK_CONTINUE_W, ATK_CONTINUE_H);//继续
				MouseLeftClick(pos_x, pos_y);
				flag = 6;
				waitTime(1000);
			}
			else{
				atkCountNow = atkCount;
				//_cprintf("case 15 2\n");
				getPos(pos_x, pos_y, 473, 214, 79, 50);//回港
				MouseLeftClick(pos_x, pos_y);
				waitTime(3000);
				flag = 16;
			}
			break;		
		case 16:
			//_cprintf("case 16\n");
			getSupply(1);
			if (atkHd->m_InfiAtk)
			{
				//_cprintf("case 16 1\n");
				flag = 0;
			}
			else if (atkTimes > 0)
			{
				atkHd->m_AtkNum++;
				atkTimes--;
				atkCountNow = atkCount;
				//_cprintf("case 16 3\n");
				flag = 0;
			}
			else{
				//_cprintf("case 16 2\n");

				((CEdit*)atkHd->GetDlgItem(IDC_AtkStop))->EnableWindow(FALSE);
				((CEdit*)atkHd->GetDlgItem(IDC_AtkStart))->EnableWindow(TRUE);
				((CEdit*)atkHd->GetDlgItem(IDC_AREA1))->EnableWindow(TRUE);
				((CEdit*)atkHd->GetDlgItem(IDC_AREA2))->EnableWindow(TRUE);
				critical_section.Unlock();
				return 0;
			}
			//atkHd->UpdateData(false);
			waitTime(atk_time);
			break;
		}
	}
	critical_section.Unlock();
	//_cprintf("atk unlock\n");
	return 0;
}


void getAttackAreaPos(int area1, int &pos_x, int &pos_y)
{

	switch (area1)
	{
	case 1:
		getPos(pos_x, pos_y, 127, 446, 55, 12);
		break;
	case 2:
		getPos(pos_x, pos_y, 203, 446, 52, 12);
		break;
	case 3:
		getPos(pos_x, pos_y, 283, 448, 51, 11);
		break;
	case 4:
		getPos(pos_x, pos_y, 352, 447, 50, 12);
		break;
	case 5:
		getPos(pos_x, pos_y, 427, 446, 50, 13);
		break;
	case 6:
		getPos(pos_x, pos_y, 504, 448, 50, 11);
		break;
	default :
		break;
	}
}

void getAttackArea2Pos(int area2, int &pos_x, int &pos_y)
{
	switch (area2)
	{
	case 1:
		getPos(pos_x, pos_y, 141, 149, 275, 108);
		break;
	case 2:
		getPos(pos_x, pos_y, 474, 149, 192, 107);
		break;
	case 3:
		getPos(pos_x, pos_y, 143, 293, 275, 108);
		break;
	case 4:
		getPos(pos_x, pos_y, 470, 290, 192, 107);
		break;
	default:
		break;
	}
}

void getAttackAreaExPos(int area2, int &pos_x, int &pos_y)
{
	switch (area2)
	{
	case 5:
		getPos(pos_x, pos_y, 205, 151, 487, 106);
		break;
	case 6:
		getPos(pos_x, pos_y, 200, 293, 495, 101);
		break;
	default:
		break;
	}
}

void getZhenXingPos(int zhenxing, int &pos_x, int &pos_y, HBITMAP &hbmp)
{
	switch (zhenxing)
	{
	case 1:
		getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, ATK_ZHENGXING_CHOOSE1_W, ATK_ZHENGXING_CHOOSE1_H);
		break;
	case 2:
		if (inRightPos("zhenxing2", hbmp, ATK_ZHENGXING_CHOOSE2_X, ATK_ZHENGXING_CHOOSE2_Y, 10, 10))
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE2_X, ATK_ZHENGXING_CHOOSE2_Y, ATK_ZHENGXING_CHOOSE2_W, ATK_ZHENGXING_CHOOSE2_H);
		else
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, ATK_ZHENGXING_CHOOSE1_W, ATK_ZHENGXING_CHOOSE1_H);
		break;
	case 3:
		if (inRightPos("zhenxing3", hbmp, ATK_ZHENGXING_CHOOSE3_X, ATK_ZHENGXING_CHOOSE3_Y, 10, 10))
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE3_X, ATK_ZHENGXING_CHOOSE3_Y, ATK_ZHENGXING_CHOOSE3_W, ATK_ZHENGXING_CHOOSE3_H);
		else
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, ATK_ZHENGXING_CHOOSE1_W, ATK_ZHENGXING_CHOOSE1_H);
		break;
	case 4:
		if (inRightPos("zhenxing4", hbmp, ATK_ZHENGXING_CHOOSE4_X, ATK_ZHENGXING_CHOOSE4_Y, 10, 10))
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE4_X, ATK_ZHENGXING_CHOOSE4_Y, ATK_ZHENGXING_CHOOSE4_W, ATK_ZHENGXING_CHOOSE4_H);
		else
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, ATK_ZHENGXING_CHOOSE1_W, ATK_ZHENGXING_CHOOSE1_H);
		break;
	case 5:
		if (inRightPos("zhenxing5", hbmp, ATK_ZHENGXING_CHOOSE5_X, ATK_ZHENGXING_CHOOSE5_Y, 10, 10))
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE5_X, ATK_ZHENGXING_CHOOSE5_Y, ATK_ZHENGXING_CHOOSE5_W, ATK_ZHENGXING_CHOOSE5_H);
		else
			getPos(pos_x, pos_y, ATK_ZHENGXING_CHOOSE1_X, ATK_ZHENGXING_CHOOSE1_Y, ATK_ZHENGXING_CHOOSE1_W, ATK_ZHENGXING_CHOOSE1_H);
		break;
	}
}