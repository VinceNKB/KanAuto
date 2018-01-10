#include "stdafx.h"
#include "global.h"
#include <Windows.h>
#include "FakeMin.h"
#include "conio.h"

volatile bool p_fakeMin = false;
static int win_x, win_y, win_w, win_h;
static int ScrWidth = 1920, ScrHeight = 1080;
static int WinState = 0;//0 正常 1 最小化

UINT FakeMin(LPVOID lpParam)
{
	while (p_fakeMin)
	{
		if (IsIconic(KCVHwnd))
		{
			//if (WinState == 0){
			//	cout << "MIN" << endl;
			//	_cprintf("fakeMinOn\n");
				WinState = 1;
				fakeMinOn();
			//}
		}
		else if (!isShift && GetForegroundWindow() == KCVHwnd)
		{
			if (WinState == 1){
			//	cout << "MAX" << endl;
			//	_cprintf("fakeMinOff\n");
				fakeMinOff();
				WinState = 0;
			}
		}
		Sleep(200);
	}
	return 0;
}

void fakeMinOn()
{
	//cout << "fakeMinOn" << endl;
	SendMessage(KCVHwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
	LPRECT lprect = new RECT();
	GetWindowRect(KCVHwnd, lprect);
	//cout << (long)lprect->left << " " << (long)lprect->top << " " << (long)lprect->right << " " << (long)lprect->bottom << endl;
	win_x = lprect->left;
	win_y = lprect->top;
	win_w = lprect->right - lprect->left;
	win_h = lprect->bottom - lprect->top;
	free(lprect);
	SetWindowPos(KCVHwnd, HWND_BOTTOM, ScrWidth + 1, ScrHeight + 1, win_w, win_h, SWP_NOSIZE);
	//SetWindowPos(KCVHwnd, HWND_BOTTOM, 0, 0, win_w, win_h, SWP_NOSIZE);
}

void fakeMinOff()
{
	//cout << "fakeMinOff" << endl;
	SetWindowPos(KCVHwnd, HWND_TOP, win_x, win_y, win_w, win_h, SWP_NOSIZE);
}

void shiftOut()
{
	SetWindowPos(KCVHwnd, HWND_BOTTOM, ScrWidth + 1, ScrHeight + 1, 0, 0, SWP_NOSIZE);
}

void shiftIn()
{
	win_x = 0;
	win_y = 0;
	SetWindowPos(KCVHwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE);
}

bool isInDes()
{
	bool rt;
	LPRECT lprect = new RECT();
	GetWindowRect(KCVHwnd, lprect);
	//cout << (long)lprect->left << " " << (long)lprect->top << " " << (long)lprect->right << " " << (long)lprect->bottom << endl;
	if (lprect->left < ScrWidth && win_y < ScrHeight)
	{
		rt = false;
	}
	else{
		rt = true;
	}
	free(lprect);
	return rt;
}

void finalFakeMin()//被老板发现怎么办？？
{
	if (!isInDes())
		SetWindowPos(KCVHwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOSIZE);
}