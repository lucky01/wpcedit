/////////////////////////////////////////////////////////////////////////////
// HexEditorView.cpp : implementation of the CHexEditorView class
// --------------------------------------------------------------
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uMSG_MOUSEWHEEL;

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView

IMPLEMENT_DYNCREATE(CHexEditorView, CScrollView)

BEGIN_MESSAGE_MAP(CHexEditorView, CScrollView)
	//{{AFX_MSG_MAP(CHexEditorView)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_REGISTERED_MESSAGE( uMSG_MOUSEWHEEL, OnWheel )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView construction/destruction

CHexEditorView::CHexEditorView()
{
	uMSG_MOUSEWHEEL = RegisterWindowMessage( "MSWHEEL_ROLLMSG" );
	Reset();
}

CHexEditorView::~CHexEditorView()
{
}

BOOL CHexEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// load font
	m_cFont.CreatePointFont( 100, "Terminal" );

	return CScrollView::PreCreateWindow(cs);
}

void CHexEditorView::Reset()
{
	m_nCurSel = 0;
	m_nCurSelEnd = 0;
	m_nLineLength = 0;
	m_nLineCount = 0;
	m_nVisStart = m_nVisEnd = 0;
	m_ptMouse.x = m_ptMouse.y = -1;
	m_fDraggingMouse = FALSE;
}

void CHexEditorView::UpdateScrollbars()
{	
	// calculate how many bytes can be displayed across
	CRect rcClient;
	GetClientRect( &rcClient );
	m_nLineLength = ( rcClient.Width() - 80 ) / 40;

	if (!m_nLineLength)    // Prevent  a possible divide-by-zero bug below
		m_nLineLength = 1;

	// make calculations
	CSize sizeTotal;
	sizeTotal.cx = 1;
	sizeTotal.cy = GetDocument()->m_nBufferLength / m_nLineLength * 20 + 100;
//	if (!m_nLineLength)
//	{
//		AfxMessageBox("Problem");
//		return;
//	}
	m_nLineCount = GetDocument()->m_nBufferLength / m_nLineLength;

	// set scrollbar sizes
	SCROLLINFO siInfo;
	siInfo.cbSize = sizeof( SCROLLINFO );
	siInfo.fMask = SIF_RANGE;
	siInfo.nMin = 0; siInfo.nMax = sizeTotal.cy;
	SetScrollSizes(MM_TEXT, sizeTotal); // this manages most of the tedious stuff
	SetScrollInfo( SB_VERT, &siInfo ); // here we actually set the size
}

void CHexEditorView::MakeCursorVisible()
{
	if( m_nCurSel >= m_nVisStart && m_nCurSel <= m_nVisEnd )
		return;

	if (!m_nLineLength) // Prevent divide-by-zero
		m_nLineLength = 1;
	CPoint ptScroll = GetScrollPosition();
	if( m_nCurSel < m_nVisStart )
	{
		while( m_nCurSel < ( ptScroll.y / 20 * m_nLineLength ) )
		{
			ptScroll.y -= 60;
			ScrollToPosition( ptScroll );
		}
	} else if( m_nCurSel > m_nVisEnd )
	{
		unsigned int nStart = m_nVisStart;
		unsigned int nEnd = m_nVisEnd - m_nVisStart;
		while( m_nCurSel > nEnd + nStart )
		{
			nStart = ( ptScroll.y / 20 * m_nLineLength );
			ptScroll.y += 60;
			ScrollToPosition( ptScroll );
		}
	}
}

void CHexEditorView::GetSel( unsigned int& nStart, unsigned int& nEnd )
{
	nStart = ( m_nCurSel <= m_nCurSelEnd ) ? m_nCurSel : m_nCurSelEnd;
	nEnd = ( nStart == m_nCurSel ) ? m_nCurSelEnd : m_nCurSel;
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView drawing

void CHexEditorView::OnDraw(CDC* pDC)
{
	CHexEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	unsigned int i, nMaxX=0;

	if (!m_nLineLength)    // prevent a divide-by-zero error
		m_nLineLength = 1;

	// save dc
	int nSavedDC = pDC->SaveDC();

	// get rid of the offset
	pDC->SetWindowOrg( 0, 0 );
	pDC->SetViewportOrg( 0, 0 );

	// get rects
	CRect rcRectWnd, rcRectClient;
	GetWindowRect( &rcRectWnd );
	GetClientRect( &rcRectClient );

	// get background brush
	CBrush bBkg; bBkg.FromHandle( GetSysColorBrush( COLOR_WINDOW ) );

	// if we lack data, just clear and exit
	if( pDoc->m_nBufferLength == 0 )
	{
		pDC->FillRect( &rcRectClient, &bBkg );
		pDC->RestoreDC( nSavedDC );
		return;
	}

	// create our memory dc
	CDC *pMemDC = new CDC();
    CBitmap bMemBMP;
	pMemDC->CreateCompatibleDC( pDC );
	bMemBMP.CreateCompatibleBitmap( pDC, rcRectClient.right, rcRectClient.bottom );
	CBitmap *pOldBitmap = pMemDC->SelectObject( &bMemBMP );

	// erase the background
	pMemDC->FillRect( &rcRectClient, &bBkg );

	// select font
	CGdiObject* pOldObj = pMemDC->SelectObject( &m_cFont );
	
	// figure what to draw
	m_nVisEnd = pDoc->m_nBufferLength;
	CPoint ptScroll = GetScrollPosition();
	m_nVisStart = ptScroll.y / 20 * m_nLineLength;
	m_nVisEnd = ( m_nVisEnd != 0 ) ? ( ( rcRectClient.Height() / 20 + 1 ) * m_nLineLength + m_nVisStart ) : 0;
	if( m_nVisEnd >= pDoc->m_nBufferLength )
		m_nVisEnd = pDoc->m_nBufferLength;

	// calculate rects
	CRect rcCharData, rcHexData;
	// data
	rcCharData.left = rcRectClient.left + 20;
	rcCharData.top = rcRectClient.top;
	rcCharData.right = rcRectClient.right / 2 - 20;
	rcCharData.bottom = rcRectClient.bottom - 10;
	if( rcCharData.Width() % 20 != 0 )
		rcCharData.right -= rcCharData.Width() % 20;
	nMaxX = rcCharData.Width() / 20;
	if (!nMaxX)   // Prevent divide-by-zero bug
		nMaxX = 1; 
	// hex
	rcHexData.left = rcRectClient.right / 2 + 20;
	rcHexData.top = rcRectClient.top;
	rcHexData.right = rcRectClient.right - 20;
	rcHexData.bottom = rcRectClient.bottom - 10;
	if( rcHexData.Width() % 20 != 0 )
		rcHexData.right -= rcHexData.Width() % 20;

	// handle the mouse input
	if( m_ptMouse.x != -1 )
	{
		BOOL fValid = TRUE;
		if( rcCharData.PtInRect( m_ptMouse ) )
		{
			m_ptMouse.x -= rcCharData.left;
			m_ptMouse.y -= rcCharData.top;
		} else if( rcHexData.PtInRect( m_ptMouse ) )
		{
			m_ptMouse.x -= rcHexData.left;
			m_ptMouse.y -= rcHexData.top;
		} else
			fValid = FALSE;

		if( fValid )
		{
			int nX = ( m_ptMouse.x - ( m_ptMouse.x % 20 ) ) / 20;
			int nY = ( m_ptMouse.y - ( m_ptMouse.y % 20 ) ) / 20;
			int nSelAdd = nX + ( nY * m_nLineLength ) + m_nVisStart;
			if( !m_fDraggingMouse )
				m_nCurSel = nSelAdd;
			m_nCurSelEnd = nSelAdd;
		}
	}

	CRect rcOut;
	unsigned int nAddX;

	// write out the data buffer
	rcOut = rcCharData;
	nAddX = 0;
	LPTSTR pData = pDoc->m_szDataBuffer.GetBuffer( pDoc->m_nBufferLength );
	for( i=m_nVisStart; i < m_nVisEnd; i++ )
	{
		// if it is over, increment our y
		if( ( i - m_nVisStart ) != 0 && ( i - m_nVisStart ) % nMaxX == 0 )
		{
			nAddX = 0;
			rcOut.top += 20;
		}
		// make the addition
		rcOut.left = rcCharData.left + nAddX;
		// fill behind current selection
		if( ( i >= m_nCurSel && i <= m_nCurSelEnd ) || ( i >= m_nCurSelEnd && i <= m_nCurSel ) )
		{
			pMemDC->SetBkColor( RGB( 220, 220, 220 ) );
		} else
		{	
			pMemDC->SetBkColor( GetSysColor( COLOR_WINDOW ) );
		}
		// draw the text
		if( pData[i] )
			pMemDC->DrawText( pData[i], &rcOut, DT_LEFT	| DT_NOCLIP );
		// add
		nAddX += 20;
	}

	// write out the data buffer in hex
	rcOut = rcHexData;
	nAddX = 0;
	CString szOut;
	pData = pDoc->m_szDataBuffer.GetBuffer( pDoc->m_nBufferLength );
	for( i=m_nVisStart; i < m_nVisEnd /*- 1*/; i++ )
	{
		// if it is over, increment our y
		if( ( i - m_nVisStart ) != 0 && ( ( i - m_nVisStart ) % nMaxX ) == 0 )
		{
			nAddX = 0;
			rcOut.top += 20;
		}
		// make the addition
		rcOut.left = rcHexData.left + nAddX;
		// fill behind current selection
		if( ( i >= m_nCurSel && i <= m_nCurSelEnd ) || ( i >= m_nCurSelEnd && i <= m_nCurSel ) )
		{
			pMemDC->SetBkColor( RGB( 220, 220, 220 ) );
		} else
		{	
			pMemDC->SetBkColor( GetSysColor( COLOR_WINDOW ) );
		}
		// draw the text		
		szOut.Format( "%02x", (unsigned char)pData[i] );
		szOut.MakeUpper();
		pMemDC->DrawText( szOut, &rcOut, DT_LEFT | DT_NOCLIP );
		// add
		nAddX += 20;
	}

	// reset the old object
	if( pOldObj )
		pMemDC->SelectObject( pOldObj );

	// copy to the real device context
	pDC->BitBlt( 0, 0, rcRectClient.right, rcRectClient.bottom, pMemDC, 0, 0, SRCCOPY );

	// restore dc
	if( pOldBitmap )
		pMemDC->SelectObject( pOldBitmap );
	bMemBMP.DeleteObject();
	pDC->RestoreDC( nSavedDC );

	delete pMemDC;
}

void CHexEditorView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	UpdateScrollbars();
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView printing

BOOL CHexEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	//return DoPreparePrinting(pInfo);
	// WILL BE IN NEXT VERSION
	MessageBox( "Printing Not Yet Implemented" );
	return FALSE;
}

void CHexEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHexEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView diagnostics

#ifdef _DEBUG
void CHexEditorView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHexEditorView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

CHexEditorDoc* CHexEditorView::GetDocument() // non-debug version is inline
{
#ifdef _DEBUG
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHexEditorDoc)));
#endif
	return (CHexEditorDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CHexEditorView message handlers

void CHexEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	BOOL fInvalidate = FALSE;
	BOOL fErase = FALSE;
	if( nChar == VK_LEFT )
	{
		if( m_nCurSel > 0 ) m_nCurSelEnd = --m_nCurSel;
		fInvalidate = TRUE;
	}
	if( nChar == VK_RIGHT )
	{
		m_nCurSelEnd = ++m_nCurSel;
		if( m_nCurSel >= GetDocument()->m_nBufferLength )
			m_nCurSel = GetDocument()->m_nBufferLength - 1;
		fInvalidate = TRUE;
	}
	if( nChar == VK_UP )
	{
		m_nCurSel -= m_nLineLength;
		if( m_nCurSel < 0 ) m_nCurSel = 0;
		m_nCurSelEnd = m_nCurSel;
		fInvalidate = TRUE;
	}
	if( nChar == VK_DOWN )
	{
		m_nCurSel += m_nLineLength;
		if( m_nCurSel >= GetDocument()->m_nBufferLength )
			m_nCurSel = GetDocument()->m_nBufferLength - 1;
		m_nCurSelEnd = m_nCurSel;
		fInvalidate = TRUE;
	}
	if( nChar == VK_DELETE || nChar == VK_BACK )
	{
		// error checking
		if( ( nChar == VK_BACK && m_nCurSel <= 0 ) || m_nCurSel >= GetDocument()->m_nBufferLength - 1 )
			return;
		// d_elete the data
		unsigned int nStart, nEnd;
		GetSel( nStart, nEnd );
		GetDocument()->DeleteData( nStart, nEnd - nStart + 1 );
		// move the cursor
		if( nChar == VK_BACK ) m_nCurSel = m_nCurSelEnd = ( nStart - 1 );
		else m_nCurSelEnd = m_nCurSel = nStart;
		// update scroll bars
		UpdateScrollbars();
		fErase = fInvalidate = TRUE;
	}

	if( fInvalidate )
	{
		MakeCursorVisible();
		Invalidate( fErase );
		return;
	}
	
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CHexEditorView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;//CScrollView::OnEraseBkgnd(pDC);
}

void CHexEditorView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// windows doesnt natively use 32 bit data to track the pos
	// so if we can, we need to get it
	if( nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION )
	{
		HWND hWndScroll = ( pScrollBar ) ? pScrollBar->m_hWnd : m_hWnd;
		SCROLLINFO siInfo;
		siInfo.cbSize = sizeof( SCROLLINFO );
		siInfo.fMask = SIF_TRACKPOS;
		::GetScrollInfo( hWndScroll, SB_VERT, &siInfo );
		nPos = siInfo.nTrackPos;
	}

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate( FALSE );
}

void CHexEditorView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate( FALSE );
}

void CHexEditorView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ptMouse = point;	
	CScrollView::OnLButtonDown(nFlags, point);
	Invalidate( FALSE );
}

void CHexEditorView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_fDraggingMouse = FALSE;
	m_ptMouse.x = m_ptMouse.y = -1;
	Invalidate( FALSE );
	CScrollView::OnLButtonUp(nFlags, point);
}

void CHexEditorView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( m_ptMouse.x != -1 )
	{
		m_fDraggingMouse = TRUE;
		m_ptMouse = point;
		Invalidate( FALSE );
	}

	CScrollView::OnMouseMove(nFlags, point);
}


void CHexEditorView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	if( cx || cy )
		UpdateScrollbars();	
}

void CHexEditorView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// load the menu
	CMenu cMenu;
	cMenu.LoadMenu( IDR_CONTEXT );
	CMenu* pPopup = cMenu.GetSubMenu( 0 );	

	// convert point
	ClientToScreen( &point );

	// track popup menu
	DWORD dwSelection = pPopup->TrackPopupMenu( (TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD ),
												point.x, point.y, this );
	// destroy it
	pPopup->DestroyMenu();

	// act on selection
	if( dwSelection == ID_CONTEXT_INSERTBYTES )
		GetDocument()->InsertBytes(); // use document's functionality
	if( dwSelection == ID_CONTEXT_EDITINTEGER || dwSelection == ID_CONTEXT_EDITHEX )
	{
		// get the selection
		unsigned int nStart, nEnd;
		GetSel( nStart, nEnd );
		// make sure they havent selected more than 4 bytes
		if( nEnd + 1 - nStart > 4 )
		{
			MessageBox( "Too many bytes selected - max 4", "Error" );
			return;
		}
		// edit the data
		GetDocument()->EditData( nStart, nEnd, ( dwSelection == ID_CONTEXT_EDITHEX ) );
		Invalidate( TRUE );
	}
	if( dwSelection == ID_CONTEXT_EDITSTRING )
	{
		// get the selection
		unsigned int nStart, nEnd;
		GetSel( nStart, nEnd );
		// edit the data
		GetDocument()->EditString( nStart, nEnd );
		Invalidate( TRUE );
	}

	CScrollView::OnRButtonUp(nFlags, point);
}

LONG CHexEditorView :: OnWheel( UINT nFlags, LONG pValue )
{
	if( nFlags & 0x0100 ) // rolled up
	{
		OnVScroll( SB_LINEUP, 0, NULL );
	}
	else // rolled down
	{
		OnVScroll( SB_LINEDOWN, 0, NULL );
	}
	return 0;
}
