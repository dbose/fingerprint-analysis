// AgentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FPAnalysis.h"
#include "AgentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgentDlg dialog


CAgentDlg::CAgentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAgentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAgentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgentDlg)
	DDX_Control(pDX, IDC_CONTROL1, m_Agent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgentDlg, CDialog)
	//{{AFX_MSG_MAP(CAgentDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgentDlg message handlers
