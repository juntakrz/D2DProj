#pragma once

#include <d2d1.h>
#include <vector>
//#include "D2DUI.h"

class CD2DCore {												//Direct2D core methods
protected:
	CD2DCore() {};
	~CD2DCore();
	//COM objects - always release
	static ID2D1Factory* m_pFactory;							//generates Direct2D resources
	static ID2D1HwndRenderTarget* m_pRenderTarget;				//target to draw graphics to
	static ID2D1SolidColorBrush* m_pSolidColorBrush;			//generic solid color brush, used by CD2DBasic

public:
	std::vector<float> m_vFloatArray;							//float array that can be used by any of D2D methods
	CD2DCore(const CD2DCore &) = delete;

	static CD2DCore& Get()
	{
		static CD2DCore _sInstance;
		return _sInstance;
	}

	bool InitD2D(HWND hWnd, RECT& clRect);						//initialize Direct2D pointers

	//returns created D2D objects on demand
	void GetD2DObjects(ID2D1Factory* &pFactory, ID2D1HwndRenderTarget* &pRenderTarget, ID2D1SolidColorBrush* &pSolidColorBrush);
	ID2D1Factory* GetD2DFactory();
	ID2D1HwndRenderTarget* GetD2DRenderTarget();

	//wrapper functions
	void BeginDraw() { m_pRenderTarget->BeginDraw(); }			//start drawing
	void EndDraw() { m_pRenderTarget->EndDraw(); }				//end drawing
	void ClearScreen(float r = 0.0f, float g = 0.0f, float b = 0.0f);
};