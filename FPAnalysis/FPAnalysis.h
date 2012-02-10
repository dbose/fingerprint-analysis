// FPAnalysis.h : main header file for the FPANALYSIS application
//

#if !defined(AFX_FPANALYSIS_H__CEF34405_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
#define AFX_FPANALYSIS_H__CEF34405_BAE3_11D6_AF70_C559F9C10445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "SkinDialog1.h"    //Activeskin support
//#include "AgentDlg.h"       //MS Agent support
//#include "MSAgent2.h"       //MS Agent helper
/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisApp:
// See FPAnalysis.cpp for the implementation of this class
//

class CFPAnalysisApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CFPAnalysisApp();

	//CSkinDialog m_dlgSkin;    // A helper SkinDialog
    //CComQIPtr<ISkin> m_pSkin; // A reference to the ActiveSkin's Skin component, 
	                          // that is contained in SkinDialog

	//CAgentDlg m_dlgAgent;     // A MSAgent host dialog

	//CMSAgent  m_theAgent;     // MS Agent helper class

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFPAnalysisApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFPAnalysisApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CFPAnalysisApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FPANALYSIS_H__CEF34405_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
