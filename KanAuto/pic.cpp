#include "stdafx.h"
#include "global.h"
#include "pic.h"

using namespace std;



void down(CImage &image, int x, int y, int w, int h, char filename[])
{
	
	CImage newImage;
	newImage.Create(w, h, image.GetBPP());
	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			newImage.SetPixel(i, j, image.GetPixel(i+x, j+y));
		}
	char name[100] = PICPATH;
	strcat_s(name, filename);
	strcat_s(name, ".bmp");
	
	newImage.Save(CString(name));
//	newImage.Save(_T("e://pic//f.jpg"));
}



void copy(CImage &image, CImage &newImage){
	newImage.Create(image.GetWidth(), image.GetHeight(), image.GetBPP());
	int maxY = image.GetHeight();
	int maxX = image.GetWidth();
	for (int i = 0; i < maxX; i++)
		for (int j = 0; j < maxY; j++)
		{
			newImage.SetPixel(i, j, image.GetPixel(i, j));
		}
	//newImage.Save(_T("e://pic//D.jpg"));
}

double picCompare(CImage &image, CImage &image2, int xS, int yS, int Xn, int Yn)//image为全屏截图，image2为文件。xS yS为原点，Xn Yn为检查像素点个数
{
	int maxY = image2.GetHeight();
	int maxX = image2.GetWidth();
	//assert(maxY == h);
	//assert(maxX == w);

	if (maxY < Yn)
		Yn = maxY;
	if (maxX < Xn)
		Xn = maxX;
	double X_Next = (double)maxX / Xn;
	double Y_Next = (double)maxY / Yn;

	COLORREF pixel, pixel2;
	int count = 0, all = 0;
	for (double x = 0; x<maxX; x += X_Next)
	{
		for (double y = 0; y<maxY; y += Y_Next)
		{	
			pixel = image.GetPixel((int)(x+xS), (int)(y+yS));
			pixel2 = image2.GetPixel((int)x, (int)y);
			if (pixel == pixel2)
				count++;
			all++;
		}
	}
	//cout<<count<<endl<<all<<endl<<(double)count * 100 / all << " %" << endl;
	return (double)count / all;
}