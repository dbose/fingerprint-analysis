#if !defined(AFX_HISTOGRAMPAGE_H__27E7199A_1FA5_46A5_B623_2A3736F75600__INCLUDED_)
#define AFX_HISTOGRAMPAGE_H__27E7199A_1FA5_46A5_B623_2A3736F75600__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramPage dialog

class CHistogramPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CHistogramPage)

// Construction
public:
	CHistogramPage();
	~CHistogramPage();

// Dialog Data
	//{{AFX_DATA(CHistogramPage)
	enum { IDD = IDD_WIZP1HISTOGRAM };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHistogramPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHistogramPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMPAGE_H__27E7199A_1FA5_46A5_B623_2A3736F75600__INCLUDED_)
