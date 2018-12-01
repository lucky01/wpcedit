/////////////////////////////////////////////////////////////////////////////
// HexEditor.cpp : Defines the class behaviors for the application.
// ----------------------------------------------------------------
// This code was written by Paul "Crazy" Frazee, and can be
// used royalty-free in any program. However, if the code is to be
// redistributed (in a modified state or not), I would appreciate
// an acknowledgement that the code was originally mine, or based
// off of mine. Please enjoy!
// 
// You can reach me at paulfrazee@cox.net, or CrazyFrazee911 (aim).
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define STORE_HERE
#include "HexEditor.h"

#include "MainFrm.h"
#include "HexEditorDoc.h"
#include "HexEditorView.h"
#include "dmd.h"
#include "splasher.h"
#include "Nag.h"
//#include "WinVer.h"  // used for getting version information from struct to About box
//#include "Windows.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CHexEditorApp

BEGIN_MESSAGE_MAP(CHexEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CHexEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditorApp construction

CHexEditorApp::CHexEditorApp()
{
	delete pDocTemplate;
	ProgramInitialized = FALSE;
}



// <Splash>
class CMySplashWnd : public CSplashWnd
{
public:
//Constructors / Destructors
  CMySplashWnd();

  DECLARE_DYNCREATE(CMySplashWnd);
};

IMPLEMENT_DYNCREATE(CMySplashWnd, CSplashWnd);

CMySplashWnd::CMySplashWnd()
{
  //Use the following 2 lines of code if you would like a transparent splash screen
   SetBitmapToUse(IDB_TRANSPARENT_SPLASH);

	SetTransparent();
}

// </Splash>


/////////////////////////////////////////////////////////////////////////////
// The one and only CHexEditorApp object

CHexEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHexEditorApp initialization

BOOL CHexEditorApp::InitInstance()
{
    // Start of one-instance code
	// Check if program is already running
    bool AlreadyRunning;
    HANDLE hMutexOneInstance = ::CreateMutex( NULL, FALSE,
		_T("WPCEDIT-F27C57BF-AF6A-4ffe-A445-994C232741FE"));

    // what changes for the alternative solutions
    // is the UID in the above call
    // which will be replaced by a call on
    // createExclusionName

    AlreadyRunning = ( ::GetLastError() == ERROR_ALREADY_EXISTS || 
                       ::GetLastError() == ERROR_ACCESS_DENIED);
    // The call fails with ERROR_ACCESS_DENIED if the Mutex was 
    // created in a different users session because of passing
    // NULL for the SECURITY_ATTRIBUTES on Mutex creation);

    if ( AlreadyRunning )
	{ // kill this 
		HWND hOther = NULL;
        EnumWindows(searcher, (LPARAM)&hOther);

        if ( hOther != NULL )
	    { // pop up 
             ::SetForegroundWindow( hOther );

             if ( IsIconic( hOther ) )
             { // restore 
                 ::ShowWindow( hOther, SW_RESTORE );
             } // restore 
        } // pop up 

        return FALSE; // terminates the creation
    } // kill this 
    // ... continue with InitInstance
	// End of one-instance code


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("WPCEdit"));


	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	LoadProgramSettings(&ProgramSettings);

	if (!(ProgramSettings.NagMessageShown))
	{
		Nag NagDialog;
		switch (NagDialog.DoModal())
		{
			case IDOK :
				ProgramSettings.NagMessageShown = TRUE;
				SaveProgramSettingsToRegistry(&ProgramSettings);
				break;
			case IDCANCEL :
			default:
				m_pMainWnd = NULL;
				return FALSE;
		}
	}
	//
	// BEGIN Splash screen addition
	// Important to do this AFTER the INI loading because we get some settings
	// regarding the splash screen from the INI file, also need to load up the
	// current run-time path from the GetModuleInfo() call above...
	//
	CSplashFactory factory;
	if (factory.Create(RUNTIME_CLASS(CMySplashWnd)))
	{
		Sleep(750);
	}
	// END splash screen code addition

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHexEditorDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHexEditorView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
	{
		return FALSE;
	}

	SaveProgramSettingsToRegistry(&ProgramSettings);


	//FOLLOWING LINE IS THE ADDITION OF SPLASH SCREEN COMPONENT (if you forget to 
	//call close, it will be done for you automatically when "factory" goes out
	//of scope!!. 
	factory.Close();

	// The one and only window has been initialized, so show and update it.
	((CMainFrame *)m_pMainWnd)->SetupWindowStartup();

    // The DMD Dialog may modify the settings and registry when OK is clicked
	DMDDialogPtr = new DMD(NULL, &ProgramSettings, DMD_DIALOG_TYPE_GRAPHICS);
	DMDDialogPtr->Create();

    // The DMD Dialog may modify the settings and registry when OK is clicked
	FONTDialogPtr = new DMD(NULL, &ProgramSettings, DMD_DIALOG_TYPE_FONTDATA);
	FONTDialogPtr->Create();

    // The DMD Dialog may modify the settings and registry when OK is clicked
	ANIDialogPtr = new DMD(NULL, &ProgramSettings, DMD_DIALOG_TYPE_ANIDATA);
	ANIDialogPtr->Create();

	ProgramInitialized = TRUE;
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_VER;
	CStatic	m_CR;
	CStatic	m_AboutIcon;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	UINT IconAboutTimer;
	int IconIndex;
// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	IconIndex = STARTING_ICON_INDEX_ABOUT_BOX_ANIMATION;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_VER, m_VER);
	DDX_Control(pDX, IDC_STATIC_CR, m_CR);
	DDX_Control(pDX, IDC_STATIC_ABOUTICON, m_AboutIcon);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHexEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorApp message handlers


int CHexEditorApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete DMDDialogPtr;	
	return CWinApp::ExitInstance();
}

// One-instance code
BOOL CALLBACK CHexEditorApp::searcher(HWND hWnd, LPARAM lParam)
{
	DWORD result;

    LRESULT ok = ::SendMessageTimeout(hWnd,
                                      UWM_ARE_YOU_ME,
                                      0, 0, 
                                      SMTO_BLOCK |
//                                      SMTO_ABORT_IF_HUNG,
                                      SMTO_ABORTIFHUNG,
                                      200,
                                      &result);
    if(ok == 0)
	{
		return TRUE; // ignore this and continue
	}
    if(result == UWM_ARE_YOU_ME)
    { /* found it */
		HWND * target = (HWND *)lParam;
        *target = hWnd;
        return FALSE; // stop search
    } /* found it */
	return TRUE; // continue search
} // CMyApp::searcher

LRESULT CMainFrame::OnAreYouMe(WPARAM, LPARAM)
{
	return UWM_ARE_YOU_ME;
} // CMainFrame::OnAreYouMe
// One-instance code


int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	
	// TODO: Add your specialized creation code here
	IconAboutTimer = SetTimer(TIMER_ABOUT_ICON, TIMER_ABOUTICON_INITIAL, NULL);
	return 0;
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (IconAboutTimer)
	{
		KillTimer(IconAboutTimer);	
	}
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == TIMER_ABOUT_ICON)
	{

		CRect rect;
		int NewTimer;
		m_AboutIcon.GetWindowRect(rect);

		HICON hIconNew = AfxGetApp()->LoadIcon((UINT)icons[IconIndex++]);

		m_AboutIcon.SetIcon(hIconNew);
		m_AboutIcon.InvalidateRect(NULL, TRUE);

		if (IconIndex >= (sizeof(icons) / sizeof(icons[0])))  
			IconIndex = 0;
		switch (IconIndex)
		{
			case 1: // We just drew the initial image..
				NewTimer = TIMER_ABOUTICON_INITIAL;
				break;
			case 0: // We just finished the text animation...
				NewTimer = TIMER_ABOUTICON_AXED;
				break;
			default : // otherwise we're in animation mode wait .1 seconds				 
				NewTimer = TIMER_ABOUTICON_ANIMATING;
		}
		if (IconAboutTimer)
		{
			KillTimer(IconAboutTimer);	
			IconAboutTimer = SetTimer(TIMER_ABOUT_ICON, NewTimer, NULL);
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CHexEditorApp::LoadFactoryDefaultProgramSettings(RegistrySettings *Ptr)
{
	Ptr->PixelColor = DEFAULT_PIXEL_COLOR;
	Ptr->XoredCheckboxState = DEFAULT_XORCHECKBOXSTATE;
	Ptr->SkippedCheckboxState = DEFAULT_SKIPCHECKBOXSTATE;
	Ptr->NagMessageShown = FALSE;
	Ptr->DMDNagMessageShown = FALSE;
	int i;
	for (i = 0; i < MAX_NAGS; i++)
	{
		Ptr->MiscNagsShown[i] = FALSE;
	}
}


void CHexEditorApp::LoadProgramSettings(RegistrySettings *Ptr)
{
	LoadFactoryDefaultProgramSettings(Ptr);
	Ptr->PixelColor = GetProfileInt(REGISTRY_DMDEDIT_SETTINGS,"PixelColor",Ptr->PixelColor);
	Ptr->XoredCheckboxState = GetProfileInt(REGISTRY_DMDEDIT_SETTINGS, "XorCheckbox",Ptr->XoredCheckboxState);
	Ptr->SkippedCheckboxState = GetProfileInt(REGISTRY_DMDEDIT_SETTINGS, "SkipCheckbox",Ptr->SkippedCheckboxState);
	Ptr->DMDNagMessageShown = GetProfileInt(REGISTRY_DMDEDIT_SETTINGS, "DMDNagScreenShown", Ptr->DMDNagMessageShown);
	Ptr->NagMessageShown = GetProfileInt(REGISTRY_NAG_SCREENS,"DisclaimerShown",Ptr->NagMessageShown);
	int i;
	for (i = 0; i < MAX_NAGS; i++)
	{
		Ptr->MiscNagsShown[i] = GetProfileInt(REGISTRY_NAG_SCREENS,NagRegistryKeyText[i],Ptr->MiscNagsShown[i]);
	}
	ValidateProgramSettings(Ptr);
}	

void CHexEditorApp::SaveProgramSettingsToRegistry(RegistrySettings *Ptr)
{
	ValidateProgramSettings(Ptr);
	WriteProfileInt(REGISTRY_DMDEDIT_SETTINGS, "PixelColor", Ptr->PixelColor);
	WriteProfileInt(REGISTRY_DMDEDIT_SETTINGS, "XorCheckbox", Ptr->XoredCheckboxState);
	WriteProfileInt(REGISTRY_DMDEDIT_SETTINGS, "SkipCheckbox", Ptr->SkippedCheckboxState);
	WriteProfileInt(REGISTRY_DMDEDIT_SETTINGS, "DMDNagScreenShown", Ptr->DMDNagMessageShown);
	WriteProfileInt(REGISTRY_NAG_SCREENS, "DisclaimerShown", Ptr->NagMessageShown);
	int i;
	for (i = 0; i < MAX_NAGS; i++)
	{
		WriteProfileInt(REGISTRY_NAG_SCREENS,NagRegistryKeyText[i],Ptr->MiscNagsShown[i]);
	}
}

void CHexEditorApp::ValidateProgramSettings(RegistrySettings *Ptr)
{
	if (Ptr->PixelColor >= PIXEL_COLORS)
	{
		Ptr->PixelColor = DEFAULT_PIXEL_COLOR;
	}
	if (Ptr->XoredCheckboxState > 1)  // enforce our 1-or-0 values
	{
		Ptr->XoredCheckboxState = 1;
	}
	if (Ptr->SkippedCheckboxState > 1)
	{
		Ptr->SkippedCheckboxState = 1;
	}
}


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString InfoText;
	InfoText.Format("%s Version %.1f",APPLICATION_TITLE,APPLICATION_VERSION);
	m_VER.SetWindowText(InfoText);
	m_CR.SetWindowText(APPLICATION_COPYRIGHT);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
