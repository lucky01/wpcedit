#if !defined(AFX_DLGEDITDATA_H__1C5FEC41_B5DC_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_DLGEDITDATA_H__1C5FEC41_B5DC_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGEditData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDLGEditData dialog

class CDLGEditData : public CDialog
{
// Construction
public:
	CDLGEditData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDLGEditData)
	enum { IDD = IDD_EDITDATA };
	CEdit	m_wndInput;
	CString	m_szInput;
	//}}AFX_DATA

	int m_nMaxLength; // max length input can be

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGEditData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDLGEditData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEDITDATA_H__1C5FEC41_B5DC_11D7_9734_00045A4C0065__INCLUDED_)
