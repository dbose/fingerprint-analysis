//{{AFX_INCLUDES()
#include "agentctlex1.h"
//}}AFX_INCLUDES
#if !defined(AFX_AGENTDLG_H__0DB07698_439C_470F_81E5_9B5B796DFE91__INCLUDED_)
#define AFX_AGENTDLG_H__0DB07698_439C_470F_81E5_9B5B796DFE91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AgentDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAgentDlg dialog

class CAgentDlg : public CDialog
{
// Construction
public:
	CAgentDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAgentDlg)
	enum { IDD = IDD_AGENT_DIALOG };
	CAgentCtlEx	m_Agent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAgentDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGENTDLG_H__0DB07698_439C_470F_81E5_9B5B796DFE91__INCLUDED_)
