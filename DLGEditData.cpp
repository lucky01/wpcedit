/////////////////////////////////////////////////////////////////////////////
// DLGEditData.cpp : implementation file
// -------------------------------------
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
#include "DLGEditData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGEditData dialog


CDLGEditData::CDLGEditData(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGEditData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGEditData)
	m_szInput = _T("");
	//}}AFX_DATA_INIT
	m_nMaxLength = 0;
}


void CDLGEditData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGEditData)
	DDX_Control(pDX, IDC_INPUT, m_wndInput);
	DDX_Text(pDX, IDC_INPUT, m_szInput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGEditData, CDialog)
	//{{AFX_MSG_MAP(CDLGEditData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGEditData message handlers

BOOL CDLGEditData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_wndInput.SetLimitText( m_nMaxLength );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
