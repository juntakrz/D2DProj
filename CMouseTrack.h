#pragma once

#include "D2DUI.h"

class CMouseTrack : public D2DUI
{
	CMouseTrack() {};
	~CMouseTrack() {};

	HWND m_hWnd;
	POINT m_Point;
	uint16_t m_MouseScanDelay;

	//std::shared_ptr<std::thread> m_pTrackThread;

public:
	static CMouseTrack& Get()
	{
		static CMouseTrack _sInstance;
		return _sInstance;
	}

	//std::shared_ptr CreateMouseThread();
	void Initialize();
	void MouseThread();
};