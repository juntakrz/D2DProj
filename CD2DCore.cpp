#include "CD2DCore.h"

ID2D1Factory* CD2DCore::m_pFactory = nullptr;
ID2D1HwndRenderTarget* CD2DCore::m_pRenderTarget = nullptr;
ID2D1SolidColorBrush* CD2DCore::m_pSolidColorBrush = nullptr;

CD2DCore::~CD2DCore()
{
	if (m_pFactory)
	{
		m_pFactory->Release();
		m_pFactory = nullptr;
	}
	if (m_pRenderTarget)
	{
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}
	if (m_pSolidColorBrush)
	{
		m_pSolidColorBrush->Release();
		m_pSolidColorBrush = nullptr;
	}
}

bool CD2DCore::InitD2D(HWND hWnd, RECT& clRect)
{
	m_vFloatArray = { 0.0f, 0.0f, 0.0f };

	//create factory and check if HRESULT returns anything but S_OK
	HRESULT hr;

	#if defined(DEBUG) || defined(_DEBUG)
	D2D1_FACTORY_OPTIONS fo;
	fo.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, fo, &m_pFactory);
	#else
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	#endif
	if (hr != S_OK) return false;

	hr = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),														//set default render target properties
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clRect.right, clRect.bottom)),	//handle to window, render size
		&m_pRenderTarget																	//render target
	);
	if (hr != S_OK) return false;

	if (FAILED(m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &m_pSolidColorBrush))) return false;

	return true;
}

void CD2DCore::ClearScreen(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}

void CD2DCore::GetD2DObjects(ID2D1Factory* &pFactory, ID2D1HwndRenderTarget* &pRenderTarget, ID2D1SolidColorBrush* &pSolidColorBrush)
{
	pFactory = m_pFactory;
	pRenderTarget = m_pRenderTarget;
	pSolidColorBrush = m_pSolidColorBrush;
}

ID2D1Factory* CD2DCore::GetD2DFactory()
{
	return m_pFactory;
}

ID2D1HwndRenderTarget* CD2DCore::GetD2DRenderTarget()
{
	return m_pRenderTarget;
}