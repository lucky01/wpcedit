/*
Module : SPLASHER.CPP
Purpose: A splash screen component for MFC which uses a DIB bitmap
         instead of a resource. Palette management code is also included
         so that the bitmap will display using its own optimized palette.
         It also used as a UI thread so that UI of the splash screen 
         remains responsive.
Created: PJN / 15-11-1996
History: PJN / 11-12-1997 1) Incoporation of n_ew DIB code provided by the authors own
                          CDibImage class. A static library version is used by 
                          splasher here. If you want to use CDIbImage for anything
                          other than CSplashThread, then you need to download
                          CDibImage on its own.
                          2) Can now load from resource or bitmap
                          3) General tidy up of the code.
         PJN / 22-3-1998  1) Palette is now correctly initialised on startup
                          2) Code now protects itself if m_SplashScreen cannot be created
         PJN / 22-12-1998 1) Now no longer dependent on CDibImage.
                          2) Unicode Enabled the code,
                          3) General tidy up of the code
                          4) Removed the unnecessary variable m_bCreated
                          5) Fixed a potential race condition in CSplashThread::HideSplash()
         PJN / 01-03-2000 1) Fixed a problem with bitmaps which do not have a palette
                          2) Fixed a problem in Win 98 and Win2000 when the splash screen is
                          closed but the main window of your app fails to activate. The code 
                          now uses AttachThreadInput to synchronise the UI activities of the
                          main GUI thread and the splash screen thread.
         PJN / 01-01-2001 1) Now includes copyright message in the source code and documentation.
                          2) Modified the way the sample app waits for the thread to exit. It
                          now synchronises with the exit of the splash screen thread
                          3) Now allows the icon of the splash screen to be specified
                          4) Now allows the splash screen window to be customized at run time
                          through a virtual function "CSplashThread::CreateSplash". Thanks to 
                          Yury Goltsman for suggesting these enhancements.
         PJN / 27-08-2001 1) Splash screen now by default includes the window style WS_EX_TOPMOST
         PJN / 31-08-2001 1) Fixed an assert which was occuring when you brought up the splash window
                          and closed it really quickly. Thanks to Wanner Robert for spotting this problem.
                          2) Removed a busy loop in HideSplash and used a Win32 event for synchronisation
                          instead.
                          3) Implemented a class factory design pattern to further simplify the use
                          of the splash screen class. All client code now needs to do is derive a class 
                          from CSplashWnd (making sure it's declared DYNCREATE) and at a minimum just
                          call some of it's methods in the constructor to determine what it will display
                          at runtime. Then just use CSplashFactory::Create with the name of your derived
                          class. When you want to close the splash screen just call 
                          CSplashFactory::Create. What could be simpler!!!.
         PJN / 03-10-2002 1) Now allows you to specify a transparent color to draw the splash screen with.
                          This allows you to realize shapes other than the standard rectangle. Thanks to 
                          Gero Gerber for this update. Please note that this support is only available on
                          Windows 2000 or later.
                          2) Made the destructor of CSplashWnd virtual
         PJN / 11-10-2002 1) Fixed up some coding issues reported by BoundsChecker in CSplashWnd::OnPaint.
                          2) Now supports a drop shadow effect on the splash screen (assuming that the 
                          client OS is Windows XP or later).
         PJN / 28-08-2003 1) Removed a number of level 4 warnings.
         PJN / 06-09-2003 1) Fixed a problem where you get a crash in the close method if the window to gain 
                          focus was NULL. Thanks to Darius Thabit for reporting this problem.

                          

Copyright (c) 1996 - 2003 by PJ Naughter.  (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////////// Includes //////////////////////////

#include "stdafx.h"
#include "Splasher.h"



//////////////////// Defines ///////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//Define the various constants we need to call SetLayeredWindowAttributes. 
//Doing this means that the code does not required the latest Platform
//SDK to be installed
#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED           0x00080000
#endif
#ifndef LWA_COLORKEY
#define LWA_COLORKEY            0x00000001
#endif

//Define for drop shadow support. Doing this means that the code does
//not require the latest Platform SDK to be installed
#ifndef CS_DROPSHADOW
#define CS_DROPSHADOW       0x00020000
#endif


//////////////////// Implementation ////////////////////

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
  //{{AFX_MSG_MAP(CSplashWnd)
  ON_WM_CREATE()
  ON_WM_PAINT()
  ON_WM_LBUTTONDOWN()
  ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CSplashWnd, CWnd);

CSplashWnd::CSplashWnd()
{
  m_bOKToClose = FALSE;
  m_nHeight = 0;
  m_nWidth = 0;
  m_bUseFile = FALSE;
  m_pszResourceName = NULL;
  m_hIcon = NULL;
  m_bTransparent = FALSE;
  m_clrTransparent = RGB(255, 0, 255);
//  m_bDraggable = TRUE;
// Windows 98 crashes when dragging the spalsh screen and then it goes away.
//
  m_bDraggable = FALSE;
  m_bDropShadow = FALSE;

  //Determine if the OS supports layered windows
  HINSTANCE hUser32 = GetModuleHandle(_T("USER32.DLL"));
  if (hUser32)
    m_lpfnSetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes) GetProcAddress(hUser32, "SetLayeredWindowAttributes");
  else 
    m_lpfnSetLayeredWindowAttributes = NULL;
}

CSplashWnd::~CSplashWnd()
{
}

BOOL CSplashWnd::LoadBitmap()
{     
  //Use LoadImage to get the image loaded into a DIBSection
  HBITMAP hBitmap;
  if (m_bUseFile)
    hBitmap = (HBITMAP) ::LoadImage(NULL, m_sFilename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
  else
    hBitmap = (HBITMAP) ::LoadImage(AfxGetResourceHandle(), m_pszResourceName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

  //Check that we could load it up  
  if (hBitmap == NULL)       
  {
    ASSERT(FALSE); //Did you forget to derive your class from CSplashWnd and setup its member variables correctly\n"));
    return FALSE;
  }

  //Get the width and height of the DIBSection
  BITMAP bm;
  GetObject(hBitmap, sizeof(BITMAP), &bm);
  m_nHeight = bm.bmHeight;
  m_nWidth = bm.bmWidth;

  //Covert from the SDK bitmap handle to the MFC equivalent
  m_Bitmap.Attach(hBitmap);

  return TRUE;   
}

BOOL CSplashWnd::SetTransparent(COLORREF clrTransparent)
{
  BOOL bSuccess = FALSE;

  if (m_lpfnSetLayeredWindowAttributes)
  {
    m_bTransparent = TRUE;
    m_clrTransparent = clrTransparent;
    bSuccess = TRUE;
  }

  return bSuccess;
}

void CSplashWnd::SetDraggable(BOOL bDraggable)
{
  m_bDraggable = bDraggable;
}

void CSplashWnd::SetDropShadow(BOOL bDropShadow)
{
  m_bDropShadow = bDropShadow;
}

void CSplashWnd::CreatePaletteFromBitmap()
{
  //Get the color depth of the DIBSection
  BITMAP bm;
  m_Bitmap.GetObject(sizeof(BITMAP), &bm);

  //If the DIBSection is 256 color or less, it has a color table
  if ((bm.bmBitsPixel * bm.bmPlanes) <= 8)     
  {
    //Create a memory DC and select the DIBSection into it
    CDC memDC;
    memDC.CreateCompatibleDC(NULL);
    CBitmap* pOldBitmap = memDC.SelectObject(&m_Bitmap);

    //Get the DIBSection's color table
    RGBQUAD rgb[256];
    ::GetDIBColorTable(memDC.m_hDC, 0, 256, rgb);

    //Create a palette from the color table
    LPLOGPALETTE pLogPal = (LPLOGPALETTE) new BYTE[sizeof(LOGPALETTE) + (256*sizeof(PALETTEENTRY))];
    pLogPal->palVersion = 0x300;       
    pLogPal->palNumEntries = 256;

    for (WORD i=0; i<256; i++)       
    {
      pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
      pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
      pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
      pLogPal->palPalEntry[i].peFlags = 0;
    }
    VERIFY(m_Palette.CreatePalette(pLogPal));
//    ASSERT(m_Palette.CreatePalette(pLogPal));
    
    //Clean up
    delete pLogPal;
    memDC.SelectObject(pOldBitmap);
  }
  else  //It has no color table, so use a halftone palette     
  {
    CDC* pRefDC = GetDC();
    m_Palette.CreateHalftonePalette(pRefDC);
    ReleaseDC(pRefDC);     
  }     
}

BOOL CSplashWnd::Create()
{                   
  //Load up the bitmap from file or from resource
  VERIFY(LoadBitmap());
//	Valid = TRUE;
//	if (!(LoadBitmap()))
//	{
//		Valid = FALSE;
//		return FALSE;
//	}
  //Modify the owner window of the splash screen to be an invisible WS_POPUP 
  //window so that the splash screen does not appear in the task bar
  LPCTSTR pszWndClassOwner = AfxRegisterWndClass(0, 0, 0, m_hIcon);
  VERIFY(m_wndOwner.CreateEx(0, pszWndClassOwner, _T(""), WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, 0));
//  ASSERT(m_wndOwner.CreateEx(0, pszWndClassOwner, _T(""), WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, 0));

  //Create the appropiate window class to use for the splash window
  LPCTSTR pszWndClass = NULL;
  if (m_bDropShadow)
  {
    try
    {
      pszWndClass = AfxRegisterWndClass(CS_DROPSHADOW, AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0, m_hIcon);
    }
    catch(CResourceException* pEx)
    {
      //Avoid the memory leak
      pEx->Delete();

      //Probably because CS_DROPSHADOW is not supported on this OS, try again without it
      pszWndClass = AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0, m_hIcon);
    }
  }
  else
    pszWndClass = AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW), 0, m_hIcon);

  //Create this window
  VERIFY(CreateEx(WS_EX_TOPMOST, pszWndClass, _T(""), WS_POPUP | WS_VISIBLE, 0, 0, m_nWidth, m_nHeight, m_wndOwner.GetSafeHwnd(), NULL));
//  ASSERT(CreateEx(WS_EX_TOPMOST, pszWndClass, _T(""), WS_POPUP | WS_VISIBLE, 0, 0, m_nWidth, m_nHeight, m_wndOwner.GetSafeHwnd(), NULL));

  //Make the window transparent if required to
  if (m_bTransparent && m_lpfnSetLayeredWindowAttributes)
  {
    ASSERT(m_lpfnSetLayeredWindowAttributes);

    //Add the transparent style
    LONG nStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
    SetWindowLong(m_hWnd, GWL_EXSTYLE, nStyle | WS_EX_LAYERED);

    //Make the Window transparent used the specifed color
    m_lpfnSetLayeredWindowAttributes(m_hWnd, m_clrTransparent, 0, LWA_COLORKEY);
  }

  //Create the palette, We need to do this after the window is created because
  //we may need to access the DC associated with it
  CreatePaletteFromBitmap();

  //realize the bitmap's palette into the DC
  OnQueryNewPalette();

  return TRUE;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  //Let the parent class do its thing
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  //Center the splash window on the screen
  CenterWindow();

  return 0;
}

void CSplashWnd::OnPaint()
{
  CPaintDC dc(this);
  
  //select the palette and bitmap into the DC
  CDC memDC;
  memDC.CreateCompatibleDC(&dc);
  CBitmap* pOldBitmap = memDC.SelectObject(&m_Bitmap);
  CPalette* pOldPalette = NULL;
  if (m_Palette.m_hObject)
    pOldPalette = dc.SelectPalette(&m_Palette, FALSE);
  dc.RealizePalette();
  dc.BitBlt(0, 0, m_nWidth, m_nHeight, &memDC, 0, 0, SRCCOPY);
  memDC.SelectObject(pOldBitmap);         
  if (pOldPalette)
    dc.SelectPalette(pOldPalette, FALSE);
}

void CSplashWnd::OnLButtonDown(UINT /*nFlags*/, CPoint /*point*/) 
{
  if (m_bDraggable)
  {
    //Fake a Window drag
    SendMessage(WM_LBUTTONUP);
    SendMessage(WM_SYSCOMMAND, 0xF012);
  }
}

void CSplashWnd::OnClose() 
{
  if (m_bOKToClose) 
  {
    //Close this window
    CWnd::OnClose();

    //destroy our invisible owner when we're done
    m_wndOwner.PostMessage(WM_CLOSE);
  }
}

BOOL CSplashWnd::SelRelPal(BOOL bForceBkgnd)
{
  // We are going active, so realize our palette.
  CDC* pDC = GetDC();

  CPalette* pOldPal = pDC->SelectPalette(&m_Palette, bForceBkgnd);
  UINT u = pDC->RealizePalette();
  pDC->SelectPalette(pOldPal, TRUE);
  pDC->RealizePalette();

  ReleaseDC(pDC);

  // If any colors have changed or we are in the
  // background, repaint the lot.
  if (u || bForceBkgnd) 
    InvalidateRect(NULL, TRUE); // Repaint.
  
  return (BOOL) u; // TRUE if some colors changed.
}

void CSplashWnd::OnPaletteChanged(CWnd* pFocusWnd)
{
  // See if the change was caused by us and ignore it if not.
  if (pFocusWnd != this) 
    SelRelPal(TRUE); // Realize in the background. 
}

BOOL CSplashWnd::OnQueryNewPalette()
{
  return SelRelPal(FALSE); // Realize in the foreground.
}

void CSplashWnd::SetBitmapToUse(const CString& sFilename)
{
  m_bUseFile = TRUE;
  m_sFilename = sFilename;
}

void CSplashWnd::SetBitmapToUse(UINT nResourceID)
{
  m_bUseFile = FALSE;
  m_pszResourceName = MAKEINTRESOURCE(nResourceID);
}

void CSplashWnd::SetBitmapToUse(LPCTSTR pszResourceName)
{
  m_bUseFile = FALSE;
  m_pszResourceName = pszResourceName;
}

void CSplashWnd::SetIcon(HICON hIcon)
{
  //Destroy the icon if we have one already loaded
  if (m_hIcon)
    DestroyIcon(m_hIcon);
     
  m_hIcon = hIcon; 
}



BEGIN_MESSAGE_MAP(CSplashThread, CWinThread)
	//{{AFX_MSG_MAP(CSplashThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CSplashThread, CWinThread)

CSplashThread::CSplashThread()
{
  m_pRuntimeClassSplashWnd = NULL;
  m_pSplashScreen = NULL;
  m_bInitOK = FALSE;
}

CSplashThread::~CSplashThread()
{
  delete m_pSplashScreen;
}

BOOL CSplashThread::InitInstance()
{
  //Validate our parameters
  ASSERT(m_pRuntimeClassSplashWnd);

  //Create the Splash Screen window object
  m_pSplashScreen = (CSplashWnd*) m_pRuntimeClassSplashWnd->CreateObject();
  if (m_pSplashScreen == NULL)
  {
//    TRACE(_T("Failed to instantiate CSplashWnd object\n"));
    m_SplashCreated.SetEvent();
    return FALSE;
  }
  
  //Validate that it is derived from SSplashWnd
  ASSERT(m_pSplashScreen->IsKindOf(RUNTIME_CLASS(CSplashWnd)));

  //Create the HWND of it
  if (!m_pSplashScreen->Create())
  {
//    TRACE(_T("Failed to creat CSplashWnd object\n"));

    //Tidy up the heap memory we have allocated
    delete m_pSplashScreen;

    m_SplashCreated.SetEvent();
    return FALSE;
  }
  m_pMainWnd = m_pSplashScreen;

  //Signal the event which indicates that the splash window has been created
  m_bInitOK = TRUE;
  m_SplashCreated.SetEvent();

	return TRUE;
}



CSplashFactory::CSplashFactory()
{
  m_pSplashThread = NULL;
}

CSplashFactory::~CSplashFactory()
{
  //Just incase client code forgot to call Close, we do it anyway
  Close();
}

BOOL CSplashFactory::Create(CRuntimeClass* pRuntimeClassSplashWnd)
{
  //Validate our parameters
  ASSERT(m_pSplashThread == NULL);
  ASSERT(pRuntimeClassSplashWnd);

  //Create the GUI worker thread
  m_pSplashThread = (CSplashThread*) AfxBeginThread(RUNTIME_CLASS(CSplashThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
  if (m_pSplashThread == NULL)
  {
//    TRACE(_T("Failed to create splash screen thread\n"));
    return FALSE;
  }

  ASSERT(m_pSplashThread->IsKindOf(RUNTIME_CLASS(CSplashThread)));
  m_pSplashThread->m_pRuntimeClassSplashWnd = pRuntimeClassSplashWnd;
  m_pSplashThread->m_bAutoDelete = FALSE; //We are in charge of the deletion of the thread
  m_pSplashThread->ResumeThread();        //Resume the thread now that we have set it up 

  return TRUE;
}

BOOL CSplashFactory::Close(CWnd* pWndToGainFocus)
{
  //Assume the worst
  BOOL bSuccess = FALSE;

  if (m_pSplashThread)
  {
    //Wait until the InitInstance has completed in worker thread
    WaitForSingleObject(m_pSplashThread->m_SplashCreated, INFINITE);

    //Attach this threads UI state to the worker threadss one, This will ensure that 
    //the activation state is managed consistenly across the two threads
    ASSERT(AfxGetApp());
    AttachThreadInput(AfxGetApp()->m_nThreadID, m_pSplashThread->m_nThreadID, TRUE);

    //Set the focus back to the correct window
    CWnd* pWndFocus = pWndToGainFocus;
    if (pWndFocus == NULL)
      pWndFocus = AfxGetMainWnd();

    if (pWndFocus)
    {
      pWndFocus->SetFocus();
      pWndFocus->SetForegroundWindow();
    }

    //If the worker thread has a splash screen then ask it to close
    //before trying to close it
    if (m_pSplashThread->m_pSplashScreen)
    {
      m_pSplashThread->m_pSplashScreen->SetOKToClose();
      m_pSplashThread->m_pSplashScreen->PostMessage(WM_CLOSE);
    }

    //Wait for it to exit and tidy up its memory
    WaitForSingleObject(m_pSplashThread->m_hThread, INFINITE);
    delete m_pSplashThread;
    m_pSplashThread = NULL;

    bSuccess = TRUE;
  }

  return bSuccess;
}

