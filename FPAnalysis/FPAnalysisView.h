// FPAnalysisView.h : interface of the CFPAnalysisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FPANALYSISVIEW_H__CEF3440F_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
#define AFX_FPANALYSISVIEW_H__CEF3440F_BAE3_11D6_AF70_C559F9C10445__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFPAnalysisView : public CScrollView
{
protected: // create from serialization only
	CFPAnalysisView();
	DECLARE_DYNCREATE(CFPAnalysisView)

// Attributes
public:
	CFPAnalysisDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFPAnalysisView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CImage   currentimage;				// current image displayed
    	
	// helper functions
	void SetFPScrollInfo();
	BOOL GetColorAndPositionAtCursor(COLORREF& cr,CPoint& pt);

	virtual ~CFPAnalysisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

   int      m_nNum;           // numerator of zoom factor
   int      m_nDen;           // denominator ditto
   

// Generated message map functions
protected:
	//{{AFX_MSG(CFPAnalysisView)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileScan();
	afx_msg void OnViewGray();
	afx_msg void OnEditUndo();
	afx_msg void OnViewBinary();
	afx_msg void OnViewNegative();
	afx_msg void OnViewConvolve();
	afx_msg void OnViewEdge();
	afx_msg void OnViewEqualize();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnWindowZoomin();
	afx_msg void OnWindowZoomout();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewBlurr();
	afx_msg void OnViewNormalize();
	afx_msg void OnViewOrientation();
	afx_msg void OnViewThinning();
	afx_msg void OnViewAdaptivebinarize();
	afx_msg void OnHelpAbout();
	afx_msg void OnViewExtraction();
	afx_msg void OnViewDocumentinfo();
	afx_msg void OnViewRoi();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEditData();
	afx_msg void OnViewSegmentation();
	afx_msg void OnViewCore();
	afx_msg void OnWindowFit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnViewWizard();
	afx_msg void OnActionRegionofinterest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFilterAfterMinutiaeExtraction();
};

#ifndef _DEBUG  // debug version in FPAnalysisView.cpp
inline CFPAnalysisDoc* CFPAnalysisView::GetDocument()
   { return (CFPAnalysisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FPANALYSISVIEW_H__CEF3440F_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
