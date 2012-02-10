// FPAnalysisDoc.cpp : implementation of the CFPAnalysisDoc class
//

#include "stdafx.h"
#include "FPAnalysis.h"

#include "FPAnalysisDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisDoc

IMPLEMENT_DYNCREATE(CFPAnalysisDoc, CDocument)

BEGIN_MESSAGE_MAP(CFPAnalysisDoc, CDocument)
	//{{AFX_MSG_MAP(CFPAnalysisDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisDoc construction/destruction

CFPAnalysisDoc::CFPAnalysisDoc()
{
	// TODO: add one-time construction code here
	

}

CFPAnalysisDoc::~CFPAnalysisDoc()
{
}

BOOL CFPAnalysisDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisDoc serialization

void CFPAnalysisDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisDoc diagnostics

#ifdef _DEBUG
void CFPAnalysisDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFPAnalysisDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisDoc commands
