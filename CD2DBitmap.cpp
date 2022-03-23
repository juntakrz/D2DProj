#include "CD2DBitmap.h"

CD2DBitmap::CD2DBitmap()
{
	m_pD2DBitmap = nullptr;
}

CD2DBitmap::~CD2DBitmap()
{
	CD2DBitmap::Clear();
}

void CD2DBitmap::Clear()
{
	m_pD2DBitmap = nullptr;
	for (auto it : m_VecPD2DBitmap)
	{
		it.second->Release();
	}
	m_VecPD2DBitmap.clear();
}

bool CD2DBitmap::AddBitmap(const uint16_t &resID)
{
	HRESULT hr;
	hr = CreateCompatibleD2DBitmap(resID, m_pD2DBitmap);
	if (hr != S_OK)
	{
		MessageBoxW(NULL, L"Couldn't create compatible D2D bitmap", L"CD2DBitmap::AddBitmap ERROR", MB_ICONERROR | MB_OK);
		return false;
	}

	m_VecPD2DBitmap.emplace_back(resID, m_pD2DBitmap);
	return true;
}

ID2D1Bitmap* CD2DBitmap::GetBitmap(const uint16_t& resID)
{
	auto it = std::find_if(m_VecPD2DBitmap.begin(), m_VecPD2DBitmap.end(), [&resID](const std::pair<uint16_t, ID2D1Bitmap*>& element)
	{
			return element.first == resID;
	});

	if (it != m_VecPD2DBitmap.end())
	{
		return it->second;
	}
	return nullptr;
}

HRESULT CD2DBitmap::CreateCompatibleD2DBitmap(const uint16_t &resID, ID2D1Bitmap* &pD2DBitmap)
{
	HRESULT hr;
	IWICImagingFactory* pWICFactory = NULL;
	IWICStream* pWICStream = NULL;
	IWICBitmapDecoder* pWICDecoder = NULL;
	IWICBitmapFrameDecode* pWICFrame = NULL;
	IWICFormatConverter* pWICConverter = NULL;

	HRSRC hBitmapRes = NULL;
	HGLOBAL hResData = NULL;
	void* pBitmapRes = NULL;
	uint32_t bitmapMemSize = NULL;

	//get handles to resource by the given resource ID (e.g IDB_BITMAP1)
	hBitmapRes = FindResourceW(GetModuleHandle(NULL), MAKEINTRESOURCEW(resID), L"PNG");
	hr = hBitmapRes ? S_OK : E_FAIL;
	hResData = LoadResource(GetModuleHandle(NULL), hBitmapRes);
	hr = hResData ? S_OK : E_FAIL;
	pBitmapRes = LockResource(hResData);
	hr = pBitmapRes ? S_OK : E_FAIL;
	bitmapMemSize = SizeofResource(GetModuleHandle(NULL), hBitmapRes);
	hr = bitmapMemSize ? S_OK : E_FAIL;

	//create a WIC bitmap from the resource
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICFactory);
	hr = pWICFactory->CreateStream(&pWICStream);
	hr = pWICStream->InitializeFromMemory(reinterpret_cast<uint8_t*>(pBitmapRes), bitmapMemSize);
	hr = pWICFactory->CreateDecoderFromStream(pWICStream, NULL, WICDecodeMetadataCacheOnLoad, &pWICDecoder);
	hr = pWICDecoder->GetFrame(0, &pWICFrame);
	hr = pWICFactory->CreateFormatConverter(&pWICConverter);
	hr = pWICConverter->Initialize(pWICFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeMedianCut);

	//create a Direct2D-compatible bitmap from a WIC bitmap
	hr = m_pRenderTarget->CreateBitmapFromWicBitmap(pWICConverter, &pD2DBitmap);

	pWICStream->Release();
	pWICDecoder->Release();
	pWICFrame->Release();
	pWICConverter->Release();
	pWICFactory->Release();

	return hr;
}

void CD2DBitmap::DrawBitmap(const uint16_t &resID, float x, float y, float width, float height, float alpha)
{
	m_pD2DBitmap = GetBitmap(resID);
	m_pRenderTarget->DrawBitmap(m_pD2DBitmap, D2D1::RectF(x, y, x + width, y + height), alpha);
	/*if (m_pD2DBitmap != nullptr)
	{	
		m_pRenderTarget->DrawBitmap(m_pD2DBitmap, D2D1::RectF(x, y, x + width, y + height), alpha);
	}*/
}

void CD2DBitmap::GetBitmapSize(const uint16_t &resID, float &bmpW, float &bmpH)
{
	m_pD2DBitmap = GetBitmap(resID);
	D2D1_SIZE_F bmpSize = m_pD2DBitmap->GetSize();
	bmpW = bmpSize.width;
	bmpH = bmpSize.height;
}