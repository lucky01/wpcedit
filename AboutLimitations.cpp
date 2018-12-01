// AboutLimitations.cpp : implementation file
//

#include "stdafx.h"
#include "HexEditor.h"
#include "AboutLimitations.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AboutLimitations dialog


AboutLimitations::AboutLimitations(CWnd* pParent /*=NULL*/)
	: CDialog(AboutLimitations::IDD, pParent)
{
	//{{AFX_DATA_INIT(AboutLimitations)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AboutLimitations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AboutLimitations)
	DDX_Control(pDX, IDC_STATIC_MYINFO, m_MyInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AboutLimitations, CDialog)
	//{{AFX_MSG_MAP(AboutLimitations)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AboutLimitations message handlers

int AboutLimitations::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

BOOL AboutLimitations::OnInitDialog() 
{
	CString InfoString;

	CDialog::OnInitDialog();
	
	InfoString.Format("This software created by %s",APPLICATION_AUTHOR);
	m_MyInfo.SetWindowText(InfoString);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
