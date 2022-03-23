#pragma once

#include "D2DUI.h"

#include "resource.h"

#include "CRenderProc.h"
#include "CScriptProc.h"
#include "Script1.h"

//main.cpp
extern HWND hMainWnd;

extern std::vector<std::shared_ptr<std::thread>> vThreadPool;