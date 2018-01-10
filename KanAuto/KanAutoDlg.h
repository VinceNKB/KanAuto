
// KanAutoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CKanAutoDlg 对话框
class CKanAutoDlg : public CDialogEx
{
// 构造
public:
	CKanAutoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_KANAUTO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CWinThread* pTMarch1;
	CWinThread* pTMarch2;
	CWinThread* pTMarch3;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeHour1();
	afx_msg void OnEnChangeMin1();
	afx_msg void OnBnClickedTimer1();
//	CString m_Hour1;
	int m_Hour1;
	int m_Hour2;
	int m_Hour3;
//	int m_Min;
	int m_Min1;
	int m_Min2;
	int m_Min3;
	int m_Sec1;
	int m_Sec2;
	int m_Sec3;
	CButton m_Stop1;
	CButton m_Stop2;
	CButton m_Stop3;
//	CButton m_Start;
	CButton m_Start2;
	CButton m_Start1;
	CButton m_Start3;
	afx_msg void OnBnClickedTimer2();
	afx_msg void OnBnClickedStop1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_MarchNo;
	int m_MarchNo1;
	int m_MarchNo2;
	int m_MarchNo3;
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedTimer3();
	afx_msg void OnBnClickedStop2();
	afx_msg void OnBnClickedStop3();
	afx_msg void OnStnClickedHandlestate();
//	CString m_HandleState;
	CButton m_GetHandle;
	afx_msg void OnBnClickedHandle();
//	CStatic m_HandleState;
	afx_msg void OnEnChangeMarchno1();
	afx_msg void OnEnChangeMarchno2();
	afx_msg void OnEnChangeMarchno3();
	int m_marchcount1;
	int m_marchcount2;
	int m_marchcount3;
	afx_msg void OnEnChangeSec1();
	afx_msg void OnEnChangeHour2();
	afx_msg void OnEnChangeMin2();
	afx_msg void OnEnChangeSec2();
	afx_msg void OnEnChangeHour3();
	afx_msg void OnEnChangeMin3();
	afx_msg void OnEnChangeSec3();
	CButton m_Shift;
	afx_msg void OnBnClickedShitf();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_AtkDlg;
	afx_msg void OnBnClickedAtkdlg();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedTest();
};
