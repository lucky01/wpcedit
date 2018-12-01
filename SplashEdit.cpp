// SplashEdit.cpp : implementation file
//

#include "stdafx.h"
//#include "RadarLog.h"
#include "SplashEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SplashEdit dialog


SplashEdit::SplashEdit(CWnd* pParent /*=NULL*/)
	: CDialog(SplashEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(SplashEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SplashEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SplashEdit)
	DDX_Control(pDX, IDC_STATIC_SPLASHFILE, m_StaticSplashFile);
	DDX_Control(pDX, IDC_SPIN_SPLASHTIME, m_SpinSplashTime);
	DDX_Control(pDX, IDC_EDIT_SPLASHTIME, m_EditSplashTime);
	DDX_Control(pDX, IDC_EDIT_SPLASHFILE, m_EditSplashFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SplashEdit, CDialog)
	//{{AFX_MSG_MAP(SplashEdit)
	ON_WM_LBUTTONDOWN()
	ON_EN_KILLFOCUS(IDC_EDIT_SPLASHTIME, verifyControls)
	ON_EN_KILLFOCUS(IDC_EDIT_SPLASHFILE, verifyControls)
	ON_EN_CHANGE(IDC_EDIT_SPLASHFILE, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_SPLASHTIME, OnChangeEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SplashEdit message handlers

void SplashEdit::OnOK() 
{
	// TODO: Add extra validation here
	verifyControls();

	//
	// Check the splash file name for any bad characters...
	//
	if (!(((CRadarLogApp *)AfxGetApp())->TestAndCheckFolderName(&m_EditSplashFile, "Splash File")))
		return;


	UINT NewSplashTime = ExtractSplashTime();
	CString NewSplashFile;
	m_EditSplashFile.GetWindowText(NewSplashFile);
	if ((NewSplashTime != OriginalSplashTime) ||
		(NewSplashFile != OriginalSplashFile))
	{
		AfxGetApp()->WriteProfileString(REGISTRY_SPLASH_SCREEN, "SplashFileName", NewSplashFile);
		AfxGetApp()->WriteProfileInt(REGISTRY_SPLASH_SCREEN, "SplashMinTimeMilliseconds", NewSplashTime);
	}
	
	CDialog::OnOK();
}

void SplashEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	verifyControls();
	
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL SplashEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SpinSplashTime.SetRange(0, MAXIMUM_SPLASH_MILLISECONDS);
	m_EditSplashTime.LimitText(5);
	m_EditSplashFile.LimitText(64); // A single file name shouln't get too large

	OriginalSplashTime = AfxGetApp()->GetProfileInt(REGISTRY_SPLASH_SCREEN, "SplashMinTimeMilliseconds", 2000);
	OriginalSplashFile = AfxGetApp()->GetProfileString(REGISTRY_SPLASH_SCREEN, "SplashFileName", "Logo.BMP");
	itoa(OriginalSplashTime, TempBuffer, 10);
	m_EditSplashTime.SetWindowText(TempBuffer);

	m_EditSplashFile.SetWindowText(OriginalSplashFile);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


UINT SplashEdit::ExtractSplashTime()
{
	CString TempString;
	m_EditSplashTime.GetWindowText(TempBuffer, 5);
	return (atoi(TempBuffer));
}

void SplashEdit::verifyControls()
{
	
	if (!(IsWindowVisible()))
		return;

	UINT SplashTime, NewSplashTime;
	
	//
	// Validate the value of number-of-signs
	//
	SplashTime = NewSplashTime = ExtractSplashTime();
	if (SplashTime > MAXIMUM_SPLASH_MILLISECONDS)
		SplashTime = MAXIMUM_SPLASH_MILLISECONDS;
	itoa(SplashTime, TempBuffer, 10);
	if (SplashTime != NewSplashTime)
		m_EditSplashTime.SetWindowText(TempBuffer);
}


void SplashEdit::updateControls()
{
	UINT SplashTime = ExtractSplashTime();	
	BOOL Enable;

	//
	// Enable/Disable the splash file if time is zero.  This is just to visually remind
	// them that a value of zero for splash-time means there is no splash screen at all.
	//
	Enable = TRUE;
	if (!SplashTime)
		Enable = FALSE;
	m_EditSplashFile.EnableWindow(Enable);		
	m_StaticSplashFile.EnableWindow(Enable);
}

void SplashEdit::OnChangeEdit() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	if (IsWindowVisible())
		updateControls();	
}

