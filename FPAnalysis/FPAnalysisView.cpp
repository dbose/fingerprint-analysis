// FPAnalysisView.cpp : implementation of the CFPAnalysisView class
//

#include "stdafx.h"
#include "FPAnalysis.h"

#include "FPAnalysisDoc.h"
#include "FPAnalysisView.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#include "dialogs.h"
#include "ScanDlg.h"  //Scan Dialog :: Deliberately seperated from "dialogs.h"
#include "EditDlg.h"  //Finger data edit dialog


//Wizard headers
#include "GaussianPage.h"
#include "HistogramPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView

IMPLEMENT_DYNCREATE(CFPAnalysisView, CScrollView)

BEGIN_MESSAGE_MAP(CFPAnalysisView, CScrollView)
	//{{AFX_MSG_MAP(CFPAnalysisView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SCAN, OnFileScan)
	ON_COMMAND(ID_VIEW_GRAY, OnViewGray)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_VIEW_BINARY, OnViewBinary)
	ON_COMMAND(ID_VIEW_NEGATIVE, OnViewNegative)
	ON_COMMAND(ID_VIEW_CONVOLVE, OnViewConvolve)
	ON_COMMAND(ID_VIEW_EDGE, OnViewEdge)
	ON_COMMAND(ID_VIEW_EQUALIZE, OnViewEqualize)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_WINDOW_ZOOMIN, OnWindowZoomin)
	ON_COMMAND(ID_WINDOW_ZOOMOUT, OnWindowZoomout)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_VIEW_BLURR, OnViewBlurr)
	ON_COMMAND(ID_VIEW_NORMALIZE, OnViewNormalize)
	ON_COMMAND(ID_VIEW_ORIENTATION, OnViewOrientation)
	ON_COMMAND(ID_VIEW_THINNING, OnViewThinning)
	ON_COMMAND(ID_VIEW_ADAPTIVEBINARIZE, OnViewAdaptivebinarize)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_VIEW_EXTRACTION, OnViewExtraction)
	ON_COMMAND(ID_VIEW_DOCUMENTINFO, OnViewDocumentinfo)
	ON_COMMAND(ID_VIEW_ROI, OnViewRoi)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_EDIT_DATA, OnEditData)
	ON_COMMAND(ID_VIEW_SEGMENTATION, OnViewSegmentation)
	ON_COMMAND(ID_VIEW_CORE, OnViewCore)
	ON_COMMAND(ID_WINDOW_FIT, OnWindowFit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_VIEW_WIZARD, OnViewWizard)
	ON_COMMAND(ID_ACTION_REGIONOFINTEREST, OnActionRegionofinterest)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_ACTION_FILTERAFTERMINUTIAEEXTRACTION, &CFPAnalysisView::OnFilterAfterMinutiaeExtraction)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView construction/destruction

CFPAnalysisView::CFPAnalysisView()
{
	 
	//initialize zoom-specific members
	 m_nNum = m_nDen = 1;
	
}

CFPAnalysisView::~CFPAnalysisView()
{
    
}

BOOL CFPAnalysisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
 
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView drawing

void CFPAnalysisView::OnDraw(CDC* pDC)
{
	CFPAnalysisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClient;
	GetClientRect(&rectClient);
	int left = rectClient.left+ max(1, ((rectClient.Width()  - (int)(currentimage.GetWidth()*m_nNum / m_nDen))  / 2));
	int top  = rectClient.top + max(1, ((rectClient.Height() - (int)(currentimage.GetHeight()*m_nNum / m_nDen)) / 2));
	currentimage.DrawBMP(pDC,left,top,m_nNum,m_nDen);
	//ReleaseDC(pDC);	
}

void CFPAnalysisView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

}

void CFPAnalysisView::SetFPScrollInfo()
{

    CSize sizeTotal(currentimage.GetWidth() * m_nNum / m_nDen, currentimage.GetHeight() * m_nNum / m_nDen) ;
	CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
	CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);

}

BOOL CFPAnalysisView::GetColorAndPositionAtCursor(COLORREF& cr,CPoint& pt)
{
  // fetch the cursor co-ordinate
  POINT point;
  if (!GetCursorPos(&point))
    return FALSE;
  ScreenToClient(&point);

  // check whether cursor is inside scroll area ?
  CSize size = GetTotalSize();
  CRect rect(0, 0, size.cx, size.cy);
  if (!rect.PtInRect(point))
    return FALSE;

  // get the client DC
  CClientDC dc(this);
  cr = dc.GetPixel(pt.x,pt.y);

  return TRUE;

}
/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView printing

BOOL CFPAnalysisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	//p/Info->SetMaxPage(1);

    // default preparation
	return DoPreparePrinting(pInfo);
}

void CFPAnalysisView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	
	
}

void CFPAnalysisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView diagnostics

#ifdef _DEBUG
void CFPAnalysisView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFPAnalysisView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFPAnalysisDoc* CFPAnalysisView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFPAnalysisDoc)));
	return (CFPAnalysisDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisView message handlers

void CFPAnalysisView::OnFileOpen() 
{
  CFPAnalysisDoc* pDoc = GetDocument();

  
  CString sFilename;
  CString sFilt="BMP (*.bmp)|*.bmp|All files (*.*)|*.*||";

  CFileDialog dlg(
		TRUE,				// Create an open file dialog
		"*.BMP",			// Default file extension
		NULL,				// Filename
		OFN_HIDEREADONLY |	// Flags - don't show the read only check box)
		OFN_FILEMUSTEXIST,	//       - make sure file exists
		sFilt);				// the file filter

  dlg.m_ofn.lpstrTitle = "Choose The Fingerprint Bitmap...";  //set the title

	if (dlg.DoModal()==IDOK)
	{
		sFilename = dlg.GetPathName();
		CString sExt = dlg.GetFileExt();
		CString sFilenameShort= dlg.GetFileName();

		if (!sExt.CompareNoCase("BMP"))
		{
			currentimage.SetFilename(sFilename);
			currentimage.LoadBMP();
			Invalidate(FALSE);
			pDoc->SetTitle(sFilenameShort);
		}
		else
			AfxMessageBox("Incorrect File Type.", MB_ICONSTOP);
		
	}

	  //set the size of view to image-size...
	  CChildFrame* pParent =(CChildFrame*)GetParentFrame();
	  CRect rcParent;

	  rcParent.left = 0;
	  rcParent.top =0;
	  rcParent.right = (int)currentimage.GetWidth();
	  rcParent.bottom = (int)currentimage.GetHeight();
	  pParent->MoveWindow(&rcParent);

	  //initialize zoom-specific members
	  m_nNum = m_nDen = 1;
	  SetFPScrollInfo();

      // Refresh the entire view...
	  Invalidate(TRUE);				
}

void CFPAnalysisView::OnFileSave() 
{
  if (currentimage.OK())
	{
		if(AfxMessageBox("This will overwrite your existing file.", MB_ICONEXCLAMATION | MB_OKCANCEL)==IDOK)
		{
			
			CString sFilename = currentimage.GetFilename();
			CString sExt = sFilename.Right(3);

			if (!sExt.CompareNoCase("BMP"))
				currentimage.SaveBMP(sFilename);

			// disable undo after save	
			CWnd* pMain = GetParent();
			if (pMain != NULL)
			{
				CMenu* pMenu = pMain->GetMenu();
				pMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED | MF_GRAYED);
			}

			Invalidate(TRUE);					// Refresh the entire view	
			
		}
	}	
}

void CFPAnalysisView::OnFileSaveAs() 
{
   if (currentimage.OK())
	{
		CString sFilename = currentimage.GetFilename();
		CString sFilt="BMP (*.bmp)|*.bmp||";

		CFileDialog dlg(
			FALSE,							// Create a save as file dialog
			"*.BMP",						// Default file extension
			sFilename,						// Filename
			OFN_HIDEREADONLY| 				// Flags - don't show the read only check box
			OFN_FILEMUSTEXIST|				//       - make sure file exists
			OFN_OVERWRITEPROMPT,			//       - ask about overwrite if file exists
			sFilt);							// the file filter

		if (dlg.DoModal()==IDOK)
		{
			sFilename = dlg.GetPathName();
			CString sExt = dlg.GetFileExt();
			CString sFilenameShort= dlg.GetFileName();

			CFPAnalysisDoc* pDoc = GetDocument();


			if (!sExt.CompareNoCase("BMP"))
			{
				currentimage.SetFilename(sFilename);
				currentimage.SaveBMP(sFilename);
				pDoc->SetTitle(sFilenameShort);
			}

			// disable undo after save	
			CWnd* pMain = AfxGetMainWnd();
			if (pMain != NULL)
			{
				CMenu* pMenu = pMain->GetMenu();
				pMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED|MF_GRAYED);
			}

			Invalidate(TRUE);				// Refresh the entire view	

		}
	}	
}
void CFPAnalysisView::OnWindowZoomin() 
{
	if (m_nDen != 1) 
	{

      ASSERT(1 == m_nNum);
      m_nDen /= 1;

    } 
	else 
	{

      m_nNum *= 2;

	}
  	
	//modify total,page,line sizes
	SetFPScrollInfo();

	//draw the picture with StretchDIbits
	Invalidate(TRUE);
}

void CFPAnalysisView::OnWindowZoomout() 
{
	if (m_nDen != 1) 
	{

      ASSERT(1 == m_nNum);
      m_nDen *= 2;

    } 
	else 
	{

      m_nNum /= 2;

	}
  	
	////modify total,page,line sizes
	SetFPScrollInfo();

	////draw the picture with StretchDIbits
	Invalidate(TRUE);
}

//////////////////////////////TWAIN Specific////////////////////////////////////////
void CFPAnalysisView::OnFileScan() 
{
	
    CFPAnalysisDoc* pDoc = GetDocument();

   	CScanDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		currentimage.SetFilename(dlg.m_szImageName);
		currentimage.LoadBMP();
		Invalidate(FALSE);
		pDoc->SetTitle(dlg.m_szImageName);
	}

	//set the size of view to image-size...
	  CChildFrame* pParent =(CChildFrame*)GetParentFrame();
	  CRect rcParent;

	  rcParent.left = 0;
	  rcParent.top =0;
	  rcParent.right = (int)currentimage.GetWidth();
	  rcParent.bottom = (int)currentimage.GetHeight();
	  pParent->MoveWindow(&rcParent);

	  
	  SetFPScrollInfo();

      // Refresh the entire view...
	  Invalidate(TRUE);	
}


////////////////////////////////////////////////////////////////////////////////////
////////////				ImageProcessing Menu Interfaces            /////////////
////////////////////////////////////////////////////////////////////////////////////
void CFPAnalysisView::OnEditUndo() 
{
  CWnd* pMain = GetParent();
  CFPAnalysisDoc* pDoc = GetDocument();
  CString szTitle = currentimage.GetFilename();

  if (pMain != NULL)
  {
	CMenu* pMenu = pMain->GetMenu();
	UINT state = pMenu->GetMenuState(ID_EDIT_UNDO, MF_BYCOMMAND);
	ASSERT(state != 0xFFFFFFFF);
		
	if (state & MF_GRAYED)
	{
			// do nothing if undo is grayed
	}
	else
	{
	   currentimage.SetOperationType(UNDO);
       currentimage.go();
	   pDoc->SetTitle(szTitle);  // if UNDO set caption to the filename
       pMenu->EnableMenuItem(ID_EDIT_UNDO, MF_DISABLED | MF_GRAYED); //disable undo
       Invalidate(TRUE);
	}
	
  }

}

void CFPAnalysisView::OnEditCopy() 
{
	if (currentimage.OK()) 
	{
	   CBitmap     memBmp;
	   CBitmap*    memOld;
	   CClientDC   wndDC(this);
	   CDC         memDC;
	   CRect       rect;
	   
	   //First create a memory DC compatible to client DC
	   memDC.CreateCompatibleDC(&wndDC);

	   //Get client's size
	   GetWindowRect(&rect);
	   
	   //Create the memory bitmap compatible to memory DC just created
       memBmp.CreateCompatibleBitmap(&memDC,rect.Width(),rect.Height());

	   //Select the bitmap into the memory DC & save the old bitmap
	   memOld = memDC.SelectObject(&memBmp);

	   //Copy client DC(selected bitmap) ---> memory DC(selected bitmap)
	   memDC.BitBlt(0,0,rect.Width(),rect.Height(),&wndDC,0,0,SRCCOPY);

	   //Now we have a CBitmap (memory bitmap) which is copy of present view-window 
	   //loaded in memory 

	   //Invoke actual clipboard functions
	   AfxGetApp()->GetMainWnd()->OpenClipboard();

	   //Make it empty
	   EmptyClipboard();

	   //Copy the memory bitmap to clipboard
	   SetClipboardData(CF_BITMAP,memBmp.GetSafeHandle());

	   //Close the clipboard
	   CloseClipboard();

	   //Select the old & save bitmap back to memory DC
	   //In other words: Seperate CBitmap-memDC association
	   memDC.SelectObject(memOld);

	   //Now detach the bitmap handle(HBITMAP) from CBitmap object 
	   //REASON:When local scope ends CBitmap gets destroyed.If association is not broken
	   //       then bitmap handle gets deleted too with CBitmap.
	   //memBmp.Detach();

	}

	   return;
}

void CFPAnalysisView::OnEditData() 
{
   CEditDlg dlgEdit;
   dlgEdit.DoModal();
}

void CFPAnalysisView::OnViewGray() 
{
   CString szTitle = currentimage.GetFilename();
   CFPAnalysisDoc* pDoc = GetDocument();

   currentimage.SetOperationType(GRAYINT);
   currentimage.go();
   szTitle += " - Grayscaled(B/W) ";

   
   pDoc->SetTitle(szTitle);

   Invalidate(TRUE);
}


void CFPAnalysisView::OnViewSegmentation() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(FPSEGMENTATION);
  currentimage.go();
  szTitle += " - Segmented Fingerprint ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewBinary() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(HISTOGRAMBINARIZE);
  currentimage.go();
  szTitle += " - Binarized With Histogram-based Thresholding ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewAdaptivebinarize() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(ADAPTIVEBINARIZE);
  currentimage.go();
  szTitle += " - Binarized With Adaptive Thresholding ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);

}
 
void CFPAnalysisView::OnViewNegative() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(NEGATIVE);
  currentimage.go();
  szTitle += " - Negative Of The Previous ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewConvolve() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(CONV);
  currentimage.go();
  szTitle += " - Convolved/Filtered ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);	
}

void CFPAnalysisView::OnViewEdge() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(EDGEDETECTION);
  currentimage.go();
  szTitle += " - Edge Mapped ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewEqualize() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(EQUALIZE);
  currentimage.go();
  szTitle += " - Equalized ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}


void CFPAnalysisView::OnViewBlurr() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(BLUR);
  currentimage.go();
  szTitle += " - Blurred ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewRoi() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(MARKROI);
  currentimage.go();
  szTitle += " - Region Masked ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
	
}
void CFPAnalysisView::OnViewNormalize() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(NORMALIZE);
  currentimage.go();
  szTitle += " - Normalized ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewThinning() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(THINNING);
  currentimage.go();
  szTitle += " - Thinned ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
   	
}

void CFPAnalysisView::OnViewExtraction() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(EXTRACT);
  currentimage.go();
  szTitle += " - Minutiae Extracted ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewCore() 
{
  CString szTitle = currentimage.GetFilename();
  CFPAnalysisDoc* pDoc = GetDocument();

  currentimage.SetOperationType(CORE);
  currentimage.go();
  szTitle += " - CORE Located ";

  pDoc->SetTitle(szTitle);

  Invalidate(TRUE);
}

void CFPAnalysisView::OnViewOrientation() 
{
  currentimage.SetOperationType(ORIENTATION);
  currentimage.go();
  Invalidate(TRUE);
}


void CFPAnalysisView::OnActionRegionofinterest() 
{
	currentimage.SetOperationType(MARKROI);
	currentimage.go();
	Invalidate(TRUE);
	
}

void CFPAnalysisView::OnMouseMove(UINT nFlags, CPoint point) 
{
    ///////Get current pixel's RGB value
/*
	if (currentimage.OK() != false)
	{
	 
	 CRect rect;
	 GetClientRect(&rect);

	 CPoint pointImage = point + GetDeviceScrollPosition();
	 if (rect.PtInRect(pointImage))
	 {
	
	   CMainFrame *pMainFrame = ((CMainFrame *) AfxGetApp()->m_pMainWnd);

       CString szValue;
	   szValue=currentimage.GetPixelValueString(point);
	   CString text;
	   text.Format("(%3d, %3d)  ",point.x, point.y);
	   text+="[";
	   text+=szValue;
	   text+="]";
       pMainFrame->SetMessageText((LPCTSTR)text);
		
	}
	

	CScrollView::OnMouseMove(nFlags, point);
	*/
}

void CFPAnalysisView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
   	if (currentimage.OK())
	{
		CMenu MenuBar;
		MenuBar.LoadMenu(IDR_FPANALTYPE);
		CMenu* pMenu = MenuBar.GetSubMenu(2);
		
		pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
	}
	else
	{
		CScrollView::OnContextMenu(pWnd,point);
	}
}
 
///////////////////////////Paintshop Pro like effect////////////////////////
////////////////////////////////////////////////////////////////////////////
///////////////////////////Zoom On Scrolling////////////////////////////////
BOOL CFPAnalysisView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
    short zoomfactor=(zDelta / 120);
	if (zDelta < 0)
	{
		//mouse wheel is rotated towards user
		OnWindowZoomin();
	
	}
	else
	{
		//mouse wheel is rotated away from user
		OnWindowZoomout();
	}

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CFPAnalysisView::OnWindowFit() 
{
   SIZE sz;
   sz.cx = (int)currentimage.GetWidth();
   sz.cy = (int)currentimage.GetHeight();

   SetScaleToFitSize(sz);

   m_nDen = m_nNum = 1;

   //modify total,page,line sizes
   SetFPScrollInfo();

   //draw the picture with StretchDIbits
   Invalidate(TRUE);
}






void CFPAnalysisView::OnHelpAbout() 
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();	
}




void CFPAnalysisView::OnViewDocumentinfo() 
{
  if (currentimage.OK() == false)
	  return;

  CImageInfoDlg dlg;
  CString szCompression;
  BITMAP bmp;

  currentimage.GetBitmap(&bmp);
  
  dlg.m_height.Format("%d Pixels",bmp.bmHeight);
  dlg.m_width.Format("%d Pixels",bmp.bmWidth);
  dlg.m_bpp.Format("%d",bmp.bmBitsPixel);

  /*switch((currentimage.m_pbihdr)->biCompression)
  {
   case BI_RGB:
	    szCompression = "Uncompressed Format";
		break;
   case BI_RLE8:
	    szCompression = "RLE With 8 bits/pixel";
		break;
   case BI_RLE4:
	    szCompression = "RLE With 4 bits/pixel";
		break;
   }*/

  dlg.m_compression = "";//szcompression;
  dlg.m_imagesize.Format("%d KByte",((bmp.bmHeight * bmp.bmBitsPixel)*(bmp.bmWidthBytes))/(8 * 1024));
  dlg.m_colorsused.Format("%d",0);

  dlg.DoModal();

   
}

/////////////////////// Drag & Drop support //////////////////
void CFPAnalysisView::OnDropFiles(HDROP hDropInfo) 
{
	CFPAnalysisDoc* pDoc = GetDocument();

    WORD dwFiles;
    char lpszFile[80];

	//Drop only one file at a time, so if more than one file has been dropped, the 
	//action is disallowed.
 
	dwFiles = ::DragQueryFile(hDropInfo,0xFFFFFFFF,(LPTSTR)NULL,0);

	if (dwFiles > 1)
	   return;

	//Handle one file at a time

	// Get the name of the file dropped...
    ::DragQueryFile(hDropInfo,0,lpszFile,sizeof(lpszFile));
	
	//DEBUG
	AfxMessageBox(lpszFile);

	//Be sure that file is BMP file
	if (strstr(lpszFile,".BMP"))
	{
	    currentimage.SetFilename(lpszFile);
		currentimage.LoadBMP();
		Invalidate(FALSE);
		pDoc->SetTitle(lpszFile);
	}
	else
		AfxMessageBox("Incorrect File Type.", MB_ICONSTOP);

	//set the size of view to image-size...
	 CChildFrame* pParent =(CChildFrame*)GetParentFrame();
	 CRect rcParent;

	 rcParent.left = 0;
	 rcParent.top =0;
	 rcParent.right = (int)currentimage.GetWidth();
	 rcParent.bottom = (int)currentimage.GetHeight();
	 pParent->MoveWindow(&rcParent);

	 //initialize zoom-specific members
	 m_nNum = m_nDen = 1;
	 SetFPScrollInfo();

     // Refresh the entire view...
	 Invalidate(TRUE);		
	
	 //Call base class's implementation
	 CScrollView::OnDropFiles(hDropInfo);
}





void CFPAnalysisView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
    OnDraw(pDC);
	
	CScrollView::OnPrint(pDC, pInfo);
}




void CFPAnalysisView::OnViewWizard() 
{
    CPropertySheet ps;

	CHistogramPage     page1;
	CGaussianPage      page2;
	
    ps.AddPage(&page1);
	ps.AddPage(&page2);
	
	ps.SetWizardMode();
    
	ps.DoModal();
	
}


void CFPAnalysisView::OnFilterAfterMinutiaeExtraction()
{
	 CString szTitle = currentimage.GetFilename();
	  CFPAnalysisDoc* pDoc = GetDocument();

	  currentimage.SetOperationType(MINUTIAE_FILTERING);
	  currentimage.go();
	  szTitle += " - Minutiae Extracted ";

	  pDoc->SetTitle(szTitle);

	  Invalidate(TRUE);
}
