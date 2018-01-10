// KanAtk.cpp : 实现文件
//

#include "stdafx.h"
#include "KanAuto.h"
#include "KanAtk.h"
#include "afxdialogex.h"
#include "global.h"
#include "conio.h"
#include "robo.h"


volatile bool AtkOn = false;
// KanAtk 对话框
threadStartMarch threadInfoAtk;

IMPLEMENT_DYNAMIC(KanAtk, CDialogEx)

KanAtk::KanAtk(CWnd* pParent /*=NULL*/)
	: CDialogEx(KanAtk::IDD, pParent)
	, m_Area1(0)
	, m_Area2(0)
	, m_AtkCount(0)
	, m_AtkNum(0)
	, m_AtkWait(0)
	, m_InfiAtk(FALSE)
	, m_Night(FALSE)
	, m_Zhenxing(0)
	, m_atkTimes(0)
{
	m_Area1 = 1;
	m_Area2 = 1;
	m_AtkCount = 1;
	m_atkTimes = 1;
	m_Zhenxing = 1;
	m_AtkWait = 5;
}

KanAtk::~KanAtk()
{
}

void KanAtk::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AREA1, m_Area1);
	//  DDV_MinMaxInt(pDX, m_Area1, 1, 6);
	//  DDX_Text(pDX, IDC_ADDX_Text(pDX, IDC_AREA1, m_Area1);REA2, m_Area);
	DDX_Text(pDX, IDC_AREA2, m_Area2);
	DDV_MinMaxInt(pDX, m_Area2, 1, 6);
	DDX_Control(pDX, IDC_AtkStart, m_AtkStart);
	DDX_Control(pDX, IDC_AtkStop, m_AtkStop);
	DDX_Text(pDX, IDC_AtkCount, m_AtkCount);
	DDX_Text(pDX, IDC_AtkNum, m_AtkNum);
	DDX_Text(pDX, IDC_AtkWait, m_AtkWait);
	DDX_Check(pDX, IDC_InfiAtk, m_InfiAtk);
	DDX_Check(pDX, IDC_Night, m_Night);
	DDX_Text(pDX, IDC_Zhenxing, m_Zhenxing);
	DDV_MinMaxInt(pDX, m_Zhenxing, 1, 5);
	DDX_Text(pDX, IDC_ATKTIMES, m_atkTimes);
	DDV_MinMaxInt(pDX, m_atkTimes, 0, 100);
}


BEGIN_MESSAGE_MAP(KanAtk, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AtkStart, &KanAtk::OnBnClickedAtkstart)
	ON_BN_CLICKED(IDC_AtkStop, &KanAtk::OnBnClickedAtkstop)
	ON_BN_CLICKED(IDC_Night, &KanAtk::OnBnClickedNight)
	ON_BN_CLICKED(IDC_InfiAtk, &KanAtk::OnBnClickedInfiatk)
//	ON_EN_CHANGE(IDC_AtkCount, &KanAtk::OnEnChangeAtkcount)
//	ON_WM_TIMER()
//	ON_EN_CHANGE(IDC_Zhenxing, &KanAtk::OnEnChangeZhenxing)
//	ON_EN_CHANGE(IDC_ATKTIMES, &KanAtk::OnEnChangeAtktimes)
//	ON_EN_CHANGE(IDC_AREA1, &KanAtk::OnEnChangeArea1)
END_MESSAGE_MAP()


// KanAtk 消息处理程序



void KanAtk::OnCancel()
{
	//CDialogEx::OnCancel();
	return;
}


void KanAtk::OnOK()
{
	//CDialogEx::OnOK();
	return;
}



void KanAtk::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(IDCANCEL);
	CDialog::OnClose();
	//CDialogEx::OnClose();
}


void KanAtk::OnBnClickedAtkstart()
{
	//SetTimer(1, 500, NULL);
	AtkOn = TRUE;
	
	UpdateData(true);
	m_AtkNum = 0;
	if (m_AtkCount == 0)
		m_AtkCount = 1;
	UpdateData(false);

	threadInfoAtk.area1 = m_Area1;
	threadInfoAtk.area2 = m_Area2;
	threadInfoAtk.waitTime = m_AtkWait;
	threadInfoAtk.atkHd = this;
	threadInfoAtk.atkCount = m_AtkCount;
	threadInfoAtk.zhenxing = m_Zhenxing;
	threadInfoAtk.atkTimes = m_atkTimes;

	AfxBeginThread(p_Attck, &threadInfoAtk);

	((CEdit*)GetDlgItem(IDC_AREA1))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_AREA2))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_AtkStop))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_AtkStart))->EnableWindow(FALSE);
	// TODO:  在此添加控件通知处理程序代码
}


void KanAtk::OnBnClickedAtkstop()
{
	KillTimer(1);
	UpdateData(true);
	if (m_AtkNum == 0)
		m_AtkNum = 1;
	UpdateData(false);

	AtkOn = FALSE;
	((CEdit*)GetDlgItem(IDC_AREA1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_AREA2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_AtkStop))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_AtkStart))->EnableWindow(TRUE);
	// TODO:  在此添加控件通知处理程序代码
}



void KanAtk::OnBnClickedNight()
{
	UpdateData(true);
	// TODO:  在此添加控件通知处理程序代码
}


void KanAtk::OnBnClickedInfiatk()
{
	UpdateData(true);
	// TODO:  在此添加控件通知处理程序代码
}



//void KanAtk::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//		switch (nIDEvent)
//		{
//		case 1:
//			UpdateData(false);
//			
//		}
//	CDialogEx::OnTimer(nIDEvent);
//}

