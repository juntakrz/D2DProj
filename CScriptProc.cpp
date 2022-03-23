#include "pch.h"
#include "CScriptProc.h"

CScript* CScriptProc::m_pCurrentScript;					//a script to handle with the abstract class
bool CScriptProc::isLoading = false;					//send this variable to main render method so it will pause on loading

bool CScriptProc::LoadInitialScript(CScript* m_pReceivedScript)
{
	if (m_pReceivedScript)
	{
		isLoading = true;
		m_pCurrentScript = m_pReceivedScript;				//load received script
		m_pCurrentScript->Load();
		isLoading = false;
		return true;
	}
	return false;
}

bool CScriptProc::LoadNextScript(CScript* m_pReceivedScript)
{
	isLoading = true;
	m_pCurrentScript->Unload();
	m_pReceivedScript->Load();
	delete m_pCurrentScript;
	m_pCurrentScript = m_pReceivedScript;
	m_pCurrentScript->Load();
	isLoading = false;
	return true;
}

void CScriptProc::Update()
{
	m_pCurrentScript->Update();
}

void CScriptProc::Render()
{
	m_pCurrentScript->Render();
}