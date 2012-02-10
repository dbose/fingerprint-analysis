// MSAgent.cpp: implementation of the CMSAgent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MSAgent2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMSAgent::CMSAgent()
{
   m_pAgentControl = NULL;
   m_szCharPath = "";
   m_CharID = "";
   m_bVisible = false;

}

CMSAgent::~CMSAgent()
{
   //m_pAgentControl = NULL;
}

void CMSAgent::Probe(CAgentCtlEx* pAgentControl)
{
  //Probe a real control to the class
  m_pAgentControl = pAgentControl;
  Probe(m_pAgentControl,"James","C:\\WINDOWS\\Msagent\\chars\\james.acs");

}

void CMSAgent::Probe(CAgentCtlEx* pAgentControl,CString CharID,CString szCharPath)
{
   //Probe a real control to the class
   m_pAgentControl = pAgentControl;

   //First check CharPath is empty ?
   if (szCharPath.IsEmpty())
   {
	   //load default character : GENIE
	   m_szCharPath = "C:\\WINDOWS\\Msagent\\chars\\james.acs";
   }
   else
   {
	   m_szCharPath = szCharPath;
   }

   if (CharID.IsEmpty()==FALSE)
   {
	 VARIANT vPath;
	 VariantInit(&vPath);
	 vPath.vt = VT_BSTR;
	 vPath.bstrVal = m_szCharPath.AllocSysString();

     m_characters = m_pAgentControl->GetCharacters();
	 m_characters.Load(m_CharID = CharID,vPath);
	 Agent = m_characters.Character(m_CharID);
   }
}

void CMSAgent::Show(BOOL bFast)
{
	VARIANT vbFast;
	VariantInit(&vbFast);
	vbFast.vt = VT_BOOL;
	vbFast.boolVal = bFast;

	Agent.Show(vbFast);
	m_bVisible = true;
}

void CMSAgent::Hide(BOOL bFast)
{
    VARIANT vbFast;
	VariantInit(&vbFast);
	vbFast.vt = VT_BOOL;
	vbFast.boolVal = bFast;

	Agent.Hide(vbFast);
	m_bVisible = false;
}

void CMSAgent::Speak(CString szText)
{
	if ((m_bVisible)&&(szText.IsEmpty()==FALSE))
	{
	  CString szDummy = "";
	  VARIANT vszDummy;
	  VariantInit(&vszDummy);
	  vszDummy.vt = VT_BSTR;
	  vszDummy.bstrVal = szDummy.AllocSysString();

	  VARIANT vszText;
	  VariantInit(&vszText);
	  vszText.vt = VT_BSTR;
	  vszText.bstrVal = szText.AllocSysString();

   	  Agent.Speak(vszText,vszDummy);
	}
}

void CMSAgent::Think(CString szText)
{
	if ((m_bVisible)&&(szText.IsEmpty()==FALSE))
	{
		Agent.Think((LPCTSTR)szText);
	}
}

void CMSAgent::SetCharPath(CString szCharPath)
{
	//Check CharPath is empty ?
   if (szCharPath.IsEmpty())
   {
	   //load default character : GENIE
	   m_szCharPath = "C:\\WINDOWS\\Msagent\\chars\\james.acs";
   }
   else
   {
	   m_szCharPath = szCharPath;
   }

}

void CMSAgent::Unload()
{
	m_characters.Unload(m_CharID);
}

void CMSAgent::Load(CString CharID)
{
   if (CharID.IsEmpty()==FALSE)
   {
	 VARIANT vPath;
	 VariantInit(&vPath);
	 vPath.vt = VT_BSTR;
	 vPath.bstrVal = m_szCharPath.AllocSysString();

     m_characters = m_pAgentControl->GetCharacters();
	 m_characters.Load(m_CharID = CharID,vPath);
	 Agent = m_characters.Character(m_CharID);
   }
}

void CMSAgent::Load(CString CharID,CString szCharPath)
{
	//First check CharPath is empty ?
   if (szCharPath.IsEmpty())
   {
	   //load default character : GENIE
	   m_szCharPath = "C:\\WINDOWS\\Msagent\\chars\\james.acs";
   }
   else
   {
	   m_szCharPath = szCharPath;
   }

   if (CharID.IsEmpty()==FALSE)
   {
	 VARIANT vPath;
	 VariantInit(&vPath);
	 vPath.vt = VT_BSTR;
	 vPath.bstrVal = m_szCharPath.AllocSysString();

     m_characters = m_pAgentControl->GetCharacters();
	 m_characters.Load(m_CharID = CharID,vPath);
	 Agent = m_characters.Character(m_CharID);
   }

}

bool CMSAgent::IsVisible()
{
   return m_bVisible;
}
