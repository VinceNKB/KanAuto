#include "stdafx.h"
#include "global.h"
#include "pic.h"
#include "ScreenCapture.h"

using namespace std;

HWND IESHwnd;
HWND KCVHwnd;
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	printf("%s", "abc");

}

bool getHWND()
{
	KCVHwnd = FindWindowEx(NULL, NULL, NULL, _T("提督業も忙しい！"));//注意窗口不能最小化 
	if (KCVHwnd == NULL)
	{
		//cout << "找不到提督業も忙しい！" << endl;
		return FALSE;
	}

	if (!EnumChildWindows(KCVHwnd, FindChildWnd, 0))
		return FALSE;
	return TRUE;
}


void getImageWhole(HWND hwnd)
{
	RECT rc;
	GetClientRect(hwnd, &rc);
	//创建 

	HDC hdcScreen = GetDC(NULL);//创建屏幕DC
	HDC hdc = CreateCompatibleDC(hdcScreen);//创建内存DC  
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);//创建兼容位图 
	(HBITMAP)SelectObject(hdc, hbmp); //把位图选进内存DC    

	//复制 
	PrintWindow(hwnd, hdc, PW_CLIENTONLY);
	//PW_CLIENTONLY：Only the client area of the window is copied to hdcBlt. 
	//By default, the entire window is copied.   
	//PW_CLIENTONLY表示仅仅拷贝窗口的客户区域，而默认情况下，执行printwindow会拷贝整个窗口
	CImage image;
	image.Attach(hbmp);
	image.Save(_T("E://1111.bmp"));//如果文件后缀为.bmp，则保存为为bmp格式  
	//down(image, HOME_NAME_X, HOME_NAME_Y, HOME_NAME_W, HOME_NAME_H, HOME_NAME_PID);
	//down(image, 1, 1, 100, 100, "ddddd");

	image.Detach();
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);
}


HBITMAP getScreen(HWND hwnd){
	RECT rc;
	GetClientRect(hwnd, &rc);
	//创建 
	HBITMAP  hBitmap, hOldBitmap;
	HDC hdcScreen = GetDC(NULL);//创建屏幕DC
	HDC hdc = CreateCompatibleDC(hdcScreen);//创建内存DC  
	hBitmap = CreateCompatibleBitmap(hdcScreen, rc.right - rc.left, rc.bottom - rc.top);//创建兼容位图 
	hOldBitmap = (HBITMAP)SelectObject(hdc, hBitmap); //把位图选进内存DC    

	//复制 
	PrintWindow(hwnd, hdc, PW_CLIENTONLY);
	//PW_CLIENTONLY：Only the client area of the window is copied to hdcBlt. 
	//By default, the entire window is copied.   
	//PW_CLIENTONLY表示仅仅拷贝窗口的客户区域，而默认情况下，执行printwindow会拷贝整个窗口

	hBitmap = (HBITMAP)SelectObject(hdc, hOldBitmap);
	//清除 
	DeleteDC(hdc);
	DeleteObject(hOldBitmap);
	ReleaseDC(NULL, hdcScreen);
	return hBitmap;
}


void SCapture(HWND hwnd){
	
	HBITMAP hBitmap = getScreen(hwnd);
	if (inRightPos("home_attack", hBitmap, HOME_ATTACK_X, HOME_ATTACK_Y, 10, 10))
		cout << "ok" << endl;
	else
		cout << "no" << endl;
}

bool inRightPos(char picname[], HBITMAP &hbmp, int xS, int yS, int Xn, int Yn, double d)
{
	char name[100] = PICPATH;
	strcat_s(name, picname);
	strcat_s(name, ".bmp");

	CImage image, image2;
	image2.Load(CString(name));
	//image2.Load(_T("e://pic//marchgoconfirm.bmp"));
	image2.GetPixel(1, 1);
	image.Attach(hbmp);

	double result = picCompare(image, image2, xS, yS, Xn, Yn);
	image.Detach();
	image2.Destroy();
	image.Destroy();
	//cout << result << endl;
	return d <= result;
	return true;
}

BOOL CALLBACK FindChildWnd(HWND hWnd, LPARAM lParam)
{
	wchar_t str[50];
	GetClassName(hWnd, str, 50);
	if (wcscmp(str, _T("Internet Explorer_Server")) == 0)
	{
		IESHwnd = hWnd;
	}
	return true;
}




void getImage()
{
	CImage image;

	image.Load(_T("E://1111.bmp"));
	//home.bmp
	down(image, 543, 445, 146, 17, "test_atk");
	//down(image, HOME_ARMY_X, HOME_ARMY_Y, HOME_ARMY_W, HOME_ARMY_H, HOME_ARMY_PID);
	//down(image, HOME_MODIFY_X, HOME_MODIFY_Y, HOME_MODIFY_W, HOME_MODIFY_H, HOME_MODIFY_PID);
	//down(image, HOME_FACTORY_X, HOME_FACTORY_Y, HOME_FACTORY_W, HOME_FACTORY_H, HOME_FACTORY_PID);
	//down(image, HOME_REPAIR_X, HOME_REPAIR_Y, HOME_REPAIR_W, HOME_REPAIR_H, HOME_REPAIR_PID);
	//down(image, HOME_FOOD_X, HOME_FOOD_Y, HOME_FOOD_W, HOME_FOOD_H, HOME_FOOD_PID);

	//function2.bmp
	//down(image, FUNC_ARMY_X, FUNC_ARMY_Y, FUNC_ARMY_W, FUNC_ARMY_H, FUNC_ARMY_PID);

	//function.bmp
	/*down(image, FUNC_FOOD_X, FUNC_FOOD_Y, FUNC_FOOD_W, FUNC_FOOD_H, FUNC_FOOD_PID);
	down(image, FUNC_MODIFY_X, FUNC_MODIFY_Y, FUNC_MODIFY_W, FUNC_MODIFY_H, FUNC_MODIFY_PID);
	down(image, FUNC_REPAIR_X, FUNC_REPAIR_Y, FUNC_REPAIR_W, FUNC_REPAIR_H, FUNC_REPAIR_PID);
	down(image,FUNC_FACTORY_X, FUNC_FACTORY_Y, FUNC_FACTORY_W, FUNC_FACTORY_H, FUNC_FACTORY_PID);*/

	//func_food1.bmp
	//down(image, FOOD_FLEET1_X, FOOD_FLEET1_Y, FOOD_FLEET1_W, FOOD_FLEET1_H, FOOD_FLEET1_PID);

	//func_food2.bmp
	//down(image, FOOD_FLEET2_X, FOOD_FLEET2_Y, FOOD_FLEET2_W, FOOD_FLEET2_H, FOOD_FLEET2_PID);

	//func_food1.bmp  //func_food_en.bmp 
	//down(image, FOOD_FLEET_ALL_X, FOOD_FLEET_ALL_Y, FOOD_FLEET_ALL_W, FOOD_FLEET_ALL_H, FOOD_FLEET_ALL_DISABLE);//FOOD_FLEET_ALL_ENABLE

	//func_food1.bmp   //func_food_en.bmp 
	//down(image, FOOD_FLEET_BUTTON_X, FOOD_FLEET_BUTTON_Y, FOOD_FLEET_BUTTON_W, FOOD_FLEET_BUTTON_H, FOOD_FLEET_BUTTON_DISABLE);//FOOD_FLEET_BUTTON_ENABLE


	//marchreturn.bmp
	//down(image, MARCH_RETURN_X, MARCH_RETURN_Y, MARCH_RETURN_W, MARCH_RETURN_H, MARCH_RETURN_PID);

	//marchreturnsuccess.bmp
	//down(image, MARCH_RETURN_SU_X, MARCH_RETURN_SU_Y, MARCH_RETURN_SU_W, MARCH_RETURN_SU_H, MARCH_RETURN_SU_PID);

	//attack_3to1
	//down(image, MARCH_CHOOSE_X, MARCH_CHOOSE_Y, MARCH_CHOOSE_W, MARCH_CHOOSE_H, MARCH_CHOOSE_PID);
	//down(image, MARCH_NEED_YOU_X, MARCH_NEED_YOU_Y, MARCH_NEED_YOU_W, MARCH_NEED_YOU_H, "you");
	//down(image, MARCH_NEED_DAN_X, MARCH_NEED_DAN_Y, MARCH_NEED_DAN_W, MARCH_NEED_DAN_H, "dan");
}
