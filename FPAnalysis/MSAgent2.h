// MSAgent.h: interface for the CMSAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSAGENT_H__EB99463D_00F5_414E_8092_C02240C152B7__INCLUDED_)
#define AFX_MSAGENT_H__EB99463D_00F5_414E_8092_C02240C152B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "agentctlex1.h"
#include "agentctlcharacters1.h"
#include "agentctlcharacterex1.h"
#include "agentctlrequest1.h"

class CMSAgent  
{
public:
	CMSAgent();
	virtual ~CMSAgent();

	//Workhorse
    CAgentCtlCharacterEx  Agent;
	void Probe(CAgentCtlEx* pAgentControl);
	void Probe(CAgentCtlEx* pAgentControl,CString CharID,CString szCharPath);

	//Actions
	void Show(BOOL bFast = FALSE);
	void Hide(BOOL bFast = FALSE);
	void Speak(CString szText);
	void Think(CString szText);

	//Set character path
	void SetCharPath(CString szCharPath);

	//Character loading/unloading functions
    void Unload();
	void Load(CString CharID,CString szCharPath);
	void Load(CString CharID);
	
	//Query status
	bool IsVisible();
private:
	CAgentCtlCharacters   m_characters;
	CAgentCtlEx*          m_pAgentControl;
	CString               m_CharID;
	CString               m_szCharPath;
	bool                  m_bVisible;
};

#endif // !defined(AFX_MSAGENT_H__EB99463D_00F5_414E_8092_C02240C152B7__INCLUDED_)
