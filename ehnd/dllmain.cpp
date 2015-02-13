// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"
HINSTANCE g_hInst;
Cehnd *pEhnd;

BOOL APIENTRY DllMain(HINSTANCE hInstance,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		pEhnd = new Cehnd();
		CreateLogWin(g_hInst);
		ShowLogWin(true);
		SetLogText(L"Log Start.\n", RGB(0, 0, 0), RGB(255, 255, 255));
		g_hInst = hInstance;
		hook();

		SetLogText(L"Hook Success.\n", RGB(0, 0, 0), RGB(255, 255, 255));
	}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		delete pEhnd;
		break;
	}
	return TRUE;
}

