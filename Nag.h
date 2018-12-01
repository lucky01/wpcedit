#if !defined(AFX_NAG_H__AF53DD11_681C_4668_BA0C_BE705E2D50BD__INCLUDED_)
#define AFX_NAG_H__AF53DD11_681C_4668_BA0C_BE705E2D50BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Nag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Nag dialog

class Nag : public CDialog
{
// Construction
public:
	Nag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Nag)
	enum { IDD = IDD_NAG };
	CButton	m_Ok;
	CEdit	m_Text;
	//}}AFX_DATA
	void SetTextPtr(char *Ptr);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Nag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char *TheText;
	// Generated message map functions
	//{{AFX_MSG(Nag)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	afx_msg void OnVscrollEditNagtext();
	virtual void OnOK();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAG_H__AF53DD11_681C_4668_BA0C_BE705E2D50BD__INCLUDED_)
