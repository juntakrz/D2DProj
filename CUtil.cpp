#include "pch.h"
#include "CUtil.h"

void CUtil::GetDesktopResolution(int &horizontal, int &vertical)
{
	//variable to store monitor dimensions
	RECT desktop;

	//get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();

	//move desktop coordinates into RECT variable
	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;

}

RECT CUtil::InitWinCoordinates(const DWORD& WinStyle, const bool& AdjClientArea)
{

	RECT rFullWin = { 0, 0, APP_MAINRESX, APP_MAINRESY };
	if (AdjClientArea) AdjustWindowRectEx(&rFullWin, WinStyle, false, 0);	//either client area or full window will be of app size
	int initPosX, initPosY;
	int winResX = rFullWin.right - rFullWin.left, winResY = rFullWin.bottom - rFullWin.top;	//variables for window resolution
	GetDesktopResolution(initPosX, initPosY);
	initPosX = (initPosX / 2) - (winResX / 2);			//create window in the center of the desktop
	initPosY = (initPosY / 2) - (winResY / 2);

	return rFullWin = { initPosX, initPosY, winResX, winResY };		//x, y, w, h

}

bool CUtil::InitThreadVector(std::vector<std::shared_ptr<std::thread>>& vThreadPool)
{
	vThreadPool = {
		NULL,				//0 = used by the main update thread in CRenderProc
		NULL,				//1 = used by the main render thread in CRenderProc
		NULL,				//2 = used by the mouse tracking thread
		NULL,				//3
		NULL				//4
	};
	return true;
}