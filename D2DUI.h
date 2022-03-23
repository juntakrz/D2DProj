#pragma once

#include <array>
#include <vector>
#include <thread>
#include <memory>
#include <d2d1.h>

#include "CD2DCore.h"
#include "CD2DBasic.h"
#include "CD2DBitmap.h"

#include "ICtl.h"
#include "CButton.h"

class D2DUI
{
private:
	D2DUI(const D2DUI&) = delete;		//only references to this singleton are allowed

	struct ITH
	{
		ITH(uint8_t& a, uint8_t& b, ICtl* c) : ctlID(a), ctlType(b), pCtl(c) {}

		uint8_t ctlID, ctlType;
		ICtl* pCtl;
	};
	std::vector<ITH> m_vITHVec;			//ID, Type, object Handle vector

	uint16_t m_MouseScanDelay = 25;		//scans mouse 40 times a second by default
	uint8_t m_FPS = 60;					//updates per second for the auto render method

	HWND m_hWnd = nullptr;
	std::shared_ptr<std::thread> m_pUpdateThread, m_pRenderThread, m_pTrackThread;

protected:
	D2DUI();
	~D2DUI() { DisableMouseTracking(); };
	static bool m_IsTracking;
	std::vector<std::pair<uint8_t, RECT>> m_vCtlIDAreas;

public:
	enum Type
	{
		TYPE_NONE = 0, TYPE_BUTTON, TYPE_PANEL, TYPE_LAYER
	};
	enum State
	{
		STATE_CREATE = 0, STATE_HOVER, STATE_DOWN, STATE_CLICK, STATE_DESTROY, STATE_IDLE
	};
	enum Anim
	{
		ANIM_IDLE = 0, ANIM_ALPHASCALEMOVE_TO, ANIM_ALPHASCALEMOVE_FROM, ANIM_SCALE_TO, ANIM_SCALE_FROM, ANIM_CIRCULARSCALE
	};

	static D2DUI& Get()
	{
		static D2DUI _pInstance;
		return _pInstance;
	}

	//CONTROL METHODS
	HRESULT ClearControls();	//delete all stored controls
	std::vector<ITH>& GetCtlVector();
	std::vector<std::pair<uint8_t, RECT>>* GetCtlAreaVector();
	//no references below because methods receive rvalues
	HRESULT Create(uint8_t ctlID, uint8_t ctlType, uint16_t resID, float ctlX, float ctlY, float ctlW = 0.0f, float ctlH = 0.0f, float ctlA = 1.0f);
	HRESULT SetAnimation(uint8_t ctlID, uint8_t ctlState, uint8_t ctlAnim, std::array<float, 8> Vec8f = { 0.0f }, bool doAnimBlend = false);
	void GetCtlByID(uint8_t& ctlID, uint8_t& outCtlType, ICtl*& outHCtl);

	//GRAPHICS METHODS
	HRESULT ClearBitmaps();		//delete all stored bitmaps
	HRESULT AddBitmap(const uint16_t& resID);

	//PROCESS METHODS
	HRESULT Initialize(HWND hWnd, RECT& clRect);
	HWND GetHandleToWindow();
	void Update();
	void Render();
	void EnableAutoRender(bool enableUpdate = true, bool enableRender = true, uint8_t desiredFPS = 60);
	void DisableAutoRender(bool disableUpdate = true, bool disableRender = true);
	void SetMouseScansPerSec(uint8_t scansPerSecond);
	uint16_t& GetMouseScanDelay();
	void EnableMouseTracking();
	void DisableMouseTracking();
};