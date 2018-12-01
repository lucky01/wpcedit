#if !defined(AFX_ABOUTLIMITATIONS_H__C7E16B87_CE8F_43AC_A7CD_4642FEB25580__INCLUDED_)
#define AFX_ABOUTLIMITATIONS_H__C7E16B87_CE8F_43AC_A7CD_4642FEB25580__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AboutLimitations.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AboutLimitations dialog

class AboutLimitations : public CDialog
{
// Construction
public:
	AboutLimitations(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AboutLimitations)
	enum { IDD = IDD_ABOUT_LIMITATIONS };
	CStatic	m_MyInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AboutLimitations)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AboutLimitations)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTLIMITATIONS_H__C7E16B87_CE8F_43AC_A7CD_4642FEB25580__INCLUDED_)
