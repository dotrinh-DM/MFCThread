
// MFCThreadDlg.h : header file
//

#pragma once
UINT LeftToRight_Thread(LPVOID pParam);

// CMFCThreadDlg dialog
class CMFCThreadDlg : public CDialogEx
{
// Construction
public:
	CMFCThreadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTHREAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void stopMyThread();
	
	int number;
	CStatic myTxt;

	CWinThread* thread;
	~CMFCThreadDlg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
};
