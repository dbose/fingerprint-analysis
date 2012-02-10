//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_MODELESSDLG_H__A2C2C772_EF3F_489C_8345_DAC3FA408DCF__INCLUDED_)
#define AFX_MODELESSDLG_H__A2C2C772_EF3F_489C_8345_DAC3FA408DCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelessDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModelessDlg dialog

class CModelessDlg : public CDialog
{
// Construction
public:
	CModelessDlg();   // standard constructor
    BOOL Create(UINT nID, CWnd * pWnd)
    { 
		return CDialog::Create(nID,pWnd);
	}
// Dialog Data
	//{{AFX_DATA(CModelessDlg)
	enum { IDD = IDD_DUMMY };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModelessDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESSDLG_H__A2C2C772_EF3F_489C_8345_DAC3FA408DCF__INCLUDED_)
