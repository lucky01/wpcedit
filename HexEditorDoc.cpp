/////////////////////////////////////////////////////////////////////////////
// HexEditorDoc.cpp : implementation of the CHexEditorDoc class
// ------------------------------------------------------------
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

#include "HexEditorDoc.h"
#include "HexEditorView.h"

#include "DLGInsertData.h"
#include "DLGEditData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexEditorDoc

IMPLEMENT_DYNCREATE(CHexEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CHexEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CHexEditorDoc)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditorDoc construction/destruction

CHexEditorDoc::CHexEditorDoc()
{
	Reset();
}

CHexEditorDoc::~CHexEditorDoc()
{
	Reset();
}

BOOL CHexEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// clear out our buffers
	Reset();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHexEditorDoc serialization

void CHexEditorDoc::Serialize(CArchive& ar)
{
	// save/load
	if (ar.IsStoring())
	{
		// save
		ar.Write( m_szDataBuffer.GetBuffer(0), m_nBufferLength );
	}
	else
	{
		// tell view
		GetView()->Reset();
		
		// create a progress bar
		dlgProgress.Create( IDD_PROGRESS, GetView() );
		dlgProgress.SetProgress( 20, "Loading File Into Data Buffer" ); // 20%
		dlgProgress.m_wndAbort.EnableWindow( FALSE ); // no abort, sry

		// load the data
		LPTSTR pszBuffer = m_szDataBuffer.GetBuffer(ar.GetFile()->GetLength());
		m_nBufferLength = ar.Read( pszBuffer, ar.GetFile()->GetLength() );
		m_szDataBuffer.ReleaseBuffer();

		dlgProgress.SetProgress( 100, "Done!" ); // 100%
		dlgProgress.DestroyWindow();
	}
}

void CHexEditorDoc::Reset()
{
	m_szDataBuffer.Empty();
	m_nBufferLength = 0;
}

long CHexEditorDoc::GetData( CString szData )
{
	long nRet=0;
	szData.MakeLower();
	if( szData.Right( 1 ) == 'i' )
	{
		sscanf( szData.GetBuffer(0), "%di", &nRet );
	} else if( szData.Right( 1 ) == 's' )
	{
		sscanf( szData.GetBuffer(0), "%cs", &nRet );
	} else
	{
		if( szData.Right( 1 ) == 'h' )
#if MFC_VER < 0x0600
			szData.TrimRight();
#else
			szData.TrimRight( 'h' );
#endif
		sscanf( szData.GetBuffer(0), "%x", &nRet );
	}
	return nRet;
}

CString CHexEditorDoc::SetData( long nData, BOOL fHex )
{
	CString szRet;
	if( fHex )
		szRet.Format( _T("%x"), nData );
	else
		szRet.Format( _T("%d"), nData );
	return szRet;
}

void CHexEditorDoc::InsertBytes()
{
	// prompt for how many bytes and what pattern to fill it with
	CDLGInsertData dlg;
	if( dlg.DoModal() == IDOK )
	{
		// get how many bytes
		int nAmt = 0, i;
		sscanf( dlg.m_szInsertAmt.GetBuffer(0), "%d", &nAmt );
		// get our data
		long nData = GetData( dlg.m_szData );
		// build the data array
		int nDataCount = 0;
		if( nData < 256 ) nDataCount = 1;
		else if( nData < 65536 ) nDataCount = 2;
		else if( nData < 16777216 ) nDataCount = 3;
		else nDataCount = 4;
		int* nDataArray = new int[nDataCount];
		for( i=0; i < nDataCount; i++ )
		{
			nDataArray[i] = nData >> ( 8 * i );
		}
		// insert data
		unsigned int nStart = GetView()->m_nCurSel;
#if MFC_VER < 0x0600
		CString LeftString;
		CString RightString;
		char *Ptr;
#endif

		if( nStart < 0 || nStart >= m_nBufferLength )
			nStart = m_nBufferLength-1;
		for( i=0; i < nAmt; i++ )
		{
#if MFC_VER < 0x0600
			//
			// Need to write some code to insert here.
			// debug error fix this
			LeftString = RightString = m_szDataBuffer;
			LeftString.Left(nStart);
			Ptr = LeftString.GetBuffer(0);
			Ptr += strlen(Ptr);
			*Ptr++ = nDataArray[(i % nDataCount)];
			LeftString.ReleaseBuffer(-1);
			RightString.Left(nStart + 1);
			m_szDataBuffer = LeftString + RightString;
#else
			m_szDataBuffer.Insert( nStart, nDataArray[i%nDataCount] );
#endif
		}
		// update buffer length
		m_nBufferLength += nAmt;
		// redraw
		GetView()->UpdateScrollbars();
		GetView()->Invalidate( TRUE );
		delete nDataArray;
	}
}

void CHexEditorDoc::EditData( int nStart, int nEnd, BOOL fHex )
{
	int nSize = nEnd - nStart + 1;
	// get the data
	// NOTE - CSTRING::MID DOES NOT WORK DUE TO ITS USE OF GETLENGTH,
	// WHICH STOPS AT NULLS, WHICH ARENT THE END OF BUFFER D:
	// IN FACT, MOST CSTRING OPERATIONS DONT WORK. I USE CSTRING FOR
	// ITS EASY MEMORY MANAGEMENT
	long nData = 0;
	LPTSTR pData = m_szDataBuffer.GetBuffer(0);
	CString szData;
	for( int i = nStart; i <= nEnd; i++ )
		szData += pData[i];
	for( int i = 0; i < nSize; i++ )
		nData += szData[nSize-i-1] << ( i * 8 ); //szData[nSize-i-1] << ( i * 8 );
	szData = SetData( nData, fHex );

	// create the dialog
	CDLGEditData dlg;
	// set input control
	dlg.m_szInput = szData;
	// set the max length
	if( fHex )
		dlg.m_nMaxLength = nSize * 2;
	else
		dlg.m_nMaxLength = 50;
	// go modal
	if( dlg.DoModal() != IDOK )
		return;

	// get the data
	if( !fHex )
		dlg.m_szInput += 'i';
	nData = GetData( dlg.m_szInput );

	// create the buffer to insert
	szData.Empty();	
	int nDataCount = 0;
	if( nData < 256 ) nDataCount = 1;
	else if( nData < 65536 ) nDataCount = 2;
	else if( nData < 16777216 ) nDataCount = 3;
	else nDataCount = 4;
	for(int i=0; i < nDataCount; i++ )
	{
		szData += (char) ( nData >> ( 8 * (nDataCount - i - 1) ) );
	}

	// insert the n_ew data
	for(int i = 0; i < nSize; i++ )
	{
		if( i >= nDataCount )
			pData[nStart + i] = 0;
		else
			pData[nStart + i] = szData[i];
	}
	m_szDataBuffer.ReleaseBuffer();
}

void CHexEditorDoc::EditString( int nStart, int nEnd )
{
	// get the data
	int nSize = nEnd - nStart + 1;
	LPTSTR pData = m_szDataBuffer.GetBuffer(0);
	CString szData;
	for( int i = nStart; i <= nEnd; i++ )
		szData += pData[i];

	// create the dialog
	CDLGEditData dlg;
	dlg.m_szInput = szData;
	dlg.m_nMaxLength = nSize;
	if( dlg.DoModal() != IDOK )
		return;

	// insert the n_ew data
	for(int i = 0; i < nSize, i < dlg.m_szInput.GetLength(); i++ )
	{
		pData[nStart + i] = dlg.m_szInput[i];
	}
	m_szDataBuffer.ReleaseBuffer();
}

void CHexEditorDoc::DeleteData( int nStart, int nEnd )
{
#if MFC_VER < 0x0600
	CString LeftString = m_szDataBuffer;
	CString RightString = m_szDataBuffer;
	LeftString.Left(nStart + 1);
	RightString.Left(nStart + nEnd);
	m_szDataBuffer = LeftString + RightString;
#else
	m_szDataBuffer.Delete( nStart, nEnd );
#endif
	m_nBufferLength -= nEnd - nStart + 1;
}

CHexEditorView* CHexEditorDoc::GetView()
{
	// find the first view - if there are no views
	// we must return NULL

	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
		return NULL;

	// find the first view that is a CRichEditView

	CView* pView;
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CHexEditorView)))
			return (CHexEditorView*) pView;
	}

	// can't find one--return NULL

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorDoc diagnostics

#ifdef _DEBUG
void CHexEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHexEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexEditorDoc commands

void CHexEditorDoc::OnEditInsert() 
{
	InsertBytes();
}
