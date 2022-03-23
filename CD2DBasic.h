#pragma once

#include "CD2DCore.h"

class CD2DBasic : public CD2DCore	//basic shapes framework
{

public:
	CD2DBasic() {};
	~CD2DBasic() {};
	CD2DBasic(const CD2DBasic&) = delete;

	static CD2DBasic& Get()
	{
		static CD2DBasic _sInstance;
		return _sInstance;
	}

	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a = 1.0f, float strokeW = 1.0f);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a = 1.0f, float strokeW = 1.0f);
	void FillCircle(float x, float y, float radius, float r, float g, float b, float a = 1.0f);
	void DrawEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a = 1.0f, float strokeW = 1.0f);
	void FillEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a = 1.0f);
	void DrawRect(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f, float strokeW = 1.0f);
	void FillRect(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f);
};