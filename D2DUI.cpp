#include "D2DUI.h"
#include "CMouseTrack.h"

bool D2DUI::m_IsTracking = false;

D2DUI::D2DUI()
{
	//avoiding copying stuff for the first 64 controls
	m_vITHVec.reserve(64);
	m_vCtlIDAreas.reserve(64);
}

HRESULT D2DUI::ClearControls()
{
	for (auto& hCtl : m_vITHVec)			//deleting control objects to free up memory
	{
		delete hCtl.pCtl;
	}
	m_vITHVec.clear();
	return S_OK;
}

std::vector<D2DUI::ITH>& D2DUI::GetCtlVector()
{
	return m_vITHVec;
}

std::vector<std::pair<uint8_t, RECT>>* D2DUI::GetCtlAreaVector()
{
	return &m_vCtlIDAreas;
}

HRESULT D2DUI::Create(uint8_t ctlID, uint8_t ctlType, uint16_t resID, float ctlX, float ctlY, float ctlW, float ctlH, float ctlA)
{
	//create and initialize control
	switch (ctlType)
	{
	case (TYPE_BUTTON) :
	{
		m_vITHVec.emplace_back(ctlID, ctlType, new CButton(ctlID, resID, ctlX, ctlY, ctlW, ctlH, ctlA));
		break;
	}
	case (TYPE_PANEL) :
	{
		break;
	}
	}
	return S_OK;
}

HRESULT D2DUI::SetAnimation(uint8_t ctlID, uint8_t ctlState, uint8_t ctlAnim, std::array<float, 8> Vec8f, bool doAnimBlend)
{
	uint8_t ctlType;
	ICtl* pCtl = nullptr;
	D2DUI::GetCtlByID(ctlID, ctlType, pCtl);
	if (pCtl)
	{
		switch (ctlType)
		{
		case TYPE_BUTTON :
		{
			CButton* pButton = reinterpret_cast<CButton*>(pCtl);
			pButton->SetAnimData(ctlAnim, ctlState, Vec8f, doAnimBlend);
			break;
		}
		case TYPE_PANEL :
		{
			break;
		}
		}
	}
	return S_OK;
}

void D2DUI::GetCtlByID(uint8_t& ctlID, uint8_t& outCtlType, ICtl*& outHCtl)
{
	auto it = std::find_if(m_vITHVec.begin(), m_vITHVec.end(), [&ctlID](const ITH& element)
		{
			return element.ctlID == ctlID;
		});
	if (it != m_vITHVec.end())
	{
		outCtlType = it->ctlType;
		outHCtl = it->pCtl;
		return;
	}
	outCtlType = 0;
	outHCtl = nullptr;
}

//GRAPHICS METHODS
HRESULT D2DUI::ClearBitmaps()
{
	CD2DBitmap::Get().Clear();
	return S_OK;
}

HRESULT D2DUI::AddBitmap(const uint16_t& resID)
{
	CD2DBitmap::Get().AddBitmap(resID);
	return S_OK;
}

//PROCESS METHODS
HRESULT D2DUI::Initialize(HWND hWnd, RECT& clRect)
{
	CD2DCore::Get().InitD2D(hWnd, clRect);
	m_hWnd = hWnd;
	return S_OK;
}

HWND D2DUI::GetHandleToWindow()
{
	return m_hWnd;
}

void D2DUI::Update()
{
	for (const auto& it : m_vITHVec)
	{
		it.pCtl->Update();
	}
}

void D2DUI::Render()
{
	for (const auto& it : m_vITHVec)
	{
		it.pCtl->Render();
	}
}

void D2DUI::SetMouseScansPerSec(uint8_t scansPerSecond)
{
	m_MouseScanDelay = 1000 / scansPerSecond;
}

uint16_t& D2DUI::GetMouseScanDelay()
{
	return m_MouseScanDelay;
}

void D2DUI::EnableMouseTracking()
{
	m_IsTracking = true;
	CMouseTrack::Get().Initialize();
	if (!m_pTrackThread)
	{
		m_pTrackThread = std::make_shared<std::thread>(&CMouseTrack::MouseThread, &CMouseTrack::Get());
	}
}

void D2DUI::DisableMouseTracking()
{
	m_IsTracking = false;
	if (m_pTrackThread)
	{
		m_pTrackThread->join();
		m_pTrackThread = nullptr;
	}
}