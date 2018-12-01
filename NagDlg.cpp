// NagDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HexEditor.h"
#include "NagDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NagDlg dialog


NagDlg::NagDlg(CWnd* pParent, char *Title, char *Static, unsigned char *Check)
	: CDialog(NagDlg::IDD, pParent)
{
	TitlePtr = Title;
	StaticPtr = Static;
	CheckPtr = Check;
	//{{AFX_DATA_INIT(NagDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void NagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NagDlg)
	DDX_Control(pDX, IDC_STATICBOX, m_Static);
	DDX_Control(pDX, IDC_CHECK1, m_Check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NagDlg, CDialog)
	//{{AFX_MSG_MAP(NagDlg)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NagDlg message handlers

void NagDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (CheckPtr)
		*CheckPtr = ((m_Check.GetCheck()) & 0x0001);
	CDialog::OnOK();
}

int NagDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return 0;
}

BOOL NagDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(TitlePtr);
	m_Static.SetWindowText(StaticPtr);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
