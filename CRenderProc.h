#pragma once

#include "main.h"

class CRenderProc {
private:
	static int m_iRefreshTime;
	static bool m_IsTracking, m_IsProcActive;
	static POINT m_Point;
	static MSG uMsg;

	static void GetRefreshTime(int& iRefreshTime);

public:
	CRenderProc();
	~CRenderProc();

	static CRenderProc& Get()
	{
		static CRenderProc _sInstance;
		return _sInstance;
	}

	static void MouseThread();
	static void UpdateThread();
	static void RenderThread();
};