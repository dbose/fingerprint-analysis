// ScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FPAnalysis.h"
#include "ScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog


CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanDlg)
	DDX_Control(pDX, IDC_FINGERPRINTSCAN, m_ImgScan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
	ON_BN_CLICKED(IDC_SELECTSCANNER, OnSelectscanner)
	ON_BN_CLICKED(IDC_STARTSCANNER, OnStartscanner)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDlg message handlers

void CScanDlg::OnSelectscanner() 
{
   
   m_ImgScan.ShowSelectScanner();	

}

void CScanDlg::OnStartscanner() 
{
   if (m_szImageName.IsEmpty())
	   AfxMessageBox("Please select a file name where scanned image will be dumped",MB_OK|MB_ICONSTOP);
   else
   {
	   m_ImgScan.StartScan();
   }	
}


void CScanDlg::OnBrowse() 
{
  CString szFileName;
  CString sFilter="BMP (*.bmp)|*.bmp|All files (*.*)|*.*||";
  
  CFileDialog dlg(
		FALSE,				// Create an open file dialog
		"*.BMP",			// Default file extension
		NULL,				// Filename
		OFN_HIDEREADONLY |	// Flags - don't show the read only check box)
		OFN_FILEMUSTEXIST,	//       - make sure file exists
		sFilter);				// the file filter

  //set the title
  dlg.m_ofn.lpstrTitle = "Specify a BMP file to store the scanned image...";  

  if (dlg.DoModal()==IDOK)
      szFileName = dlg.GetPathName();
	
  //Get the full pathname
  m_szImageName = szFileName;
  
  //Display the filename
  CWnd* pImagePath = GetDlgItem(IDC_IMAGEPATH);
  pImagePath->SetWindowText((LPCTSTR)m_szImageName);

  //Set display(preview) & file mode
  m_ImgScan.SetScanTo(1);

  //Set the filename so that ImgScan control can dump to it
  m_ImgScan.SetImage(m_szImageName);	
}

/*
  Now the question is from CView derived class how could we know that :: scanning 
  is done ? So, ImgScan control provide an event - "ScanDone" which will be fired
  as soon as image is scanned completely.Simply write an handler of that event using
  DevStudio's Event Wizard and you have it.For communication with my view class i
  initially disabled the OK button and inside the "ScanDone" event-handler i enabled
  it so that in my view class 
             
			   if (dlg.DoModal() == IDOK)
			   {
			     
				  //...

               } 
  code between the curly braces is executed as soon as scanning is over and user
  clicks OK button.Little tricky !

*/

BEGIN_EVENTSINK_MAP(CScanDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CScanDlg)
	ON_EVENT(CScanDlg, IDC_FINGERPRINTSCAN, 2 /* ScanDone */, OnScanDoneFingerprintscan, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CScanDlg::OnScanDoneFingerprintscan() 
{
   CWnd* pOK = GetDlgItem(IDOK);
   pOK->EnableWindow(TRUE);	
}

BOOL CScanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    //Install the skin
	//theApp.m_pSkin->ApplySkin((long)m_hWnd);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
