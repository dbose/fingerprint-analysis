// GaussianPage.cpp : implementation file
//

#include "stdafx.h"
#include "FPAnalysis.h"
#include "GaussianPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGaussianPage property page

IMPLEMENT_DYNCREATE(CGaussianPage, CPropertyPage)

CGaussianPage::CGaussianPage() : CPropertyPage(CGaussianPage::IDD)
{
	//{{AFX_DATA_INIT(CGaussianPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CGaussianPage::~CGaussianPage()
{
}

void CGaussianPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGaussianPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGaussianPage, CPropertyPage)
	//{{AFX_MSG_MAP(CGaussianPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGaussianPage message handlers

BOOL CGaussianPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
    CPropertySheet* pParent = (CPropertySheet*)GetParent();
	pParent->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);	

	return CPropertyPage::OnSetActive();
}
