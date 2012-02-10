// FPAnalysisDoc.h : interface of the CFPAnalysisDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FPANALYSISDOC_H__CEF3440D_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
#define AFX_FPANALYSISDOC_H__CEF3440D_BAE3_11D6_AF70_C559F9C10445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFPAnalysisDoc : public CDocument
{
protected: // create from serialization only
	CFPAnalysisDoc();
	DECLARE_DYNCREATE(CFPAnalysisDoc)

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFPAnalysisDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFPAnalysisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFPAnalysisDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FPANALYSISDOC_H__CEF3440D_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
