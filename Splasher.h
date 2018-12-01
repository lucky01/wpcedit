/*
Module : SPLASHER.H
Purpose: A splash screen component for MFC which uses a DIB bitmap
         instead of a resource. Palette management code is also included
         so that the bitmap will display using its own optimized palette
Created: PJN / 15-11-1996

Copyright (c) 1996 - 2003 by PJ Naughter.  

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __SPLASHER_H__
#define __SPLASHER_H__


///////////////// Includes /////////////////////////

#ifndef __AFXMT_H__
//#pragma message("To avoid this message, please put afxmt.h in your Precompiled Header (normally stdafx.h)")
#include <afxmt.h>
#endif



///////////////// Classes //////////////////////////

class CSplashWnd : public CWnd
{
public:
//Constructors / Destructors
  CSplashWnd();
//	BOOL Valid;
  virtual ~CSplashWnd();

protected:
  typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)(HWND, COLORREF, BYTE, DWORD);

  DECLARE_DYNCREATE(CSplashWnd);

//Virtual methods
  virtual BOOL Create();
  virtual BOOL LoadBitmap();

//Misc methods
  void SetBitmapToUse(const CString& sFilename);
  BOOL SetTransparent(COLORREF clrTransparent = RGB(255, 0, 255));
  void SetDropShadow(BOOL bDropShadow = TRUE);
  void SetBitmapToUse(UINT nResourceID);
  void SetBitmapToUse(LPCTSTR pszResourceName); 
  void SetOKToClose() { m_bOKToClose = TRUE; };  
  void SetIcon(HICON hIcon);
  BOOL SelRelPal(BOOL bForceBkgnd);
  void CreatePaletteFromBitmap();
  void SetDraggable(BOOL bDragable);
  BOOL TransparencyAvailable() const { return m_lpfnSetLayeredWindowAttributes != NULL; };

  //{{AFX_VIRTUAL(CSplashWnd)
  //}}AFX_VIRTUAL

  //{{AFX_MSG(CSplashWnd)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
  afx_msg BOOL OnQueryNewPalette();
  afx_msg void OnClose();
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP()
  
//Member variables
  BOOL                           m_bOKToClose;                     //Ok to respond to WM_CLOSE messages
  CBitmap                        m_Bitmap;                         //The Bitmap we are displaying
  CPalette                       m_Palette;                        //The palette associated with the bitmap
  int                            m_nHeight;                        //The height in pixels of the bitmap
  int                            m_nWidth;                         //The width in pixels of the bitmap
  CWnd                           m_wndOwner;                       //Our hidden window parent (causes this window not to have a entry in the task bar)            
  BOOL                           m_bUseFile;                       //Should we use m_sFilename when it comes time to call LoadBitmap 
  LPCTSTR                        m_pszResourceName;                //The resource ID if m_bUseFile is FALSE
  CString                        m_sFilename;                      //The name of the file to load the bitmap from (used if m_bUseFile is TRUE)
  HICON                          m_hIcon;                          //The icon to use for this window
  BOOL                           m_bTransparent;                   //Should the image be drawn transparent
  COLORREF                       m_clrTransparent;                 //The transparent color to use
  BOOL                           m_bDraggable;                     //Should the splash window be draggable
  lpfnSetLayeredWindowAttributes m_lpfnSetLayeredWindowAttributes; //Pointer to the function "SetLayeredWindowAttributes"
  BOOL                           m_bDropShadow;                    //Should the window have a drop shadow effect

  friend class CSplashThread;    //To allow the splash thread class to access to this classes members
  friend class CSplashFactory;   //To allow the class factory to access to this classes members
};


//GUI thread in which the splash window is run
class CSplashThread : public CWinThread
{
public:
		CSplashWnd*    m_pSplashScreen;          //Pointer the CWnd splash screen
protected:
//Constructors / Destructors
	CSplashThread();
  virtual ~CSplashThread();

	DECLARE_DYNCREATE(CSplashThread)

	//{{AFX_VIRTUAL(CSplashThread)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSplashThread)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

//Member variables
  CRuntimeClass* m_pRuntimeClassSplashWnd; //The runtime class version of "m_pSplashScreen"
//	CSplashWnd*    m_pSplashScreen;          //Pointer the CWnd splash screen
  CEvent         m_SplashCreated;          //Event using to synchronise our startup
  BOOL           m_bInitOK;                //Was InitInstance successful

  friend class CSplashFactory; //To allow the class factory to access to this classes members
};


//Class which looks after creating the splash window in the separate thread
class CSplashFactory
{
public:
//Constructors / Destructors
  CSplashFactory();
  ~CSplashFactory();

//Methods
  BOOL Create(CRuntimeClass* pRuntimeClassSplashWnd);  
  BOOL Close(CWnd* pWndToGainFocus = NULL);

//protected:
  CSplashThread* m_pSplashThread; //The GUI thread we are managing
};

#endif //__SPLASHER_H__
