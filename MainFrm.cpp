/////////////////////////////////////////////////////////////////////////////
// HMainFrm.cpp : implementation of the CMainFrame class
// -----------------------------------------------------
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

#include "MainFrm.h"

#include "DMD.h"
#include "hexeditordoc.h"
#include "hexeditorview.h"
#include "aboutlimitations.h"
#include "nag.h"
#include "version.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_FORMAT, OnViewFormat)
	ON_REGISTERED_MESSAGE(UWM_ARE_YOU_ME, OnAreYouMe)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DMDGRAPHICS, OnUpdateViewDmdgraphics)
	ON_COMMAND(ID_VIEW_DMDGRAPHICS, OnViewDmdgraphics)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FONTDATA, OnUpdateViewFontdata)
	ON_COMMAND(ID_VIEW_FONTDATA, OnViewFontdata)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANIMATIONDATA, OnUpdateViewAnimationdata)
	ON_COMMAND(ID_VIEW_ANIMATIONDATA, OnViewAnimationdata)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_COMMAND(IDD_LIMITATIONS, OnLimitations)
	//}}AFX_MSG_MAP
//	ON_UPDATE_COMMAND_UI(ID_INDICATOR_CLOCK, OnUpdateClock)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
//	ID_INDICATOR_CARET,
//	ID_INDICATOR_CLOCK,
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	IconIndex = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// Load up window placement from registry
//	WINDOWPLACEMENT wp;
	if (!(LoadWindowPlacement (&wp)))
	{
		SetDefaultWindowPlacement(&wp);
	}
	SetWindowPlacement(&wp);

#if MFC_VER < 0x06000
//	if (!m_wndToolBar.Create(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
//		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
//		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
#else
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
#endif
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) || 
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	TimerIDIcon = SetTimer(TIMER_WINDOW_ICONS, TIMER_WINDOW_ICONS_UPDATE, NULL);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

/*
void CMainFrame::OnUpdateClock(CCmdUI *pCmdUI)
{
	TCHAR buf[256];
	LCID Lcid = GetUserDefaultLCID();
//	if (m_wndStatusBar.m_bPaneOn)
		VERIFY(GetTimeFormat(Lcid, 0, NULL, m_strTimeFormat, buf, 256));
//	else
//		VERIFY(GetDateFormat(Lcid, 0, NULL, m_strDateFormat, buf, 256));
	UINT nID, nStyle;
	int nWidth, nIndex = m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK);
	CClientDC dc(&m_wndStatusBar);
	CFont* pOldFont = dc.SelectObject(m_wndStatusBar.GetFont());
	CSize szExtent = dc.GetTextExtent(buf, strlen(buf));
	dc.SelectObject(pOldFont);

	m_wndStatusBar.GetPaneInfo(nIndex, nID, nStyle, nWidth);
	m_wndStatusBar.SetPaneInfo(nIndex, nID, nStyle, szExtent.cx);
	m_wndStatusBar.SetPaneText(nIndex, buf);

	pCmdUI->Enable();
}
*/

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
	{
		return FALSE;
	}
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	// The following flag-clear removes the open-active filename from the title bar
//	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewFormat() 
{
//	CDLGFormatView fvDlg;
//	fvDlg.DoModal();
}

void CMainFrame::OnUpdateViewDmdgraphics(CCmdUI* pCmdUI) 
{
	if ((((CHexEditorApp *)(AfxGetApp()))->ProgramInitialized) == FALSE)
	{
		return;
	}

	pCmdUI->Enable(((((CHexEditorView *)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView())->GetDocument())->m_nBufferLength));
	pCmdUI->SetCheck(((CHexEditorApp *)(AfxGetApp()))->DMDDialogPtr->IsWindowVisible());
}

void CMainFrame::OnViewDmdgraphics() 
{
	if (!(((CHexEditorApp *)AfxGetApp())->ProgramSettings.DMDNagMessageShown))
	{
		Nag NagDialog;
		NagDialog.SetTextPtr(DMDNagText);
		switch (NagDialog.DoModal())
		{
			case IDOK :
				((CHexEditorApp *)AfxGetApp())->ProgramSettings.DMDNagMessageShown = TRUE;
				((CHexEditorApp *)AfxGetApp())->SaveProgramSettingsToRegistry(&((CHexEditorApp *)AfxGetApp())->ProgramSettings);
				break;
			case IDCANCEL :
			default:
				return;
		}
	}

	DMD *D;
	unsigned char Visible;
	D = ((CHexEditorApp *)(AfxGetApp()))->DMDDialogPtr;
	Visible = D->IsWindowVisible();
	if (!Visible)
	{
		if (D->Init() == 0)
		{
			D->ShowWindow(1);
		}
	}
	else
	{
		D->ShowWindow(0);
	}
}

void CMainFrame::OnUpdateViewFontdata(CCmdUI* pCmdUI) 
{
	if ((((CHexEditorApp *)(AfxGetApp()))->ProgramInitialized) == FALSE)
	{
		return;
	}

	pCmdUI->Enable(((((CHexEditorView *)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView())->GetDocument())->m_nBufferLength));
	pCmdUI->SetCheck(((CHexEditorApp *)(AfxGetApp()))->FONTDialogPtr->IsWindowVisible());
}

void CMainFrame::OnViewFontdata() 
{
	DMD *F;
	unsigned char Visible;
	F = ((CHexEditorApp *)(AfxGetApp()))->FONTDialogPtr;
	Visible = F->IsWindowVisible();
	if (!Visible)
	{
		if (F->Init() == 0)
		{
			F->ShowWindow(1);
		}
	}
	else
	{
		F->ShowWindow(0);
	}
}

void CMainFrame::OnUpdateViewAnimationdata(CCmdUI* pCmdUI) 
{
	if ((((CHexEditorApp *)(AfxGetApp()))->ProgramInitialized) == FALSE)
	{
		return;
	}

	pCmdUI->Enable(((((CHexEditorView *)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView())->GetDocument())->m_nBufferLength));
	pCmdUI->SetCheck(((CHexEditorApp *)(AfxGetApp()))->ANIDialogPtr->IsWindowVisible());
}

void CMainFrame::OnViewAnimationdata() 
{
	DMD *A;
	unsigned char Visible;
	A = ((CHexEditorApp *)(AfxGetApp()))->ANIDialogPtr;
	Visible = A->IsWindowVisible();
	if (!Visible)
	{
		if (A->Init() == 0)
		{
			A->ShowWindow(1);
		}
	}
	else
	{
		A->ShowWindow(0);
	}
}

BOOL CMainFrame::LoadWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	CString strBuffer = AfxGetApp()->GetProfileString ("WindowPosition", "WindowPos");
	if (strBuffer.IsEmpty())
	{
		return FALSE;
	}
	
	int cReat = _stscanf (strBuffer, "%i:%i:%i:%i:%i:%i:%i:%i:%i:%i",
		&pwp->flags, &pwp->showCmd,
		&pwp->ptMinPosition.x, &pwp->ptMinPosition.y,
		&pwp->ptMaxPosition.x, &pwp->ptMaxPosition.y,
		&pwp->rcNormalPosition.left, &pwp->rcNormalPosition.top,
		&pwp->rcNormalPosition.right, &pwp->rcNormalPosition.bottom);

	if (cReat != 10)
	{
		return FALSE;
	}
	return TRUE;
}

void CMainFrame::SetupWindowStartup()
{
	CRect WorkAreaRect;
	CRect NormalWindow = wp.rcNormalPosition;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, WorkAreaRect, NULL);

	if (   (!(WorkAreaRect.PtInRect(NormalWindow.TopLeft())))
		&& (!(WorkAreaRect.PtInRect(NormalWindow.BottomRight())))
       )
		SetDefaultWindowPlacement(&wp);
	SetWindowPos(NULL, wp.rcNormalPosition.left,
		               wp.rcNormalPosition.top,
					   (wp.rcNormalPosition.right - wp.rcNormalPosition.left),
					   (wp.rcNormalPosition.bottom - wp.rcNormalPosition.top),
					   0
					   );
	ShowWindow(wp.showCmd);
	UpdateWindow();
}

void CMainFrame::SaveWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	CString strBuffer;
	strBuffer.Format ("%i:%i:%i:%i:%i:%i:%i:%i:%i:%i",
		pwp->flags, pwp->showCmd,
		pwp->ptMinPosition.x, pwp->ptMinPosition.y,
		pwp->ptMaxPosition.x, pwp->ptMaxPosition.y,
		pwp->rcNormalPosition.left, pwp->rcNormalPosition.top,
		pwp->rcNormalPosition.right, pwp->rcNormalPosition.bottom);
	AfxGetApp ()->WriteProfileString ("WindowPosition", "WindowPos", strBuffer);
}

void CMainFrame::SetDefaultWindowPlacement(LPWINDOWPLACEMENT pwp)
{
	pwp->length = sizeof(pwp);
	pwp->flags = WPF_SETMINPOSITION;
	pwp->showCmd = SW_SHOWNORMAL;
	pwp->ptMinPosition.x = -1;
	pwp->ptMinPosition.y = -1;
	pwp->ptMaxPosition.x = -1;
	pwp->ptMaxPosition.y = -1;
	pwp->rcNormalPosition.left = 151;
	pwp->rcNormalPosition.top = 66;
	pwp->rcNormalPosition.right = 728;
	pwp->rcNormalPosition.bottom = 417;
}


void CMainFrame::OnClose() 
{
	if (GetWindowPlacement (&wp))
	{
		if (IsZoomed ())
		{
			wp.flags |= WPF_RESTORETOMAXIMIZED;
		}
		SaveWindowPlacement (&wp);
	}
	SaveBarState("ControlBars\\State");
	
	CFrameWnd::OnClose();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	DMD *D;
	DMD *F;
	DMD *A;
	unsigned char DMDVisible;
	D = ((CHexEditorApp *)(AfxGetApp()))->DMDDialogPtr;
	F = ((CHexEditorApp *)(AfxGetApp()))->FONTDialogPtr;
	A = ((CHexEditorApp *)(AfxGetApp()))->ANIDialogPtr;
	DMDVisible = D->IsWindowVisible() | F->IsWindowVisible() | A->IsWindowVisible();

	if (nIDEvent == TIMER_WINDOW_ICONS)
	{
		int NewTimer;

		if ((IconIndex != 0) || ((IconIndex == 0) && (IsIconic() || DMDVisible)))
		{
			LoadNewIcon (icons[IconIndex++]);
			if (IconIndex >= (sizeof(icons) / sizeof(icons[0])))  
			{
				IconIndex = 0;
			}
		}

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
		if (TimerIDIcon)
		{
			KillTimer(TimerIDIcon);	
			TimerIDIcon = SetTimer(TIMER_WINDOW_ICONS, NewTimer, NULL);
		}
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::LoadNewIcon(UINT nIconID)
{
	HICON hIconNew = AfxGetApp()->LoadIcon(nIconID);
	SetIcon(hIconNew, FALSE);
}

void CMainFrame::OnLimitations() 
{
	// TODO: Add your command handler code here
	AboutLimitations Limitations;
	Limitations.DoModal();
}

void CMainFrame::GetMessageString( UINT nID, CString& rMessage ) const
{
//	if(nID==AFX_IDS_IDLEMESSAGE)
//	{
//		rMessage.Format("%s %.1f %s",APPLICATION_TITLE,APPLICATION_VERSION,APPLICATION_COPYRIGHT);
//	}
	CFrameWnd::GetMessageString( nID, rMessage );
}

















