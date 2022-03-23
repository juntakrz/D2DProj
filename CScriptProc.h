#pragma once

#include "CScript.h"

class CScriptProc {

	static CScript* m_pCurrentScript;			//currently exectued script
	CScriptProc() {};
	~CScriptProc() {};

public:
	static bool isLoading;
	static bool LoadInitialScript(CScript* m_pReceivedScript);
	static bool LoadNextScript(CScript* m_pReceivedScript);
	static void Update();			//passed on to methods in an m_pReceivedScript
	static void Render();
};