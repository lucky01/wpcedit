// HexEditor.h : main header file for the HEXEDITOR application
//

#if !defined(AFX_HEXEDITOR_H__F8480F24_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
#define AFX_HEXEDITOR_H__F8480F24_B2D1_11D7_9734_00045A4C0065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "defines.h"
#include "dmd.h"

#define UWM_ARE_YOU_ME_MSG _T("UWM_ARE_YOU_ME-{F27C57BF-AF6A-4ffe-A445-994C232741FE}")
#define DECLARE_USER_MESSAGE(name) \
     static const UINT name = ::RegisterWindowMessage(name##_MSG);
DECLARE_USER_MESSAGE(UWM_ARE_YOU_ME);

#define STARTING_ICON_INDEX_ABOUT_BOX_ANIMATION 16
const static int icons[] = 
	{IDI_ICON44, IDI_ICON43, IDI_ICON42, IDI_ICON41, IDI_ICON40, IDI_ICON39, IDI_ICON38, IDI_ICON37,
	 IDI_ICON36, IDI_ICON35, IDI_ICON34, IDI_ICON33, IDI_ICON32, IDI_ICON31, IDI_ICON30, IDI_ICON29,
	 IDI_ICON28, IDI_ICON29, IDI_ICON30, IDI_ICON31, IDI_ICON32, IDI_ICON33, IDI_ICON34, IDI_ICON35,
	 IDI_ICON36, IDI_ICON37, IDI_ICON38, IDI_ICON39, IDI_ICON40, IDI_ICON41, IDI_ICON42, IDI_ICON43,
	 IDI_ICON44};



/////////////////////////////////////////////////////////////////////////////
// CHexEditorApp:
// See HexEditor.cpp for the implementation of this class
//

class CHexEditorApp : public CWinApp
{
public:
	CHexEditorApp();
	DMD *DMDDialogPtr;
	DMD *FONTDialogPtr;
	DMD *ANIDialogPtr;

	RegistrySettings ProgramSettings;
	void LoadFactoryDefaultProgramSettings(RegistrySettings *Ptr);
	void LoadProgramSettings(RegistrySettings *Ptr);
	void SaveProgramSettingsToRegistry(RegistrySettings *Ptr);
	void ValidateProgramSettings(RegistrySettings *Ptr);

	void CalculateMD5(BYTE *test, UINT size, BYTE *digest);
	BOOL ProgramInitialized;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
protected:
	CSingleDocTemplate* pDocTemplate;
	static BOOL CALLBACK searcher(HWND hWnd, LPARAM lParam);
//	void md5_process(md5_state_t *pms, const md5_byte_t *data /*[64]*/);
//	void md5_init(md5_state_t *pms);
//	void md5_append(md5_state_t *pms, const md5_byte_t *data, int nbytes);
//	void md5_finish(md5_state_t *pms, md5_byte_t digest[16]);





// Implementation
	//{{AFX_MSG(CHexEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDITOR_H__F8480F24_B2D1_11D7_9734_00045A4C0065__INCLUDED_)
