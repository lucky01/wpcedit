// HexEditorView.h : interface of the CHexEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXEDITORVIEW_H__F8480F2C_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_HEXEDITORVIEW_H__F8480F2C_B2D1_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern UINT uMSG_MOUSEWHEEL;

class CHexEditorView : public CScrollView
{
protected: // create from serialization only
	CHexEditorView();
	DECLARE_DYNCREATE(CHexEditorView)

// Attributes
public:
	CHexEditorDoc* GetDocument();
	unsigned int m_nCurSel, m_nCurSelEnd;
	unsigned int m_nLineLength;
	unsigned int m_nLineCount;
	unsigned int m_nVisStart, m_nVisEnd;
	CFont m_cFont;
	CPoint m_ptMouse;
	BOOL m_fDraggingMouse;

// Operations
public:
	void Reset();
	void UpdateScrollbars();
	void MakeCursorVisible();
	void GetSel( unsigned int& nStart, unsigned int& nEnd );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHexEditorView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LONG OnWheel( UINT nFlags, LONG pValue );
	DECLARE_MESSAGE_MAP()
};

//#ifndef _DEBUG  // debug version in HexEditorView.cpp
//inline CHexEditorDoc* CHexEditorView::GetDocument()
//CHexEditorDoc* CHexEditorView::GetDocument()
//   { return (CHexEditorDoc*)m_pDocument; }
//#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDITORVIEW_H__F8480F2C_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
