// Dialogs.h : header file
// CG: This file was added by the Progress Dialog component

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

#ifndef __DIALOGS_H__
#define __DIALOGS_H__

class CProgressDlg : public CDialog
{
// Construction / Destruction
public:
	void SetDialogCaption(CString szCaption);
    CProgressDlg(CString m_szCaption="");   // standard constructor
    ~CProgressDlg();

    BOOL Create(CWnd *pParent=NULL);

    // Checking for Cancel button
    BOOL CheckCancelButton();
    // Progress Dialog manipulation
    void SetRange(int nLower,int nUpper);
    int  SetStep(int nStep);
    int  SetPos(int nPos);
    int  OffsetPos(int nPos);
    int  StepIt();
        
// Dialog Data
    //{{AFX_DATA(CProgressDlg)
	enum { IDD = CG_IDD_PROGRESS };
    CProgressCtrl	m_Progress;
	CString	m_szCaption;
	//}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CProgressDlg)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    int      m_nLower;
    int      m_nUpper;
    int      m_nStep;
    
    BOOL m_bCancel;
    BOOL m_bParentDisabled;

    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void UpdatePercent(int nCurrent);
    void PumpMessages();

    // Generated message map functions
    //{{AFX_MSG(CProgressDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __DIALOGS_H__
/////////////////////////////////////////////////////////////////////////////
// CConvolutionDlg dialog

class CConvolutionDlg : public CDialog
{
// Construction
public:
	void EnableEditBoxes(BOOL bEnable);
	CConvolutionDlg(CWnd* pParent = NULL);   // standard constructor
	int m_iSel;

// Dialog Data
	//{{AFX_DATA(CConvolutionDlg)
	enum { IDD = IDD_CONVOLUTION };
	CSliderCtrl	m_sctlSharpness;
	CStatic	m_stSharpness;
	CComboBox	m_CBFilter;
	float		m_iPos1;
	float		m_iPos2;
	float		m_iPos3;
	float		m_iPos4;
	float		m_iPos5;
	float   	m_iPos6;
	float		m_iPos7;
	float		m_iPos8;
	float   	m_iPos9;
	float		m_iPos10;
	float		m_iPos11;
	float		m_iPos12;
	float		m_iPos13;
	float		m_iPos14;
	float		m_iPos15;
	float		m_iPos16;
	float		m_iPos17;
	float		m_iPos18;
	float		m_iPos19;
	float		m_iPos20;
	float		m_iPos21;
	float		m_iPos22;
	float		m_iPos23;
	float		m_iPos24;
	float		m_iPos25;
	CString	m_szHelp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvolutionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvolutionDlg)
	afx_msg void OnCloseupComboFilter();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////
// About Dialog

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//CGif	m_Gif;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCredit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg dialog

class CImageInfoDlg : public CDialog
{
// Construction
public:
	CImageInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageInfoDlg)
	enum { IDD = IDD_BITMAPINFO };
	CString	m_height;
	CString	m_width;
	CString	m_bpp;
	CString	m_compression;
	CString	m_imagesize;
	CString	m_colorsused;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////
// CCredits dialog
#define     DISPLAY_TIMER_ID		150		// timer id

class CCredits : public CDialog
{
// Construction
public:
	CCredits(CWnd* pParent = NULL);   // standard constructor

	RECT        m_ScrollRect,r;		   // rect of Static Text frame
	int         nArrIndex,nCounter;	   // work ints
	CString     m_szWork;			   // holds display line
	BOOL        m_bFirstTime;
	BOOL        m_bDrawText;
	int         nClip;
	int         nCurrentFontHeight;

	CWnd*       m_pDisplayFrame;

	CBitmap     m_bmpWork;                  // bitmap holder
	CBitmap* 	pBmpOld;                    // other bitmap work members
	CBitmap*    m_bmpCurrent;
	HBITMAP 	m_hBmpOld;

	CSize 		m_size;                     // drawing helpers
	CPoint 		m_pt;
	BITMAP 		m_bmpInfo;
	CDC 		m_dcMem;
	BOOL 		m_bProcessingBitmap;

// Dialog Data
	//{{AFX_DATA(CCredits)
	enum { IDD = IDD_DISPLAY };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCredits)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCredits)
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
