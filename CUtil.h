#pragma once

namespace CUtil
{	
	void GetDesktopResolution(int& horizontal, int& vertical);
	RECT InitWinCoordinates(const DWORD& WinStyle, const bool& AdjClientArea);
	bool InitThreadVector(std::vector<std::shared_ptr<std::thread>>& vThreadPool);
};