
// KanAuto.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKanAutoApp: 
// �йش����ʵ�֣������ KanAuto.cpp
//

class CKanAutoApp : public CWinApp
{
public:
	CKanAutoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKanAutoApp theApp;