// DLGProgress.cpp : implementation file
//

#include "stdafx.h"
#include "HexEditor.h"
#include "DLGProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLGProgress dialog


CDLGProgress::CDLGProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDLGProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDLGProgress::SetProgress( int nProgress, CString szCurTask )
{
	m_wndProgressBar.SetPos( nProgress );
	m_wndTask.SetWindowText( szCurTask );
}

void CDLGProgress::SetSubProgress( int nProgress )
{
	if( nProgress == -1 )
		m_wndMiniProgressBar.EnableWindow( FALSE );
	else
	{
		m_wndMiniProgressBar.EnableWindow( TRUE );
		m_wndMiniProgressBar.SetPos( nProgress );
	}
}

void CDLGProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGProgress)
	DDX_Control(pDX, IDC_ABORT, m_wndAbort);
	DDX_Control(pDX, IDC_MINIPROGRESSBAR, m_wndMiniProgressBar);
	DDX_Control(pDX, IDC_TASK, m_wndTask);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_wndProgressBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGProgress, CDialog)
	//{{AFX_MSG_MAP(CDLGProgress)
	ON_BN_CLICKED(IDC_ABORT, OnAbort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGProgress message handlers

BOOL CDLGProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// set ranges etc
	m_wndProgressBar.SetRange( 0, 100 );
	m_wndMiniProgressBar.SetRange( 0, 100 );
	m_wndMiniProgressBar.EnableWindow( FALSE );
	m_wndTask.SetWindowText( "" );
	m_fAborted = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDLGProgress::OnAbort() 
{
	m_fAborted = TRUE;	
}
