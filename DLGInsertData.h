#if !defined(AFX_DLGINSERTDATA_H__5292B963_B397_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_DLGINSERTDATA_H__5292B963_B397_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGInsertData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGInsertData dialog

class CDLGInsertData : public CDialog
{
// Construction
public:
	CDLGInsertData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGInsertData)
	enum { IDD = IDD_INSERTDATA };
	CString	m_szData;
	CString	m_szInsertAmt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGInsertData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGInsertData)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINSERTDATA_H__5292B963_B397_11D7_9734_00045A4C0065__INCLUDED_)
