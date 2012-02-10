#if !defined(AFX_GAUSSIANPAGE_H__210CAD46_C4B5_41FB_B693_55FEAE62A638__INCLUDED_)
#define AFX_GAUSSIANPAGE_H__210CAD46_C4B5_41FB_B693_55FEAE62A638__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GaussianPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGaussianPage dialog

class CGaussianPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGaussianPage)

// Construction
public:
	CGaussianPage();
	~CGaussianPage();

// Dialog Data
	//{{AFX_DATA(CGaussianPage)
	enum { IDD = IDD_WIZP2GAUSSIAN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGaussianPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGaussianPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAUSSIANPAGE_H__210CAD46_C4B5_41FB_B693_55FEAE62A638__INCLUDED_)
