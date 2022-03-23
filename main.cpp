#include "pch.h"
#include "main.h"

//Global variables
HWND hMainWnd = nullptr;
HINSTANCE hMainInst = nullptr;
RECT clRect = { 0 };
std::vector<std::shared_ptr<std::thread>> vThreadPool;		//main pool for all threads

CRenderProc* RenderProc;	//class for processing renderer messages

HRESULT InitApp()
{
	//COM initialization
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if FAILED(D2DUI::Get().Initialize(hMainWnd, clRect)) {
		return E_FAIL;
	}

	//Load the default script / level
	if (!CScriptProc::LoadInitialScript(new Script1()))
	{
		return E_FAIL;
	}
	RenderProc = new CRenderProc();		//Rendering methods
	return S_OK;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	switch (Msg) {

	case WM_CREATE: {
		srand(time(NULL));
		GetClientRect(hWnd, &clRect);		//store usable client area
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		DestroyWindow(hMainWnd);
		break;
	}

	}
	//hand off messages to the default Windows procedure
	return DefWindowProcW(hWnd, Msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow) {

	//initialize thread vector
	CUtil::InitThreadVector(vThreadPool);

	//store handle to instance of this app
	hMainInst = hInstance;

	//register windows class
	WNDCLASSEXW wc = {};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpszClassName = APP_WINCLASS;
	wc.lpfnWndProc = MainWndProc;
	wc.lpszMenuName = NULL;
	wc.hInstance = hMainInst;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	RegisterClassExW(&wc);

	//precalculate window position and size
	static RECT rWinCoords = CUtil::InitWinCoordinates(WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, TRUE);

	//create the window and process messages
	hMainWnd = CreateWindowExW(NULL, APP_WINCLASS, APP_WINNAME, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		rWinCoords.left, rWinCoords.top, rWinCoords.right, rWinCoords.bottom, NULL, NULL, hMainInst, NULL);

	if (!hMainWnd)
		return -1;
	
	//initialize default app things like Direct2D and default script
	if (FAILED(InitApp()))
		return -1;

	ShowWindow(hMainWnd, nCmdShow);

	MSG Msg;
	bool getResult;

	while ((getResult = GetMessageW(&Msg, NULL, 0, 0)) > 0) {
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}

	delete RenderProc;
	return 0;
}