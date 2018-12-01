/////////////////////////////////////////////////////////////////////////////
// DLGInsertData.cpp : implementation file
// ---------------------------------------
// This code was written by Paul "Crazy" Frazee, and can be
// used royalty-free in any program. However, if the code is to be
// redistributed (in a modified state or not), I would appreciate
// an acknowledgement that the code was originally mine, or based
// off of mine. Please enjoy!
// 
// You can reach me at paulfrazee@cox.net, or CrazyFrazee911 (aim).
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HexEditor.h"
#include "DLGInsertData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGInsertData dialog


CDLGInsertData::CDLGInsertData(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGInsertData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGInsertData)
	m_szData = _T("");
	m_szInsertAmt = _T("");
	//}}AFX_DATA_INIT
}


void CDLGInsertData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGInsertData)
	DDX_Text(pDX, IDC_DATA, m_szData);
	DDX_Text(pDX, IDC_INSERTAMT, m_szInsertAmt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGInsertData, CDialog)
	//{{AFX_MSG_MAP(CDLGInsertData)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGInsertData message handlers
