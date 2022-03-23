#include "CMouseTrack.h"

void CMouseTrack::Initialize()
{
	m_hWnd = D2DUI::Get().GetHandleToWindow();
	m_MouseScanDelay = D2DUI::Get().GetMouseScanDelay();
	//m_pTrackThread = std::make_shared<std::thread>(&CMouseTrack::MouseThread);
}

void CMouseTrack::MouseThread()
{
	wchar_t debug[64];

	while (m_IsTracking)
	{
		GetCursorPos(&m_Point);
		ScreenToClient(m_hWnd, &m_Point);

		wsprintfW(debug, L"Cursor at X=%d Y=%d\n", m_Point.x, m_Point.y);
		OutputDebugStringW(debug);

		std::this_thread::sleep_for(std::chrono::milliseconds(m_MouseScanDelay));
	}

}