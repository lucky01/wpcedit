// Nag.cpp : implementation file
//

#include "stdafx.h"
#include "HexEditor.h"
#include "Nag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Nag dialog


Nag::Nag(CWnd* pParent)
	: CDialog(Nag::IDD, pParent)
{
	TheText = &NagText[0];
	//{{AFX_DATA_INIT(Nag)
	//}}AFX_DATA_INIT
}

void Nag::SetTextPtr(char *Ptr)
{
	TheText = Ptr;
}

void Nag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Nag)
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDC_EDIT_NAGTEXT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Nag, CDialog)
	//{{AFX_MSG_MAP(Nag)
	ON_WM_SHOWWINDOW()
	ON_EN_VSCROLL(IDC_EDIT_NAGTEXT, OnVscrollEditNagtext)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Nag message handlers

void Nag::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	GotoDlgCtrl (GetDlgItem(IDCANCEL));
	// TODO: Add your message handler code here
	
}

BOOL Nag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_Text.SetWindowText(NagText);	
	m_Text.SetWindowText(TheText);	
	m_Ok.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void Nag::OnVscrollEditNagtext() 
{
	// TODO: Add your control notification handler code here
	if (m_Text.GetScrollPos(SB_VERT) >= m_Text.GetScrollLimit(SB_VERT))
		m_Ok.EnableWindow(TRUE);
}

void Nag::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void Nag::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Text.GetScrollPos(SB_VERT) >= m_Text.GetScrollLimit(SB_VERT))
		m_Ok.EnableWindow(TRUE);
	
	CDialog::OnMouseMove(nFlags, point);
}

BOOL Nag::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Text.GetScrollPos(SB_VERT) >= m_Text.GetScrollLimit(SB_VERT))
		m_Ok.EnableWindow(TRUE);
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void Nag::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Text.GetScrollPos(SB_VERT) >= m_Text.GetScrollLimit(SB_VERT))
		m_Ok.EnableWindow(TRUE);
	
	CDialog::OnLButtonUp(nFlags, point);
}
