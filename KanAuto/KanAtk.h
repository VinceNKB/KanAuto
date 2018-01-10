#pragma once
#include "Resource.h"
#include "afxwin.h"
// KanAtk 对话框

class KanAtk : public CDialogEx
{
	DECLARE_DYNAMIC(KanAtk)

public:
	KanAtk(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~KanAtk();

// 对话框数据
	enum { IDD = IDD_ATKDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	int m_Area1;
	int m_Area2;
	CButton m_AtkStart;
	CButton m_AtkStop;
	int m_AtkCount;
	int m_AtkNum;
	int m_AtkWait;
	BOOL m_InfiAtk;
	BOOL m_Night;
	afx_msg void OnBnClickedAtkstart();
	afx_msg void OnBnClickedAtkstop();
	afx_msg void OnBnClickedNight();
	afx_msg void OnBnClickedInfiatk();
	afx_msg void OnEnChangeAtkcount();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_Zhenxing;
	int m_atkTimes;
	afx_msg void OnEnChangeZhenxing();
	afx_msg void OnEnChangeAtktimes();
	afx_msg void OnEnChangeArea1();
};
