
// KanAutoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KanAuto.h"
#include "KanAutoDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "ScreenCapture.h"
#include "robo.h"
#include "conio.h"
#include "FakeMin.h"
#include "KanAtk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

time_t t_clock1;
time_t t_clock2;
time_t t_clock3;

const static int MARCH_RANDOM = 300;
//int marchcount1 = 0;
//int marchcount2 = 0;
//int marchcount3 = 0;

volatile bool march1Run = false;
volatile bool march2Run = false;
volatile bool march3Run = false;
bool atkDlgOn = false;
bool isShift = false;
KanAtk *kanAtk = NULL;


threadStartMarch threadInfo;
threadStartMarch threadInfo2;
threadStartMarch threadInfo3;

CCriticalSection critical_section;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKanAutoDlg �Ի���



CKanAutoDlg::CKanAutoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKanAutoDlg::IDD, pParent)
	, m_Hour1(0)
	, m_Hour2(0)
	, m_Hour3(0)
	, m_Min1(0)
	, m_Min2(0)
	, m_Min3(0)
	, m_Sec1(0)
	, m_Sec2(0)
	, m_Sec3(0)
	, m_MarchNo1(1)
	, m_MarchNo2(1)
	, m_MarchNo3(1)

	, m_marchcount1(0)
	, m_marchcount2(0)
	, m_marchcount3(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKanAutoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HOUR1, m_Hour1);
	DDV_MinMaxInt(pDX, m_Hour1, 0, 200);
	DDX_Text(pDX, IDC_HOUR2, m_Hour2);
	DDV_MinMaxInt(pDX, m_Hour2, 0, 200);
	DDX_Text(pDX, IDC_HOUR3, m_Hour3);
	DDV_MinMaxInt(pDX, m_Hour3, 0, 200);
	DDX_Text(pDX, IDC_MIN1, m_Min1);
	DDV_MinMaxInt(pDX, m_Min1, 0, 59);
	DDX_Text(pDX, IDC_MIN2, m_Min2);
	DDV_MinMaxInt(pDX, m_Min2, 0, 59);
	DDX_Text(pDX, IDC_MIN3, m_Min3);
	DDV_MinMaxInt(pDX, m_Min3, 0, 59);
	DDX_Text(pDX, IDC_SEC1, m_Sec1);
	DDV_MinMaxInt(pDX, m_Sec1, 0, 59);
	DDX_Text(pDX, IDC_SEC2, m_Sec2);
	DDV_MinMaxInt(pDX, m_Sec2, 0, 59);
	DDX_Text(pDX, IDC_SEC3, m_Sec3);
	DDV_MinMaxInt(pDX, m_Sec3, 0, 59);
	DDX_Control(pDX, IDC_STOP1, m_Stop1);
	DDX_Control(pDX, IDC_STOP2, m_Stop2);
	DDX_Control(pDX, IDC_STOP3, m_Stop3);
	DDX_Control(pDX, IDC_Timer1, m_Start1);
	DDX_Control(pDX, IDC_Timer2, m_Start2);
	DDX_Control(pDX, IDC_Timer3, m_Start3);
	DDX_Text(pDX, IDC_MARCHNO1, m_MarchNo1);
	DDV_MinMaxInt(pDX, m_MarchNo1, 1, 40);
	DDX_Text(pDX, IDC_MARCHNO2, m_MarchNo2);
	DDV_MinMaxInt(pDX, m_MarchNo2, 1, 40);
	DDX_Text(pDX, IDC_MARCHNO3, m_MarchNo3);
	DDV_MinMaxInt(pDX, m_MarchNo3, 1, 40);
	//  DDX_Text(pDX, IDC_HANDLESTATE, m_HandleState);
	DDX_Control(pDX, IDC_HANDLE, m_GetHandle);
	//  DDX_Control(pDX, IDC_HANDLESTATE, m_HandleState);
	DDX_Text(pDX, IDC_MARCHCOUNT1, m_marchcount1);
	DDX_Text(pDX, IDC_MARCHCOUNT2, m_marchcount2);
	DDX_Text(pDX, IDC_MARCHCOUNT3, m_marchcount3);
	DDX_Control(pDX, IDC_SHITF, m_Shift);
	DDX_Control(pDX, IDC_ATKDLG, m_AtkDlg);
}

BEGIN_MESSAGE_MAP(CKanAutoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_HOUR1, &CKanAutoDlg::OnEnChangeHour1)
	ON_EN_CHANGE(IDC_MIN1, &CKanAutoDlg::OnEnChangeMin1)
	ON_BN_CLICKED(IDC_Timer1, &CKanAutoDlg::OnBnClickedTimer1)
	ON_BN_CLICKED(IDC_Timer2, &CKanAutoDlg::OnBnClickedTimer2)
	ON_BN_CLICKED(IDC_STOP1, &CKanAutoDlg::OnBnClickedStop1)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_Timer3, &CKanAutoDlg::OnBnClickedTimer3)
	ON_BN_CLICKED(IDC_STOP2, &CKanAutoDlg::OnBnClickedStop2)
	ON_BN_CLICKED(IDC_STOP3, &CKanAutoDlg::OnBnClickedStop3)
	ON_STN_CLICKED(IDC_HANDLESTATE, &CKanAutoDlg::OnStnClickedHandlestate)
	ON_BN_CLICKED(IDC_HANDLE, &CKanAutoDlg::OnBnClickedHandle)
	ON_EN_CHANGE(IDC_MARCHNO1, &CKanAutoDlg::OnEnChangeMarchno1)
	ON_EN_CHANGE(IDC_MARCHNO2, &CKanAutoDlg::OnEnChangeMarchno2)
	ON_EN_CHANGE(IDC_MARCHNO3, &CKanAutoDlg::OnEnChangeMarchno3)
	ON_EN_CHANGE(IDC_SEC1, &CKanAutoDlg::OnEnChangeSec1)
	ON_EN_CHANGE(IDC_HOUR2, &CKanAutoDlg::OnEnChangeHour2)
	ON_EN_CHANGE(IDC_MIN2, &CKanAutoDlg::OnEnChangeMin2)
	ON_EN_CHANGE(IDC_SEC2, &CKanAutoDlg::OnEnChangeSec2)
	ON_EN_CHANGE(IDC_HOUR3, &CKanAutoDlg::OnEnChangeHour3)
	ON_EN_CHANGE(IDC_MIN3, &CKanAutoDlg::OnEnChangeMin3)
	ON_EN_CHANGE(IDC_SEC3, &CKanAutoDlg::OnEnChangeSec3)
	ON_BN_CLICKED(IDC_SHITF, &CKanAutoDlg::OnBnClickedShitf)
	ON_BN_CLICKED(IDC_ATKDLG, &CKanAutoDlg::OnBnClickedAtkdlg)
END_MESSAGE_MAP()


// CKanAutoDlg ��Ϣ�������

BOOL CKanAutoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	//AllocConsole();// ����̨���
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	time_t t_clock1 = time(NULL);
	time_t t_clock2 = time(NULL);
	time_t t_clock3 = time(NULL);
	((CEdit*)GetDlgItem(IDC_STOP1))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_STOP2))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_STOP3))->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARCHNO1))->SetWindowTextW(_T("2"));
	((CEdit*)GetDlgItem(IDC_MARCHNO2))->SetWindowTextW(_T("5"));
	((CEdit*)GetDlgItem(IDC_MARCHNO3))->SetWindowTextW(_T("21"));


	if (getHWND()){
		GetDlgItem(IDC_HANDLESTATE)->SetWindowTextW(_T("�ѻ�þ��"));
		if(!p_fakeMin){
		p_fakeMin = true;
		AfxBeginThread(FakeMin, NULL);}
	}
	else
		GetDlgItem(IDC_HANDLESTATE)->SetWindowTextW(_T("δ��þ��"));
	
	isShift = isInDes();
	if (isShift){
		m_Shift.SetWindowTextW(_T("���봰��"));
	}
	else{
		m_Shift.SetWindowTextW(_T("�Ƴ�����"));
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKanAutoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKanAutoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CKanAutoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKanAutoDlg::OnEnChangeHour1()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeMin1()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnBnClickedTimer1()
{
	t_clock1 = time(NULL);
	UpdateData(TRUE);

	if (m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1 < MarchTime[m_MarchNo1 - 1] * 60)
	{
		t_clock1 += m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1;
		//_cprintf("1 start\n");
		SetTimer(1, 500, NULL);
		((CEdit*)GetDlgItem(IDC_HOUR1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP1))->EnableWindow(TRUE);
	}
	else
	{
		t_clock1 = time(NULL);
		int addtime = rand() % MARCH_RANDOM;
		t_clock1 += m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1 + addtime;
		m_marchcount1 = 0;

		march1Run = true;
		threadInfo.marchNo = m_MarchNo1;
		threadInfo.shipNo = 2;
		threadInfo.dlgHd = this;
		threadInfo.time = m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1 + addtime;
		threadInfo.supplyType = 1;
		pTMarch1 = AfxBeginThread(p_StartMarch, &threadInfo);
	//	_cprintf("2 start\n");
	
		UpdateData(FALSE);

		((CEdit*)GetDlgItem(IDC_HOUR1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer1))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP1))->EnableWindow(TRUE);
	
	}
}


void CKanAutoDlg::OnBnClickedTimer2()
{
	t_clock2 = time(NULL);
	UpdateData(TRUE);

	if (m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2 < MarchTime[m_MarchNo2 - 1] * 60)
	{
		t_clock2 += m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2;
		SetTimer(2, 500, NULL);
		((CEdit*)GetDlgItem(IDC_HOUR2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP2))->EnableWindow(TRUE);
	}
	else
	{
		t_clock2 = time(NULL);
		int addtime = rand() % MARCH_RANDOM;
		t_clock2 += m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2 + addtime;
		m_marchcount2 = 0;

		march2Run = true;
		threadInfo2.marchNo = m_MarchNo2;
		threadInfo2.shipNo = 3;
		threadInfo2.dlgHd = this;
		threadInfo2.time = m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2 + addtime;
		threadInfo2.supplyType = 1;

		pTMarch2 = AfxBeginThread(p_StartMarch, &threadInfo2);

		
		UpdateData(FALSE);
		//SetTimer(2, 500, NULL);
		((CEdit*)GetDlgItem(IDC_HOUR2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer2))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP2))->EnableWindow(TRUE);

	}
}

void CKanAutoDlg::OnBnClickedTimer3()
{
	t_clock3 = time(NULL);
	UpdateData(TRUE);
	int addtime = rand() % MARCH_RANDOM;

	if (m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3 < MarchTime[m_MarchNo3 - 1] * 60)
	{
		t_clock3 += m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3;
		SetTimer(3, 500, NULL);
		((CEdit*)GetDlgItem(IDC_HOUR3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP3))->EnableWindow(TRUE);
	}
	else
	{
		t_clock3 = time(NULL);
		int addtime = rand() % MARCH_RANDOM;
		t_clock3 += m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3 + addtime;
		m_marchcount3 = 0;

		march3Run = true;
		threadInfo3.marchNo = m_MarchNo3;
		threadInfo3.shipNo = 4;
		threadInfo3.dlgHd = this;
		threadInfo3.time = m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3 + addtime;
		threadInfo3.supplyType = 1;

		pTMarch3 = AfxBeginThread(p_StartMarch, &threadInfo3);

		
		UpdateData(FALSE);
		//SetTimer(3, 500, NULL);
		((CEdit*)GetDlgItem(IDC_HOUR3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MIN3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_SEC3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_MARCHNO3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_Timer3))->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_STOP3))->EnableWindow(TRUE);
	}
}


void CKanAutoDlg::OnBnClickedStop1()
{
	KillTimer(1);
	march1Run = false;
	((CEdit*)GetDlgItem(IDC_HOUR1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MIN1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_SEC1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARCHNO1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_Timer1))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_STOP1))->EnableWindow(FALSE);
}

void CKanAutoDlg::OnBnClickedStop2()
{
	KillTimer(2);
	march2Run = false;
	((CEdit*)GetDlgItem(IDC_HOUR2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MIN2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_SEC2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARCHNO2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_Timer2))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_STOP2))->EnableWindow(FALSE);
}

void CKanAutoDlg::OnBnClickedStop3()
{
	KillTimer(3);
	march3Run = false;
	((CEdit*)GetDlgItem(IDC_HOUR3))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MIN3))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_SEC3))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARCHNO3))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_Timer3))->EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_STOP3))->EnableWindow(FALSE);
}


void CKanAutoDlg::OnTimer(UINT_PTR nIDEvent)
{
	int t;
	time_t cur_t;
	switch (nIDEvent)
	{
	case 1:
	//	_cprintf("timer 1\n");
		cur_t = time(NULL);
		t = (int)t_clock1 - cur_t;
		if (t <= 0)
		{
			int addtime = rand() % MARCH_RANDOM;
			//int addtime = waitTime(MARCH_RANDOM, 0.5);
			//_cprintf("1 start\n");
			KillTimer(1);
			UpdateData(TRUE);
			int curMarchTime = MarchTime[m_MarchNo1 - 1];
			m_Hour1 = curMarchTime / 60;
			curMarchTime = curMarchTime % 60;
			m_Min1 = curMarchTime;
			m_Sec1 = 0;

			t_clock1 = time(NULL);
			t_clock1 += m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1 + addtime;
			threadInfo.time = m_Hour1 * 3600 + m_Min1 * 60 + m_Sec1 + addtime;
			m_marchcount1++;
			UpdateData(FALSE);
			//��Զ������Զ��
			
			threadInfo.shipNo = 2;
			AfxBeginThread(p_MarchReturn, &threadInfo);

			Sleep(1000);

			threadInfo.marchNo = m_MarchNo1;
			threadInfo.shipNo = 2;
			threadInfo.dlgHd = this;
			threadInfo.supplyType = 2;
			march1Run = true;
			pTMarch1 = AfxBeginThread(p_StartMarch, &threadInfo);
		}
		else{
			m_Hour1 = t / 3600;
			t = t % 3600;
			m_Min1 = t / 60;
			m_Sec1 = t % 60;
			UpdateData(FALSE);
		}
		
		break;
	case 2:
	//	_cprintf("timer 2\n");
		cur_t = time(NULL);
		t = (int)t_clock2 - cur_t;
		if (t <= 0)
		{
			int addtime = rand() % MARCH_RANDOM;
			//int addtime = waitTime(MARCH_RANDOM, 0.5);
			KillTimer(2);
			UpdateData(TRUE);
			int curMarchTime = MarchTime[m_MarchNo2 - 1];
			m_Hour2 = curMarchTime / 60;
			curMarchTime = curMarchTime % 60;
			m_Min2 = curMarchTime;
			m_Sec2 = 0;

			t_clock2 = time(NULL);
			t_clock2 += m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2 + addtime;
			threadInfo2.time = m_Hour2 * 3600 + m_Min2 * 60 + m_Sec2 + addtime;
			m_marchcount2++;
			UpdateData(FALSE);
			//��Զ������Զ��
			threadInfo2.shipNo = 3;
			AfxBeginThread(p_MarchReturn, &threadInfo2);

			Sleep(1000);

			threadInfo2.marchNo = m_MarchNo2;
			threadInfo2.shipNo = 3;
			threadInfo2.dlgHd = this;
			threadInfo2.supplyType = 2;
			march2Run = true;
			pTMarch2 = AfxBeginThread(p_StartMarch, &threadInfo2);
		}
		else{
			m_Hour2 = t / 3600;
			t = t % 3600;
			m_Min2 = t / 60;
			m_Sec2 = t % 60;
			UpdateData(FALSE);
		}
		
		break;
	case 3:
	//	_cprintf("timer 3\n");
		cur_t = time(NULL);
		t = (int)t_clock3 - cur_t;
		if (t <= 0)
		{
			int addtime = rand() % MARCH_RANDOM;
			//int addtime = waitTime(MARCH_RANDOM, 0.5);
			KillTimer(3);
			UpdateData(TRUE);
			int curMarchTime = MarchTime[m_MarchNo3 - 1];
			m_Hour3 = curMarchTime / 60;
			curMarchTime = curMarchTime % 60;
			m_Min3 = curMarchTime;
			m_Sec3 = 0;

			t_clock3 = time(NULL);
			t_clock3 += m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3 + addtime;
			threadInfo3.time = m_Hour3 * 3600 + m_Min3 * 60 + m_Sec3 + addtime;
			m_marchcount3++;
			UpdateData(FALSE);
			//��Զ������Զ��
			threadInfo3.shipNo = 4;
			AfxBeginThread(p_MarchReturn, &threadInfo3);

			Sleep(1000);

			threadInfo3.marchNo = m_MarchNo3;
			threadInfo3.shipNo = 4;
			threadInfo3.dlgHd = this;
			march3Run = true;
			threadInfo3.supplyType = 2;
			pTMarch3 = AfxBeginThread(p_StartMarch, &threadInfo3);
		}
		else{
			m_Hour3 = t / 3600;
			t = t % 3600;
			m_Min3 = t / 60;
			m_Sec3 = t % 60;
			UpdateData(FALSE);
		}
		
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CKanAutoDlg::OnOK()
{
	//CDialogEx::OnOK();
	return;
}


void CKanAutoDlg::OnCancel()
{
	//CDialogEx::OnCancel();
	return;
}


void CKanAutoDlg::OnClose()
{
	//CDialogEx::OnClose();
	p_fakeMin = false;
	march1Run = false;
	march2Run = false;
	march3Run = false;
	EndDialog(IDCANCEL);
	CDialog::OnClose();
}



void CKanAutoDlg::OnStnClickedHandlestate()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnBnClickedHandle()
{
	if (getHWND()){
		/*if (!p_fakeMin){
			p_fakeMin = true;
			AfxBeginThread(FakeMin, NULL);
		}*/
		GetDlgItem(IDC_HANDLESTATE)->SetWindowTextW(_T("�ѻ�þ��"));
	}
	else
		GetDlgItem(IDC_HANDLESTATE)->SetWindowTextW(_T("δ��þ��"));
}


void CKanAutoDlg::OnEnChangeMarchno1()
{

	UpdateData(TRUE);
	int curMarchTime;
	if (m_MarchNo1 < 1 || m_MarchNo1 > 40)
		curMarchTime = 0; 
	else
		curMarchTime = MarchTime[m_MarchNo1-1];
	m_Hour1 = curMarchTime / 60;
	curMarchTime = curMarchTime % 60;
	m_Min1 = curMarchTime;
	m_Sec1 = 0;
	UpdateData(FALSE);
}


void CKanAutoDlg::OnEnChangeMarchno2()
{
	UpdateData(TRUE);
	int curMarchTime;
	if (m_MarchNo2 < 1 || m_MarchNo2 > 40)
		curMarchTime = 0;
	else
		curMarchTime = MarchTime[m_MarchNo2 - 1];
	m_Hour2 = curMarchTime / 60;
	curMarchTime = curMarchTime % 60;
	m_Min2 = curMarchTime;
	m_Sec2 = 0;
	UpdateData(FALSE);
}


void CKanAutoDlg::OnEnChangeMarchno3()
{
	UpdateData(TRUE);
	int curMarchTime;
	if (m_MarchNo1 < 1 || m_MarchNo1 > 40)
		curMarchTime = 0;
	else
		curMarchTime = MarchTime[m_MarchNo3 - 1];
	m_Hour3 = curMarchTime / 60;
	curMarchTime = curMarchTime % 60;
	m_Min3 = curMarchTime;
	m_Sec3 = 0;
	UpdateData(FALSE);
}


void CKanAutoDlg::OnEnChangeSec1()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeHour2()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeMin2()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeSec2()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeHour3()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeMin3()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnEnChangeSec3()
{
	UpdateData();
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CKanAutoDlg::OnBnClickedShitf()
{
	if (isShift){
		m_Shift.SetWindowTextW(_T("�Ƴ�����"));
		isShift = false;
		shiftIn();
	}
	else{
		m_Shift.SetWindowTextW(_T("���봰��"));
		isShift = true;
		shiftOut();
	}
}



void CKanAutoDlg::OnBnClickedAtkdlg()
{

	if (NULL == kanAtk)
	{
		// ������ģ̬�Ի���ʵ��   
		kanAtk = new KanAtk();
		kanAtk->Create(IDD_ATKDIALOG, this);
	}

	kanAtk->ShowWindow(SW_SHOW);	
}

