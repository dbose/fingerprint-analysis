//{{AFX_INCLUDES()
#include "imgscan.h"
//}}AFX_INCLUDES
#if !defined(AFX_SCANDLG_H__0204AC71_65B2_463E_B579_8AADB430EB00__INCLUDED_)
#define AFX_SCANDLG_H__0204AC71_65B2_463E_B579_8AADB430EB00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanDlg.h : header file
//
#include "imgscan.h"
/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog

class CScanDlg : public CDialog
{
// Construction
public:
	CScanDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_szImageName;
// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_SCAN };
	CImgScan	m_ImgScan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanDlg)
	afx_msg void OnSelectscanner();
	afx_msg void OnStartscanner();
	afx_msg void OnBrowse();
	afx_msg void OnScanDoneFingerprintscan();
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANDLG_H__0204AC71_65B2_463E_B579_8AADB430EB00__INCLUDED_)
