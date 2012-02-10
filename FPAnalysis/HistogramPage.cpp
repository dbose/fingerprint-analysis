// HistogramPage.cpp : implementation file
//

#include "stdafx.h"
#include "FPAnalysis.h"
#include "HistogramPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramPage property page

IMPLEMENT_DYNCREATE(CHistogramPage, CPropertyPage)

CHistogramPage::CHistogramPage() : CPropertyPage(CHistogramPage::IDD)
{
	//{{AFX_DATA_INIT(CHistogramPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CHistogramPage::~CHistogramPage()
{
}

void CHistogramPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistogramPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistogramPage, CPropertyPage)
	//{{AFX_MSG_MAP(CHistogramPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramPage message handlers

BOOL CHistogramPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	CPropertySheet* pParent = (CPropertySheet*)GetParent();
	pParent->SetWizardButtons(PSWIZB_NEXT);	
	
	return CPropertyPage::OnSetActive();
}
