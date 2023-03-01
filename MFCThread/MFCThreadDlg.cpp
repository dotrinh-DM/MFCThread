
// MFCThreadDlg.cpp : implementation file

#include "pch.h"
#include "framework.h"
#include "MFCThread.h"
#include "MFCThreadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CMFCThreadDlg::CMFCThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NUMBER, myTxt);
}

BEGIN_MESSAGE_MAP(CMFCThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCThreadDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CMFCThreadDlg message handlers
//void CMFCThreadDlg::abcd()
//{
//	TRACE("\n bbbbbbbbbbbbbbbbbbbbb: \n");
//}

BOOL CMFCThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetTimer(200, 500, NULL);
	thread = AfxBeginThread(LeftToRight_Thread, this);
	//myTxt.SetWindowText(_T("ssss0%"));
	AfxMessageBox(_T("testttt"), MB_ICONWARNING);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CMFCThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT LeftToRight_Thread(LPVOID pParam)
{
	CMFCThreadDlg* ptr = (CMFCThreadDlg*)pParam;
	while (ptr->number < 100)
	{
		Sleep(100);
		TRACE("\n aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: %d \n", ptr->number);
		ptr->number++;
	}
	return 0;
}

//ham huy cua class
CMFCThreadDlg::~CMFCThreadDlg()
{
	stopMyThread();
}

void CMFCThreadDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 200) {
		CString abc;
		abc.Format(_T("%d"), number);
		myTxt.SetWindowText(abc);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCThreadDlg::stopMyThread()
{
	number = 101;
	if (thread != NULL) {
		::WaitForSingleObject(thread->m_hThread, 0xFFFFFF);
		thread = NULL;
	}
}

void CMFCThreadDlg::OnBnClickedButtonStart()
{
	stopMyThread();
}
