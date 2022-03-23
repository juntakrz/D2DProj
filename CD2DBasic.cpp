#include "CD2DBasic.h"

void CD2DBasic::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a, float strokeW)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_pSolidColorBrush, strokeW);
}

void CD2DBasic::DrawCircle(float x, float y, float radius, float r, float g, float b, float a, float strokeW)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pSolidColorBrush, strokeW);
}

void CD2DBasic::FillCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pSolidColorBrush);
}

void CD2DBasic::DrawEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a, float strokeW)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), m_pSolidColorBrush, strokeW);
}
void CD2DBasic::FillEllipse(float x, float y, float radiusX, float radiusY, float r, float g, float b, float a)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radiusX, radiusY), m_pSolidColorBrush);
}

void CD2DBasic::DrawRect(float x, float y, float w, float h, float r, float g, float b, float a, float strokeW)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->DrawRectangle(D2D1::RectF(x, y, x + w, y + h), m_pSolidColorBrush, strokeW);
}

void CD2DBasic::FillRect(float x, float y, float w, float h, float r, float g, float b, float a)
{
	m_pSolidColorBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->FillRectangle(D2D1::RectF(x, y, x + w, y + h), m_pSolidColorBrush);
}