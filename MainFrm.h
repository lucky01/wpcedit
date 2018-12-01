// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F8480F28_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_MAINFRM_H__F8480F28_B2D1_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	void OnUpdateClock(CCmdUI *pCmdUI);
	int TimerIDIcon;
	int IconIndex;
	void LoadNewIcon(UINT nIconID);

// Attributes
protected:
public:
	virtual void GetMessageString(UINT nID, CString& rMessage) const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SetupWindowStartup();

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CStatusBar  m_wndStatusBar;
	CString m_strTimeFormat;
	WINDOWPLACEMENT wp;
	BOOL LoadWindowPlacement(LPWINDOWPLACEMENT pwp);
	void SetDefaultWindowPlacement(LPWINDOWPLACEMENT pwp);
	void SaveWindowPlacement(LPWINDOWPLACEMENT pwp);

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewFormat();
	afx_msg LRESULT OnAreYouMe(WPARAM, LPARAM);
	afx_msg void OnUpdateViewDmdgraphics(CCmdUI* pCmdUI);
	afx_msg void OnViewDmdgraphics();
	afx_msg void OnUpdateViewFontdata(CCmdUI* pCmdUI);
	afx_msg void OnViewFontdata();
	afx_msg void OnUpdateViewAnimationdata(CCmdUI* pCmdUI);
	afx_msg void OnViewAnimationdata();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLimitations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F8480F28_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
