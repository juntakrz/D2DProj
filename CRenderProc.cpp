#include "pch.h"
#include "CRenderProc.h"

int CRenderProc::m_iRefreshTime = 0;
bool CRenderProc::m_IsTracking = true;
bool CRenderProc::m_IsProcActive = true;
POINT CRenderProc::m_Point = { 0, 0 };


CRenderProc::CRenderProc()
{
	//precalculate frame refresh time
	GetRefreshTime(CRenderProc::m_iRefreshTime);

	//add shared pointer to the main render thread to the vector pool of app threads
	vThreadPool.insert(vThreadPool.begin() + THREADID_UPDATE, std::make_shared<std::thread>(&CRenderProc::UpdateThread));
	vThreadPool.insert(vThreadPool.begin() + THREADID_RENDER, std::make_shared<std::thread>(&CRenderProc::RenderThread));
}

CRenderProc::~CRenderProc()
{
	//shutting down threads
	m_IsTracking = false;
	m_IsProcActive = false;

	vThreadPool.at(THREADID_UPDATE)->join();
	vThreadPool.at(THREADID_RENDER)->join();

}

void CRenderProc::GetRefreshTime(int &iRefreshTime)
{
	//returns time in milliseconds
	iRefreshTime = 1000 / (APP_REFRESHLIMIT * 2);
}

void CRenderProc::UpdateThread()
{
	while (m_IsProcActive)
	{
			if (!CScriptProc::isLoading) CScriptProc::Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(m_iRefreshTime));
	}
}

void CRenderProc::RenderThread()
{
	while (m_IsProcActive)
	{
			if (!CScriptProc::isLoading) CScriptProc::Render();
			std::this_thread::sleep_for(std::chrono::milliseconds(m_iRefreshTime));
	}
}