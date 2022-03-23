#pragma once

#include <wincodec.h>
#include "CD2DCore.h"

//TO DO!!
//Understand how to load raw bitmap images straight into D2DBitmap

class CD2DBitmap : public CD2DCore
{
private:
	std::vector<std::pair<uint16_t, ID2D1Bitmap*>> m_VecPD2DBitmap;
	ID2D1Bitmap* m_pD2DBitmap;
	HRESULT CreateCompatibleD2DBitmap(const uint16_t &resID, ID2D1Bitmap* &pD2DBitmap);
public:
	CD2DBitmap();
	~CD2DBitmap();
	CD2DBitmap(const CD2DBitmap&) = delete;

	static CD2DBitmap& Get()
	{
		static CD2DBitmap _sInstance;
		return _sInstance;
	}

	void Clear();
	bool AddBitmap(const uint16_t &resID);
	ID2D1Bitmap* GetBitmap(const uint16_t &bitmapID);
	void DrawBitmap(const uint16_t &resID, float x, float y, float width, float height, float alpha = 1.0f);
	void GetBitmapSize(const uint16_t &resID, float &bmpW, float &bmpH);
};