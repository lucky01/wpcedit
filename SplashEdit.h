#if !defined(AFX_SPLASHEDIT_H__4ACACE3C_1A55_4F91_BCDF_67FCC1A06611__INCLUDED_)
#define AFX_SPLASHEDIT_H__4ACACE3C_1A55_4F91_BCDF_67FCC1A06611__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SplashEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SplashEdit dialog

class SplashEdit : public CDialog
{
// Construction
public:
	SplashEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SplashEdit)
	enum { IDD = IDD_SPLASH_EDIT };
	CStatic	m_StaticSplashFile;
	CSpinButtonCtrl	m_SpinSplashTime;
	CEdit	m_EditSplashTime;
	CEdit	m_EditSplashFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SplashEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char TempBuffer[64];
	UINT ExtractSplashTime();
	void verifyControls();
	UINT OriginalSplashTime;
	CString OriginalSplashFile;
	void updateControls();
	void OnChangeEdit();
	// Generated message map functions
	//{{AFX_MSG(SplashEdit)
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHEDIT_H__4ACACE3C_1A55_4F91_BCDF_67FCC1A06611__INCLUDED_)
