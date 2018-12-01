#if !defined(AFX_NAGDLG_H__50C604F8_99EA_4395_A8B0_6F620D449CC8__INCLUDED_)
#define AFX_NAGDLG_H__50C604F8_99EA_4395_A8B0_6F620D449CC8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NagDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NagDlg dialog

class NagDlg : public CDialog
{
// Construction
public:
	NagDlg(CWnd* pParent = NULL,
		   char *Title = NULL,
		   char *Static = NULL, 
		   unsigned char *Check = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NagDlg)
	enum { IDD = IDD_NAGDLG };
	CStatic	m_Static;
	CButton	m_Check;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NagDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char *TitlePtr;
	char *StaticPtr;
	unsigned char *CheckPtr;
	// Generated message map functions
	//{{AFX_MSG(NagDlg)
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAGDLG_H__50C604F8_99EA_4395_A8B0_6F620D449CC8__INCLUDED_)
