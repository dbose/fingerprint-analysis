// ModelessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FPAnalysis.h"
#include "ModelessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog


CModelessDlg::CModelessDlg()
{
	
}


void CModelessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelessDlg)

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModelessDlg, CDialog)
	//{{AFX_MSG_MAP(CModelessDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg message handlers

void CModelessDlg::OnCancel() 
{
   DestroyWindow();
}

void CModelessDlg::PostNcDestroy() 
{
   delete this;
}
