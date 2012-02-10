#if !defined(AFX_SKINDIALOG1_H__94C22A81_FEEF_11D6_B343_E21BE38D1948__INCLUDED_)
#define AFX_SKINDIALOG1_H__94C22A81_FEEF_11D6_B343_E21BE38D1948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinDialog1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkinDialog dialog

class CSkinDialog : public CDialog
{
// Construction
public:
	CSkinDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinDialog)
	enum { IDD = IDD_SKINDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSkinDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINDIALOG1_H__94C22A81_FEEF_11D6_B343_E21BE38D1948__INCLUDED_)
