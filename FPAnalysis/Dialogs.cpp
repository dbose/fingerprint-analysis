//  Dialogs.cpp : implementation file
// CG: This file was added by the Progress Dialog component

#include "stdafx.h"
#include "resource.h"
#include "Dialogs.h"

#include "FPAnalysis.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

CProgressDlg::CProgressDlg(CString szCaption)
{
    if (szCaption.IsEmpty()!=TRUE)
		m_szCaption = szCaption;
	else
		m_szCaption="Processing...";

    m_bCancel=FALSE;
    m_nLower=0;
    m_nUpper=100;
    m_nStep=1;
    m_bParentDisabled = FALSE;
}

CProgressDlg::~CProgressDlg()
{
    if(m_hWnd!=NULL)
      DestroyWindow();
}

BOOL CProgressDlg::DestroyWindow()
{
    ReEnableParent();
    return CDialog::DestroyWindow();
}

void CProgressDlg::ReEnableParent()
{
    if(m_bParentDisabled && (m_pParentWnd!=NULL))
      m_pParentWnd->EnableWindow(TRUE);
    m_bParentDisabled=FALSE;
}

BOOL CProgressDlg::Create(CWnd *pParent)
{
    // Get the true parent of the dialog
    m_pParentWnd = CWnd::GetSafeOwner(pParent);

    // m_bParentDisabled is used to re-enable the parent window
    // when the dialog is destroyed. So we don't want to set
    // it to TRUE unless the parent was already enabled.

    if((m_pParentWnd!=NULL) && m_pParentWnd->IsWindowEnabled())
    {
      m_pParentWnd->EnableWindow(FALSE);
      m_bParentDisabled = TRUE;
    }

    if(!CDialog::Create(CProgressDlg::IDD,pParent))
    {
      ReEnableParent();
      return FALSE;
    }

    return TRUE;
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CProgressDlg)
    DDX_Control(pDX, CG_IDC_PROGDLG_PROGRESS, m_Progress);
	DDX_Text(pDX, IDC_CAPTION, m_szCaption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
    //{{AFX_MSG_MAP(CProgressDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CProgressDlg::OnCancel()
{
    m_bCancel=TRUE;
}

void CProgressDlg::SetRange(int nLower,int nUpper)
{
    m_nLower = nLower;
    m_nUpper = nUpper;
    m_Progress.SetRange(nLower,nUpper);
}
  
int CProgressDlg::SetPos(int nPos)
{
    PumpMessages();
    int iResult = m_Progress.SetPos(nPos);
    UpdatePercent(nPos);
    return iResult;
}

int CProgressDlg::SetStep(int nStep)
{
    m_nStep = nStep; // Store for later use in calculating percentage
    return m_Progress.SetStep(nStep);
}

int CProgressDlg::OffsetPos(int nPos)
{
    PumpMessages();
    int iResult = m_Progress.OffsetPos(nPos);
    UpdatePercent(iResult+nPos);
    return iResult;
}

int CProgressDlg::StepIt()
{
    PumpMessages();
    int iResult = m_Progress.StepIt();
    UpdatePercent(iResult+m_nStep);
    return iResult;
}

void CProgressDlg::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}

BOOL CProgressDlg::CheckCancelButton()
{
    // Process all pending messages
    PumpMessages();

    // Reset m_bCancel to FALSE so that
    // CheckCancelButton returns FALSE until the user
    // clicks Cancel again. This will allow you to call
    // CheckCancelButton and still continue the operation.
    // If m_bCancel stayed TRUE, then the next call to
    // CheckCancelButton would always return TRUE

    BOOL bResult = m_bCancel;
    m_bCancel = FALSE;

    return bResult;
}

void CProgressDlg::UpdatePercent(int nNewPos)
{
    CWnd *pWndPercent = GetDlgItem(CG_IDC_PROGDLG_PERCENT);
    int nPercent;
    
    int nDivisor = m_nUpper - m_nLower;
    ASSERT(nDivisor>0);  // m_nLower should be smaller than m_nUpper

    int nDividend = (nNewPos - m_nLower);
    ASSERT(nDividend>=0);   // Current position should be greater than m_nLower

    nPercent = nDividend * 100 / nDivisor;

    // Since the Progress Control wraps, we will wrap the percentage
    // along with it. However, don't reset 100% back to 0%
    if(nPercent!=100)
      nPercent %= 100;

    // Display the percentage
    CString strBuf;
    strBuf.Format(_T("%d%c"),nPercent,_T('%'));

	CString strCur; // get current percentage
    pWndPercent->GetWindowText(strCur);

	if (strCur != strBuf)
		pWndPercent->SetWindowText(strBuf);
}
    
void CProgressDlg::SetDialogCaption(CString szCaption)
{
  m_szCaption=szCaption;
  SetWindowText(m_szCaption);
}
/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

	//theApp.m_pSkin->ApplySkin((long)m_hWnd);

    m_Progress.SetRange(m_nLower,m_nUpper);
    m_Progress.SetStep(m_nStep);
    m_Progress.SetPos(m_nLower);

	SetWindowText(m_szCaption);

    return TRUE;  
}
/////////////////////////////////////////////////////////////////////////////
// CConvolutionDlg dialog


CConvolutionDlg::CConvolutionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvolutionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvolutionDlg)
	m_iPos1 = 0.0;
	m_iPos2 = 0.0;
	m_iPos3 = 0.0;
	m_iPos4 = 0.0;
	m_iPos5 = 0.0;
	m_iPos6 = 0.0;
	m_iPos7 = 0.0;
	m_iPos8 = 0.0;
	m_iPos9 = 0.0;
	m_iPos10 = 0.0;
	m_iPos11 = 0.0;
	m_iPos12 = 0.0;
	m_iPos13 = 0.0;
	m_iPos14 = 0.0;
	m_iPos15 = 0.0;
	m_iPos16 = 0.0;
	m_iPos17 = 0.0;
	m_iPos18 = 0.0;
	m_iPos19 = 0.0;
	m_iPos20 = 0.0;
	m_iPos21 = 0.0;
	m_iPos22 = 0.0;
	m_iPos23 = 0.0;
	m_iPos24 = 0.0;
	m_iPos25 = 0.0;
	m_szHelp = _T("");
	//}}AFX_DATA_INIT
}


void CConvolutionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvolutionDlg)
	DDX_Control(pDX, IDC_SLIDER_SHARP, m_sctlSharpness);
	DDX_Control(pDX, IDC_STATIC_SHARP, m_stSharpness);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_CBFilter);
	DDX_Text(pDX, IDC_EDIT1, m_iPos1);
	DDX_Text(pDX, IDC_EDIT2, m_iPos2);
	DDX_Text(pDX, IDC_EDIT3, m_iPos3);
	DDX_Text(pDX, IDC_EDIT4, m_iPos4);
	DDX_Text(pDX, IDC_EDIT5, m_iPos5);
	DDX_Text(pDX, IDC_EDIT6, m_iPos6);
	DDX_Text(pDX, IDC_EDIT7, m_iPos7);
	DDX_Text(pDX, IDC_EDIT8, m_iPos8);
	DDX_Text(pDX, IDC_EDIT9, m_iPos9);
	DDX_Text(pDX, IDC_EDIT10, m_iPos10);
	DDX_Text(pDX, IDC_EDIT11, m_iPos11);
	DDX_Text(pDX, IDC_EDIT12, m_iPos12);
	DDX_Text(pDX, IDC_EDIT13, m_iPos13);
	DDX_Text(pDX, IDC_EDIT14, m_iPos14);
	DDX_Text(pDX, IDC_EDIT15, m_iPos15);
	DDX_Text(pDX, IDC_EDIT16, m_iPos16);
	DDX_Text(pDX, IDC_EDIT17, m_iPos17);
	DDX_Text(pDX, IDC_EDIT18, m_iPos18);
	DDX_Text(pDX, IDC_EDIT19, m_iPos19);
	DDX_Text(pDX, IDC_EDIT20, m_iPos20);
	DDX_Text(pDX, IDC_EDIT21, m_iPos21);
	DDX_Text(pDX, IDC_EDIT22, m_iPos22);
	DDX_Text(pDX, IDC_EDIT23, m_iPos23);
	DDX_Text(pDX, IDC_EDIT24, m_iPos24);
	DDX_Text(pDX, IDC_EDIT25, m_iPos25);
	DDX_Text(pDX, IDC_EDIT_HELP, m_szHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvolutionDlg, CDialog)
	//{{AFX_MSG_MAP(CConvolutionDlg)
	ON_CBN_CLOSEUP(IDC_COMBO_FILTER, OnCloseupComboFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvolutionDlg member functions::not message handlers
void CConvolutionDlg::EnableEditBoxes(BOOL bEnable)
{
   int IDC_START = 1001;
   for(int k = 1;k <= 25 ; k++)
   {
	  CEdit* pEdit = (CEdit *)this->GetDlgItem(IDC_START + k);
	  ASSERT(pEdit != NULL);
	  pEdit->EnableWindow(bEnable);
   }
}

/////////////////////////////////////////////////////////////////////////////
// CConvolutionDlg message handlers
void CConvolutionDlg::OnCloseupComboFilter() 
{
	int iSharpness;
   	m_iSel=m_CBFilter.GetCurSel();
	if (m_iSel != CB_ERR)
	{
	 switch(m_iSel)
	 {
	  case 0: 
		    EnableEditBoxes(FALSE);
		    // Laplacian
		    m_iPos8 = -1.0;
	        m_iPos12 = -1.0;
	        m_iPos13 = 4.0;
	        m_iPos14 = -1.0;
	        m_iPos18 = -1.0;
            
			m_szHelp = "Laplacian Operator after the name of mathematical 'nabla square' fuction.Generally used to detect intensity variation along the edges";


			break;
	  case 1: 
		    EnableEditBoxes(FALSE); 
		    // Sobel
		    m_iPos7 = 1.0;
	        m_iPos8 = 2.0;
	        m_iPos9 = 1.0;
	        m_iPos12 = 0.0;
	        m_iPos13 = 0.0;
	        m_iPos14 = 0.0;
		    m_iPos17 = -1.0;
	        m_iPos18 = -2.0;
	        m_iPos19 = -1.0;
			break;
	  case 2: 
		    EnableEditBoxes(FALSE);
		    // Roberts
		    m_iPos7 = 0.0;
	        m_iPos8 = 0.0;
	        m_iPos9 = 0.0;
	        m_iPos12 = 0.0;
	        m_iPos13 = 1.0;
	        m_iPos14 = 0.0;
		    m_iPos17 = 0.0;
	        m_iPos18 = 0.0;
	        m_iPos19 = -1.0;
			break;
	  case 3: 
		    EnableEditBoxes(FALSE);
		    // Isotropic
		    m_iPos7 = -1.0;
	        m_iPos8 = 0.0;
	        m_iPos9 = 1.0;
	        m_iPos12 = -1.414;
	        m_iPos13 = 0.0;
	        m_iPos14 = 1.414;
		    m_iPos17 = -1.0;
	        m_iPos18 = 0.0;
	        m_iPos19 = 1.0;
			break;
	  case 4: 
		    EnableEditBoxes(FALSE);
		    // Prewitt
		    m_iPos7 = -1.0;
	        m_iPos8 = 0.0;
	        m_iPos9 = 1.0;
	        m_iPos12 = -1.0;
	        m_iPos13 = 0.0;
	        m_iPos14 = 1.0;
		    m_iPos17 = -1.0;
	        m_iPos18 = 0.0;
	        m_iPos19 = 1.0;
			break;
	  case 5: 
		    EnableEditBoxes(FALSE);
		    // Kirsch
		    m_iPos7 = 5.0;
	        m_iPos8 = 5.0;
	        m_iPos9 = 5.0;
	        m_iPos12 = -3.0;
	        m_iPos13 = 0.0;
	        m_iPos14 = -3.0;
		    m_iPos17 = -3.0;
	        m_iPos18 = -3.0;
	        m_iPos19 = -3.0;
			break;
	  case 6: 
		    EnableEditBoxes(FALSE);
		    // Stochastic(SNR = 1)
		    m_iPos7 = 0.97;
	        m_iPos8 = 0.0;
	        m_iPos9 = -0.97;
	        m_iPos12 = 1.0;
	        m_iPos13 = 0.0;
	        m_iPos14 = -1.0;
		    m_iPos17 = 0.97;
	        m_iPos18 = 0.0;
	        m_iPos19 = -0.97;
			break;
	  case 7: 
		    EnableEditBoxes(FALSE);
		    // Pyramidal
		    m_iPos1 = 1.0;
	        m_iPos2 = 2.0;
	        m_iPos3 = 3.0;
	        m_iPos4 = 2.0;
	        m_iPos5 = 1.0;

	        m_iPos6 = 2.0;
	        m_iPos7 = 4.0;
	        m_iPos8 = 6.0;
	        m_iPos9 = 4.0;
	        m_iPos10 = 2.0;

	        m_iPos11 = 3.0;
	        m_iPos12 = 6.0;
	        m_iPos13 = 9.0;
	        m_iPos14 = 6.0;
	        m_iPos15 = 3.0;

	        m_iPos16 = 2.0;
	        m_iPos17 = 4.0;
	        m_iPos18 = 6.0;
	        m_iPos19 = 4.0;
	        m_iPos20 = 2.0;

	        m_iPos21 = 1.0;
	        m_iPos22 = 2.0;
	        m_iPos23 = 3.0;
	        m_iPos24 = 2.0;
	        m_iPos25 = 1.0;
			break;
	  case 8: 
		    EnableEditBoxes(FALSE);
		    // Cone
		    m_iPos1 = 0.0;
	        m_iPos2 = 0.0;
	        m_iPos3 = 1.0;
	        m_iPos4 = 0.0;
	        m_iPos5 = 0.0;

	        m_iPos6 = 0.0;
	        m_iPos7 = 2.0;
	        m_iPos8 = 2.0;
	        m_iPos9 = 2.0;
	        m_iPos10 = 0.0;

        	m_iPos11 = 1.0;
	        m_iPos12 = 2.0;
	        m_iPos13 = 5.0;
	        m_iPos14 = 2.0;
	        m_iPos15 = 1.0;

	        m_iPos16 = 0.0;
	        m_iPos17 = 2.0;
	        m_iPos18 = 2.0;
	        m_iPos19 = 2.0;
	        m_iPos20 = 0.0;

	        m_iPos21 = 0.0;
	        m_iPos22 = 0.0;
	        m_iPos23 = 1.0;
	        m_iPos24 = 0.0;
	        m_iPos25 = 0.0;
			break;
	  case 9:
            EnableEditBoxes(FALSE);
		    
		    m_iPos1 = 2.0/115;
	        m_iPos2 = 4.0/115;
	        m_iPos3 = 5.0/115;
	        m_iPos4 = 4.0/115;
	        m_iPos5 = 2.0/115;

	        m_iPos6 = 4.0/115;
	        m_iPos7 = 9.0/115;
	        m_iPos8 = 12.0/115;
	        m_iPos9 = 9.0/115;
	        m_iPos10 = 4.0/115;

        	m_iPos11 = 5.0/115;
	        m_iPos12 = 12.0/115;
	        m_iPos13 = 15.0/115;
	        m_iPos14 = 12.0/115;
	        m_iPos15 = 5.0/115;

	        m_iPos16 = 4.0/115;
	        m_iPos17 = 9.0/115;
	        m_iPos18 = 12.0/115;
	        m_iPos19 = 9.0/115;
	        m_iPos20 = 4.0/115;

	        m_iPos21 = 2.0/115;
	        m_iPos22 = 4.0/115;
	        m_iPos23 = 5.0/115;
	        m_iPos24 = 4.0/115;
	        m_iPos25 = 2.0/115;
			break;
	  case 10:

		    EnableEditBoxes(FALSE);

		    m_stSharpness.ShowWindow(SW_SHOW);
	        m_sctlSharpness.ShowWindow(SW_SHOW);

			// fetch sharpness amount needed for crispening...
			UpdateData(TRUE);
            iSharpness = m_sctlSharpness.GetPos();
			if (iSharpness == 0)
				iSharpness = 1;

			m_iPos8 = -1.0;
	        m_iPos12 = -1.0;
	        m_iPos13 = 4.0 + (float)iSharpness;
	        m_iPos14 = -1.0;
	        m_iPos18 = -1.0;

			break;

	  case 11:
		   
		  //Enable all the edit boxes
		  EnableEditBoxes(TRUE);
		  break;

       }
	 }

	//DDX update
	UpdateData(FALSE);

}

//////////////////About Dialog///////////////////////////////////
BOOL CConvolutionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//Install the skin
	//theApp.m_pSkin->ApplySkin((long)m_hWnd);
	
	//Show MSAgent
	//theApp.m_theAgent.Show();
	//theApp.m_theAgent.Speak("May i help you ?");

    m_stSharpness.ShowWindow(SW_HIDE);
	m_sctlSharpness.SetRange(0,10);
	m_sctlSharpness.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_CREDIT, OnCredit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Install the skin
	//theApp.m_pSkin->ApplySkin((long)m_hWnd);

    

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnCredit() 
{
  	CCredits dlgCredit;
	dlgCredit.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg dialog


CImageInfoDlg::CImageInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageInfoDlg)
	m_height = _T("");
	m_width = _T("");
	m_bpp = _T("");
	m_compression = _T("");
	m_imagesize = _T("");
	m_colorsused = _T("");
	//}}AFX_DATA_INIT
}


void CImageInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageInfoDlg)
	DDX_Text(pDX, IDC_HEIGHT, m_height);
	DDX_Text(pDX, IDC_WIDTH, m_width);
	DDX_Text(pDX, IDC_BPP, m_bpp);
	DDX_Text(pDX, IDC_COMPRESSION, m_compression);
	DDX_Text(pDX, IDC_IMAGESIZE, m_imagesize);
	DDX_Text(pDX, IDC_COLORSUSED, m_colorsused);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CImageInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageInfoDlg message handlers
BOOL CImageInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    //Install the skin
	//theApp.m_pSkin->ApplySkin((long)m_hWnd);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




////////////////////////////////////////////////////////////////////////////
// CCredits dialog

#define SCROLLAMOUNT				-1
#define DISPLAY_SLOW				70
#define DISPLAY_MEDIUM				40
#define DISPLAY_FAST				10
#define DISPLAY_SPEED				DISPLAY_MEDIUM

#define RED						RGB(255,0,0)
#define GREEN					RGB(0,255,0)
#define BLUE					RGB(0,0,255)
#define WHITE   				RGB(255,255,255)
#define YELLOW  				RGB(255,255,0)
#define TURQUOISE 				RGB(0,255,255)
#define PURPLE  				RGB(255,0,255)
#define BLACK       			RGB(0,0,0)

#define BACKGROUND_COLOR        BLACK
#define TOP_LEVEL_TITLE_COLOR	RED
#define TOP_LEVEL_GROUP_COLOR   YELLOW
#define GROUP_TITLE_COLOR       TURQUOISE
#define NORMAL_TEXT_COLOR		WHITE

// You can set font heights here to suit your taste
#define TOP_LEVEL_TITLE_HEIGHT	21		
#define TOP_LEVEL_GROUP_HEIGHT  19     
#define GROUP_TITLE_HEIGHT    	17     
#define	NORMAL_TEXT_HEIGHT		15



// these define the escape sequences to suffix each array line with. They
// are listed in order of descending font size.
#define TOP_LEVEL_TITLE			'\n'
#define TOP_LEVEL_GROUP         '\r'
#define GROUP_TITLE           	'\t'
#define NORMAL_TEXT				'\f' 
#define DISPLAY_BITMAP			'\b'

// Enter the text and bitmap resource string identifiers which are to
// appear in the scrolling list. Append each non-empty string entry with
// an escape character corresponding to the desired font effect. Empty
// strings do not get a font assignment.
// (see #defines above)
// 
// Array count. Make sure this keeps up with how many lines there are
// in the array!
#define ARRAYCOUNT		48
char *pArrCredit[] = { 	"Fingerprint Analysis 1.00 \n",
						"",
						"Final Year Project \f",
						"Electronics & Instrumentation Engineering \f",
						"University Science Instrumentation Centre \f",
						"University Of Kalyani,West Bengal \f",
						"",
						"",
						"Project Leader \t",
						"Project Concept & Designing , Debugging\t",
						"",
						"Debasish Bose \f",
						"",
						"",
						"Product Guide & Advice \t",
						"",
						"Mr. Susanta Biswas \f",
						"",
						"",
						"Project Resources & References \t",
						"",
						"Anil Kumar Jain's research paper(s) \f",
						"and Digital Image Processing book \f",
						"",
						"",
						"Fingerprint Analysis Technique used \t",
						"",
						"Minutiae Analysis \f",
						"",
						"",
					    "",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						"",
						};

/////////////////////////////////////////////////////////////////////////////
// CCredits dialog


CCredits::CCredits(CWnd* pParent /*=NULL*/)
	: CDialog(CCredits::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCredits)
	//}}AFX_DATA_INIT
}


void CCredits::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCredits)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCredits, CDialog)
	//{{AFX_MSG_MAP(CCredits)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCredits message handlers

void CCredits::OnOK() 
{
	KillTimer(DISPLAY_TIMER_ID);
	
	CDialog::OnOK();
}

//************************************************************************
//	 InitDialog
//
//	 	Setup the display rect and start the timer.
//************************************************************************
BOOL CCredits::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//Install the skin
	//theApp.m_pSkin->ApplySkin((long)m_hWnd);

	BOOL bRet;
    	UINT nRet;
	
	nCurrentFontHeight = NORMAL_TEXT_HEIGHT;
	
	CClientDC dc(this);
	bRet = m_dcMem.CreateCompatibleDC(&dc);
	
	
	m_bProcessingBitmap=FALSE;
	
	nArrIndex=0;
	nCounter=1;
	nClip=0;
	m_bFirstTime=TRUE;
	m_bDrawText=FALSE;
	m_hBmpOld = 0;
	
	m_pDisplayFrame=(CWnd*)GetDlgItem(IDC_DISPLAY_STATIC);	

	// If you assert here, you did not assign your static display control
	// the IDC_ value that was used in the GetDlgItem(...). This is the
    // control that will display the credits.
	_ASSERTE(m_pDisplayFrame);
				 
	m_pDisplayFrame->GetClientRect(&m_ScrollRect);


	nRet = SetTimer(DISPLAY_TIMER_ID,DISPLAY_SPEED,NULL);
    _ASSERTE(nRet != 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//************************************************************************
//	 OnTimer
//
//	 	On each of the display timers, scroll the window 1 unit. Each 20
//      units, fetch the next array element and load into work string. Call
//      Invalidate and UpdateWindow to invoke the OnPaint which will paint 
//      the contents of the newly updated work string.
//************************************************************************
void CCredits::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent != DISPLAY_TIMER_ID)
		{
		CDialog::OnTimer(nIDEvent);
		return;
		}

	if (!m_bProcessingBitmap)
	if (nCounter++ % nCurrentFontHeight == 0)	 // every x timer events, show new line
		{
		nCounter=1;
		m_szWork = pArrCredit[nArrIndex++];
		
		if (nArrIndex > ARRAYCOUNT-1)
			nArrIndex=0;
		nClip = 0;
		m_bDrawText=TRUE;
		}
	
	m_pDisplayFrame->ScrollWindow(0,SCROLLAMOUNT,&m_ScrollRect,&m_ScrollRect);
	nClip = nClip + abs(SCROLLAMOUNT);	
	
    CRect r;
    CWnd* pWnd = GetDlgItem(IDC_DISPLAY_STATIC);
    ASSERT_VALID(pWnd);
    pWnd->GetClientRect(&r);
    pWnd->ClientToScreen(r);
    ScreenToClient(&r);
    InvalidateRect(r,FALSE); // FALSE does not erase background

	CDialog::OnTimer(nIDEvent);
}


//************************************************************************
//	 OnPaint
//
//	 	Send the newly updated work string to the display rect.
//************************************************************************
void CCredits::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	PAINTSTRUCT ps;
	CDC* pDc = m_pDisplayFrame->BeginPaint(&ps);
	
	pDc->SetBkMode(TRANSPARENT);


	//*********************************************************************
	//	FONT SELECTION
    CFont m_fntArial;
	CFont* pOldFont;
	BOOL bSuccess;
	
	BOOL bUnderline;
	BOOL bItalic;


	if (!m_szWork.IsEmpty())
	switch (m_szWork[m_szWork.GetLength()-1] )
	{
		case NORMAL_TEXT:
		default:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = NORMAL_TEXT_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(NORMAL_TEXT_HEIGHT, 0, 0, 0, 
   								FW_THIN, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"Arial");
			pDc->SetTextColor(NORMAL_TEXT_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;

		case TOP_LEVEL_GROUP:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = TOP_LEVEL_GROUP_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(TOP_LEVEL_GROUP_HEIGHT, 0, 0, 0, 
   								FW_BOLD, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"Arial");
			pDc->SetTextColor(TOP_LEVEL_GROUP_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		
		
		case GROUP_TITLE:
			bItalic = FALSE;
			bUnderline = FALSE;
			nCurrentFontHeight = GROUP_TITLE_HEIGHT;
   			bSuccess = m_fntArial.CreateFont(GROUP_TITLE_HEIGHT, 0, 0, 0, 
   								FW_BOLD, bItalic, bUnderline, 0, 
   								ANSI_CHARSET,
                               	OUT_DEFAULT_PRECIS,
                               	CLIP_DEFAULT_PRECIS,
                               	PROOF_QUALITY,
                               	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
                               	(LPSTR)"Arial");
			pDc->SetTextColor(GROUP_TITLE_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		
		case TOP_LEVEL_TITLE:
			bItalic = FALSE;
			bUnderline = TRUE;
			nCurrentFontHeight = TOP_LEVEL_TITLE_HEIGHT;
			bSuccess = m_fntArial.CreateFont(TOP_LEVEL_TITLE_HEIGHT, 0, 0, 0, 
								FW_BOLD, bItalic, bUnderline, 0, 
								ANSI_CHARSET,
	                           	OUT_DEFAULT_PRECIS,
	                           	CLIP_DEFAULT_PRECIS,
	                           	PROOF_QUALITY,
	                           	VARIABLE_PITCH | 0x04 | FF_DONTCARE,
	                           	(LPSTR)"Arial");
			pDc->SetTextColor(TOP_LEVEL_TITLE_COLOR);
			pOldFont  = pDc->SelectObject(&m_fntArial);
			break;
		
		case DISPLAY_BITMAP:
			if (!m_bProcessingBitmap)
			{
				CString szBitmap = m_szWork.Left(m_szWork.GetLength()-1);
	   			if (!m_bmpWork.LoadBitmap((const char *)szBitmap))
				{
					CString str; 
					str.Format("Could not find bitmap resource \"%s\". "
                               "Be sure to assign the bitmap a QUOTED resource name", szBitmap); 
					KillTimer(DISPLAY_TIMER_ID); 
					AfxMessageBox(str); 
					return; 
				}
				m_bmpCurrent = &m_bmpWork;
	   			m_bmpCurrent->GetObject(sizeof(BITMAP), &m_bmpInfo);
			
				m_size.cx = m_bmpInfo.bmWidth;	// width  of dest rect
				RECT workRect;
				m_pDisplayFrame->GetClientRect(&workRect);
				m_pDisplayFrame->ClientToScreen(&workRect);
				ScreenToClient(&workRect);
				// upper left point of dest
				m_pt.x = (workRect.right - 
							((workRect.right-workRect.left)/2) - (m_bmpInfo.bmWidth/2));
				m_pt.y = workRect.bottom;
				
				
				pBmpOld = m_dcMem.SelectObject(m_bmpCurrent);
				if (m_hBmpOld == 0)
					m_hBmpOld = (HBITMAP) pBmpOld->GetSafeHandle();
				m_bProcessingBitmap = TRUE;
			}
			break;

		}
	
	
	
	
	CBrush bBrush(BLACK);
	CBrush* pOldBrush;
	pOldBrush  = pDc->SelectObject(&bBrush);
	// Only fill rect comprised of gap left by bottom of scrolling window
	r=m_ScrollRect;
	r.top = r.bottom-abs(SCROLLAMOUNT); 
	pDc->DPtoLP(&r);
	
	if (m_bFirstTime)
	{
		m_bFirstTime=FALSE;
		pDc->FillRect(&m_ScrollRect,&bBrush);
	}
	else
		pDc->FillRect(&r,&bBrush);
	
	r=m_ScrollRect;
	r.top = r.bottom-nClip;
	
	
	if (!m_bProcessingBitmap)
	{
		int x = pDc->DrawText((const char *)m_szWork,m_szWork.GetLength()-1,&r,DT_TOP|DT_CENTER|
					DT_NOPREFIX | DT_SINGLELINE);	
		m_bDrawText=FALSE;
	}
	else
	{
    	dc.StretchBlt( m_pt.x, m_pt.y-nClip, m_size.cx, nClip, 
                   		&m_dcMem, 0, 0, m_bmpInfo.bmWidth-1, nClip,
                   		SRCCOPY );
		if (nClip > m_bmpInfo.bmHeight)
		{
			m_bmpWork.DeleteObject();
			m_bProcessingBitmap = FALSE;
			nClip=0;
			m_szWork.Empty();
			nCounter=1;
		}
		pDc->SelectObject(pOldBrush);
		bBrush.DeleteObject();
		m_pDisplayFrame->EndPaint(&ps);
		return;
	}
	
	
	pDc->SelectObject(pOldBrush);
	bBrush.DeleteObject();
	
	if (!m_szWork.IsEmpty())
	{
		pDc->SelectObject(pOldFont);
		m_fntArial.DeleteObject();
	}

	m_pDisplayFrame->EndPaint(&ps);
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CCredits::OnDestroy() 
{
	CDialog::OnDestroy();
	
    m_dcMem.SelectObject(CBitmap::FromHandle(m_hBmpOld));
    m_bmpWork.DeleteObject();
	
}




