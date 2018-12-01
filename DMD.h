#if !defined(AFX_DMD_H__0169C360_5BDA_499F_89BA_3FE7FCB29D09__INCLUDED_)
#define AFX_DMD_H__0169C360_5BDA_499F_89BA_3FE7FCB29D09__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DMD.h : header file
//

#define DMD_ROWS         32
#define DMD_COLUMNS     128
#define DMD_PAGE_BYTES  ((DMD_ROWS * DMD_COLUMNS)/8)  // 512 bytes

#define PAGE_LENGTH                 0x4000
#define BASE_CODE_ADDR_PAGED_ROM    0x4000
#define BASE_CODE_ADDR_NONPAGED_ROM 0x8000
#define NONPAGED_LENGTH             0x8000
#define NONPAGED_BANK_INDICATOR     0xFF

#define WRITE_TYPE_COLUMNS       0
#define WRITE_TYPE_ROWS          1

#define HITTYPE_NONE                    0
#define HITTYPE_TBL_ADDR_ADDR_ADDR      1
#define HITTYPE_TBL_ADDR_ADDR           2
#define HITTYPE_TBL_ADDR                3

#define IMAGE_CODE_MONOCHROME            0x00   // Single color pixel data
#define IMAGE_CODE_FD                    0xFD   // Unsure (maybe inversed paint?) IJ uses.  Use normal header 0x00 processing
#define IMAGE_CODE_BICOLOR_INDIRECT      0xFE   // Bi-color pixel data contains one plane and pointer to the other
#define IMAGE_CODE_BICOLOR_DIRECT        0xFF   // Bi-color pixel data contains both planes

#define PIXEL_HEIGHT  5
#define PIXEL_WIDTH   5

#define MAX_GRAPHIC_INDEX  2048 // at this time we will restrict value

#define IMAGE_SHIFT_X_PIXEL_COUNT     8
#define IMAGE_SHIFT_Y_PIXEL_COUNT     8

#define PLANE0_ON      0x01
#define PLANE0_XORED   0x02
#define PLANE0_SKIPPED 0x04
#define PLANE1_ON      0x10
#define PLANE1_XORED   0x20
#define PLANE1_SKIPPED 0x40

#define DMD_FULLFRAME_PAINT_DIM     0x01
#define DMD_FULLFRAME_PAINT_MEDIUM  0x02
#define DMD_FULLFRAME_PAINT_BLENDED 0x04

#define PLANE_STATUS_VALID                 0
#define PLANE_STATUS_INVALID               1
#define PLANE_STATUS_UNKNOWN_TYPE          2
#define PLANE_STATUS_UNIMPLEMENTED_TYPE    3
#define PLANE_STATUS_TABLEENTRYOUTOFRANGE  4
#define PLANE_STATUS_BADDIMENSION          5
#define PLANE_STATUS_IMAGEOUTOFRANGE       6

#define DEFAULT_DEBOUNCE_TIME  500  // 1/2 second before repeating graphics quickly
#define DEBOUNCE_STATE_IDLE        0
#define DEBOUNCE_STATE_DEBOUNCING  1
#define DEBOUNCE_STATE_DONE        2

#define DEBUG_KEY_BIT_SHIFTKEYS           0x01
#define DEBUG_KEY_BIT_CONTROLKEYS         0x02

const static char StatusText [(PLANE_STATUS_IMAGEOUTOFRANGE + 1)][32] = 
	{
		"Valid Decoding",
		"Invalid",
		"Unknown Type",
		"Unimplemented Type",
		"Table out of Range",
		"Bad Dimension",
		"Image out of Range",
	};



/////////////////////////////////////////////////////////////////////////////
// DMD dialog
struct COMMONData
{
	unsigned long ROMSize;
	unsigned char TotalPages;    // includes non-banked, conceptual pages (2 pages nonbanked)
	unsigned char BasePageIndex;
	LPTSTR StartPtr;
	unsigned char *EndPtr;
};

typedef unsigned char Plane[DMD_PAGE_BYTES];
struct DMDPlane
{
	unsigned char Plane_Status;
	unsigned int Plane_Size;
	Plane Plane_Data;
	Plane Plane_Skipped;
	Plane Plane_XorFlags;
	Plane Plane_XorBits;
};

struct DMDPlanes
{
	DMDPlane Plane0;
	DMDPlane Plane1;
};

struct FULLFRAMEImageData
{
	unsigned long TableAddress;
	int CurrentImageIndex;
	//
	DMDPlanes Planes;
};

struct VARIABLESIZEDImageData
{
	unsigned long TableAddress;
	//
	int CurrentTableIndex;
	int CurrentImageIndex;
	int CurrentImageXSize;
	int CurrentImageYSize;
	//
	int CurrentImageXShift;
	int CurrentImageYShift;
	//
	int minTableIndex;
	int minImageIndex;
	int maxTableIndex;
	int maxImageIndex;
	//
	DMDPlanes Planes;
};

struct ImageHeader
{
	unsigned char SpecialFlagByte;
	unsigned char RepeatBytes[8];
	unsigned char ReadMask;
};

typedef enum
{
   ThisPixel_Off = 0,
   ThisPixel_On,
   ThisPixel_Xored,
   ThisPixel_Skipped
} ThisPixel;

class DMD : public CDialog
{
// Construction
public:
//	DMD(CWnd* pParent = NULL);   // standard constructor
	DMD(CWnd* pParent = NULL, RegistrySettings *mainptr = NULL, int DialogType = DMD_DIALOG_TYPE_GRAPHICS);   // standard constructor
	~DMD();
	BOOL Create();
	int Init();

private:
	COMMONData CommonData;
	FULLFRAMEImageData FullFrameImageData;
	VARIABLESIZEDImageData VariableSizedImageData;;
	int dialogType;
	int debugKeyBitmask;
    int selectedTitleBox;
	CString TmpStr;
    BOOL bWiped;

	Plane PreviousPlaneDataPane0;
	Plane PreviousPlaneDataPane1;

	void CheckKeyStateForDebugFlags();
	void PaintDMDPanelImage(CPaintDC *pDc, DMDPlanes* pPlanes, unsigned char PaneMask);
	void DecodePlaneInit(DMDPlane *pPlane);
	void DecodeCurrentIndex(void);
	void DecodePreviousIndex(int count);
	void DecodeNextIndex(int count);
    void ButtonHandlerNext(int count);
    void ButtonHandlerPrevious(int count);

	void DecodeVariableSizedImage(unsigned char **Source, DMDPlanes *pPlanes, int TableIndex);
	unsigned char DecodeVariableSizedImage_Centered(unsigned char **SourcePtr, unsigned char **DestPtr, int ImageHeight, int ImageWidth);
	void DecodeVariableSizedImageIndex_NoHeader(unsigned char **SourcePtr, DMDPlanes *pPlanes, int TableHeight);
	void DecodeVariableSizedImageIndex_Header(unsigned char **SourcePtr, DMDPlanes *pPlanes, int TableHeight, int TableIndex);
	void DecodeFullFrameGraphic(unsigned long GraphicIndex);
	void DecodeImageToPlane(int Index, DMDPlane *pPlane);
	unsigned char DecodeFullFrameGraphicImage(unsigned char **Source, DMDPlane *pPlane);
	void Decode_00(unsigned char **Source, unsigned char *Dest);
	void Decode_01(unsigned char **Source, unsigned char *Dest);
	void Decode_02(unsigned char **Source, unsigned char *Dest);
	void Decode_03(unsigned char **Source, unsigned char *Dest);
	void Decode_04(unsigned char **Source, unsigned char *Dest);
	void Decode_05(unsigned char **Source, unsigned char *Dest);
	void Decode_06(unsigned char **Source, unsigned char *Dest, unsigned char *XorFlags, unsigned char *XorBits);
	void Decode_07(unsigned char **Source, unsigned char *Dest, unsigned char *XorFlags, unsigned char *XorBits);
	void Decode_08(unsigned char **Source, unsigned char *Dest, unsigned char *Skipped);
	void Decode_09(unsigned char **Source, unsigned char *Dest, unsigned char *Skipped);
	void Decode_0A(unsigned char **Source, unsigned char *Dest, unsigned char *Skipped);
	void Decode_0B(unsigned char **Source, unsigned char *Dest, unsigned char *Skipped);
	unsigned char ReadNext8BitValue(struct ImageHeader *Header, unsigned char **SourcePtr);
	unsigned char ReadNextBit(struct ImageHeader *Header, unsigned char **SourcePtr);
	void WriteNext8BitValue(unsigned char **DestPtr, unsigned int *WriteCounterPtr,unsigned char ch, unsigned char Type);
	void Decode_01or02(unsigned char **SourcePtr, unsigned char **DestPtr, unsigned char Type);
	void Decode_04or05(unsigned char **SourcePtr, unsigned char **DestPtr, unsigned char Type);
	void Decode_06or07(unsigned char **SourcePtr, unsigned char **DestPtr, unsigned char **XorFlagsPtr, unsigned char **XorBitsPtr, unsigned char Type);
	void Decode_08or09(unsigned char **SourcePtr, unsigned char **DestPtr, unsigned char **Skipped, unsigned char Type);
	void Decode_0Aor0B(unsigned char **SourcePtr, unsigned char **DestPtr, unsigned char **Skipped, unsigned char Type);

	void InvalidateDMDPages();
	void UpdateStaticTextBoxes();
	void UpdateStaticTextBoxesFullFrameGraphics();
	void UpdateStaticTextBoxesVariableSizedImage();
	void UpdateControls();
	void SaveDMDRegistrySettings();
	void UpdateStaticTextBoxesVariableSizedImagePane(int Pane);
	void UpdateStaticTextBoxesVariableSizedImagePrint(int TableIndex, int ImageIndex, CStatic *pWnd, CStatic *pWndTitle, unsigned char Status);
	void UpdateCheckboxText();

	void DebugKeyMsgStrPrint(CString str, int KeyMask);
	void DebugShiftKeyMsgStrPrint(CString str);
	void DebugControlKeyMsgStrPrint(CString str);
	
	int GetROMAddressFromWPCAddrAndPage(unsigned long *pRomAddr, unsigned long Addr, unsigned char Page);
	int ExtractWPCAddrAndPageFromBuffer(LPTSTR pSrc, unsigned long *pDstAddr, unsigned char *pDstPage);
	int GetROMAddressFromAddrOf3ByteWPCAddrPage(LPTSTR pSrc, unsigned long *pDst);
	int ProcessHitType(int HitType, LPTSTR HitTablePtr, LPTSTR HitPagePtr, LPTSTR Ptr, unsigned long *pTbl);
	
    int InitCommon();
	int InitTableAddrs();

	int PreAnalyzeVariableSizedImageTable();
	int ExtractWPCAddrAndPageOfImageTable(int *pAddr, int *pPage, int TableIndex);
	int GetROMAddressOfVariableSizedImageIndex(unsigned long *pRomAddr, int TableIndex, int ImageIndex);
	int GetROMAddressOfVariableSizedImageTable(unsigned long *pRomAddr, int TableIndex);
	int GetAddrToWPCAddressOfVariableSizedImageTable(unsigned long *pAddr, int TableIndex);
	int GetVariableSizedImageTableMetadata(int TableIndex, int *pTableHeight, int *pTableSpacing);
	int GetPrevImageIndex(int *pImageIndex, int TableIndex);
	int GetNextImageIndex(int *pImageIndex, int TableIndex);
	int GetFirstImageIndex(int *pImageIndex, int TableIndex);
	int GetLastImageIndex(int *pImageIndex, int TableIndex);
	int IncrementVariableSizedImageIndex(int *pTableIndex, int *pImageIndex);
	int DecrementVariableSizedImageIndex(int *pTableIndex, int *pImageIndex);

	void DecodeVariableSizedImageData();
	void DecodeVariableSizedImageIndexToPlane(int TableIndex, int ImageIndex, DMDPlanes *pPlanes);


// Dialog Data
	//{{AFX_DATA(DMD)
	enum { IDD = IDD_DMD };
	CButton	m_Wipe;
	CButton	m_PreviousGraphicX2;
	CButton	m_NextGraphicX2;
	CStatic	m_Dmd3Title;
	CStatic	m_Dmd2Title;
	CStatic	m_Dmd1Title;
	CSpinButtonCtrl	m_Spin;
	CListBox	m_PixelColor;
	CButton	m_Xored;
	CButton	m_Skipped;
	CStatic	m_Dmd1;
	CStatic	m_Dmd2;
	CStatic	m_Dmd3;
	CButton	m_NextGraphic;
	CButton	m_PreviousGraphic;
	CStatic	m_UserReg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DMD)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	RegistrySettings *PassedInPointer;
//    CBrush* m_pListBkBrush;
#if ALLOW_MOUSE_TO_REPEAT
	int TimerIDDMD;
	unsigned int NextDebounce;
	unsigned int PreviousDebounce;
	unsigned char NextDebounceState;
	unsigned char PreviousDebounceState;
#endif
	unsigned char NaggedOnce;
//	unsigned char NextPressed;
//	unsigned char PreviousPressed;
	// Generated message map functions
	//{{AFX_MSG(DMD)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonNextGraphic();
	afx_msg void OnButtonPreviousGraphic();
	afx_msg void OnCheckSkipped();
	afx_msg void OnCheckXored();
	afx_msg void OnSelchangeList1();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonNextGraphicx2();
	afx_msg void OnButtonPreviousGraphicx2();
	afx_msg void OnButtonWipe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMD_H__0169C360_5BDA_499F_89BA_3FE7FCB29D09__INCLUDED_)
