// FPAnalysis.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FPAnalysis.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "FPAnalysisDoc.h"
#include "FPAnalysisView.h"
#include "dialogs.h"
#include "dialogs1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisApp

BEGIN_MESSAGE_MAP(CFPAnalysisApp, CWinApp)
	//{{AFX_MSG_MAP(CFPAnalysisApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisApp construction

CFPAnalysisApp::CFPAnalysisApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFPAnalysisApp object

CFPAnalysisApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisApp initialization

BOOL CFPAnalysisApp::InitInstance()
{
		// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
		
	AfxEnableControlContainer();
	//m_dlgSkin.Create(IDD_SKINDIALOG_DIALOG);
    //m_pSkin = m_dlgSkin.GetDlgItem(IDC_SKIN2)->GetControlUnknown(); 

	//m_dlgAgent.Create(IDD_AGENT_DIALOG);
    //m_theAgent.Probe(&m_dlgAgent.m_Agent);


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Fingerprint Analysis 1.00"));

	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_FPANALTYPE,
		RUNTIME_CLASS(CFPAnalysisDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFPAnalysisView));
	AddDocTemplate(pDocTemplate);

	EnableShellOpen(); 

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	//Drag & Drop support
	m_pMainWnd->DragAcceptFiles();
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// no new document at start-up
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
 
	// The main window has been initialized, so show and update it.

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->CenterWindow();
	pMainFrame->UpdateWindow();
	pMainFrame->SetTitle("Fingerprint Analysis");


	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


// App command to run the dialog
void CFPAnalysisApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFPAnalysisApp message handlers


BOOL CFPAnalysisApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}

int CFPAnalysisApp::ExitInstance() 
{
    // We need to release the reference to the Skin component prior destructor is called
	//m_pSkin.Release(); 
    //m_dlgSkin.DestroyWindow();

	//m_dlgAgent.DestroyWindow();

	return CWinApp::ExitInstance();
}
