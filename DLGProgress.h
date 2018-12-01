#if !defined(AFX_DLGPROGRESS_H__CC5161A1_B6AA_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_DLGPROGRESS_H__CC5161A1_B6AA_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGProgress dialog

class CDLGProgress : public CDialog
{
// Construction
public:
	CDLGProgress(CWnd* pParent = NULL);   // standard constructor

// Operations
	void SetProgress( int nProgress, CString szCurTask );
	void SetSubProgress( int nProgress=-1 );

// Dialog Data
	//{{AFX_DATA(CDLGProgress)
	enum { IDD = IDD_PROGRESS };
	CButton	m_wndAbort;
	CProgressCtrl	m_wndMiniProgressBar;
	CStatic	m_wndTask;
	CProgressCtrl	m_wndProgressBar;
	//}}AFX_DATA
	BOOL m_fAborted;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGProgress)
	virtual BOOL OnInitDialog();
	afx_msg void OnAbort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROGRESS_H__CC5161A1_B6AA_11D7_9734_00045A4C0065__INCLUDED_)
