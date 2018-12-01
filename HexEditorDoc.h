// HexEditorDoc.h : interface of the CHexEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXEDITORDOC_H__F8480F2A_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_HEXEDITORDOC_H__F8480F2A_B2D1_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DLGProgress.h"
class CHexEditorView;

class CHexEditorDoc : public CDocument
{
protected: // create from serialization only
	CHexEditorDoc();
	DECLARE_DYNCREATE(CHexEditorDoc)

// Attributes
public:
	CString m_szDataBuffer;
	unsigned int m_nBufferLength; // maintained by us because getlength stops at null char
	CDLGProgress dlgProgress; // progress bar

// Operations
public:
	void Reset();

	long GetData( CString szData );
	CString SetData( long nData, BOOL fHex );

	void InsertBytes();
	void EditData( int nStart, int nEnd, BOOL fHex=TRUE );
	void EditString( int nStart, int nEnd );
	void DeleteData( int nStart, int nEnd );
	CHexEditorView* GetView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHexEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHexEditorDoc)
	afx_msg void OnEditInsert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDITORDOC_H__F8480F2A_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
