// ehnd.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "ehnd.h"

FARPROC apfnEzt[100];
FARPROC apfnMsv[100];

bool EhndInit(void)
{
	// init
	pFilter = new filter();
	CreateLogWin(g_hInst);
	ShowLogWin(true);
	hook_wc2mb();
	hook_mb2wc();

	hook();
	hook_userdict();
	hook_userdict2();

	WriteLog(L"Hook Success.\n");

	pFilter->load();
	return true;
}

// 이지트랜스 API
__declspec(naked) void J2K_Initialize(void)
{
	__asm JMP apfnEzt[4 * 0];
}
void __stdcall J2K_InitializeEx(int data0, LPSTR key)
{
	EhndInit();
	SetLogText(L"J2K_InitializeEx.\n");
	__asm
	{
		PUSH DWORD PTR DS : [key]
		PUSH data0
		CALL apfnEzt[4 * 1]
	}
}
__declspec(naked) void J2K_FreeMem(void)
{
	__asm JMP apfnEzt[4 * 2];
}
__declspec(naked) void J2K_GetPriorDict(void)
{
	__asm JMP apfnEzt[4 * 3];
}
__declspec(naked) void J2K_GetProperty(void)
{
	__asm JMP apfnEzt[4 * 4];
}
void __stdcall J2K_ReloadUserDict(void)
{
	pFilter->load();
	__asm CALL apfnEzt[4 * 5];
	return;
}
__declspec(naked) void J2K_SetDelJPN(void)
{
	__asm JMP apfnEzt[4 * 6];
}
__declspec(naked) void J2K_SetField(void)
{
	__asm JMP apfnEzt[4 * 7];
}
__declspec(naked) void J2K_SetHnj2han(void)
{
	__asm JMP apfnEzt[4 * 8];
}
__declspec(naked) void J2K_SetJWin(void)
{
	__asm JMP apfnEzt[4 * 9];
}
__declspec(naked) void J2K_SetPriorDict(void)
{
	__asm JMP apfnEzt[4 * 10];
}
__declspec(naked) void J2K_SetProperty(void)
{
	__asm JMP apfnEzt[4 * 11];
}
__declspec(naked) void J2K_StopTranslation(void)
{
	__asm JMP apfnEzt[4 * 12];
}
__declspec(naked) void J2K_Terminate(void)
{
	__asm JMP apfnEzt[4 * 13];
}
__declspec(naked) void J2K_TranslateChat(void)
{
	__asm JMP apfnEzt[4 * 14];
}
__declspec(naked) void J2K_TranslateFM(void)
{
	__asm JMP apfnEzt[4 * 15];
}
__declspec(naked) void J2K_TranslateMM(void)
{
	__asm JMP apfnEzt[4 * 16];
}
__declspec(naked) void J2K_TranslateMMEx(void)
{
	__asm JMP apfnEzt[4 * 17];
}
__declspec(naked) void *msvcrt_free(void *_Memory)
{
	__asm JMP apfnMsv[4 * 0];
}
__declspec(naked) void *msvcrt_malloc(size_t _Size)
{
	__asm JMP apfnMsv[4 * 1];
}
__declspec(naked) void *msvcrt_fopen(char *path, char *mode)
{
	__asm JMP apfnMsv[4 * 2];
}
void *__stdcall J2K_TranslateMMNT(int data0, LPSTR szIn)
{
	LPSTR szOut;
	wstring wsText, wsOriginal, wsLog;
	int i_len;
	LPWSTR lpJPN, lpKOR;
	LPSTR szJPN, szKOR;
	i_len = _MultiByteToWideChar(932, MB_PRECOMPOSED, szIn, -1, NULL, NULL);
	lpJPN = (LPWSTR)msvcrt_malloc((i_len + 1) * 3);
	if (lpJPN == NULL)
	{
		SetLogText(L"memory allocation error.\n");
		return 0;
	}
	_MultiByteToWideChar(932, 0, szIn, -1, lpJPN, i_len);

	wsOriginal = lpJPN;
	wsText = lpJPN;
	msvcrt_free(lpJPN);

	wsLog = replace_all(wsText, L"%", L"%%");
	wsLog = replace_all(wsText, L"%", L"%%");
	WriteLog(L"[REQUEST] %s\n\n", wsLog.c_str());

	// 넘어온 문자열의 길이가 0이거나 명령어일때 번역 프로세스 스킵
	if (wcslen(lpJPN) && !pFilter->cmd(wsText))
	{
		wsLog = wsText;
		wsLog = replace_all(wsLog, L"%", L"%%");
		wsLog = replace_all(wsLog, L"\t", L" ");
		wsLog = replace_all(wsLog, L"\r\n", L"");
		WriteTextLog(L"%s\t", wsLog.c_str());

		pFilter->pre(wsText);

		wsLog = replace_all(wsText, L"%", L"%%");
		WriteLog(L"[PRE] %s\n\n", wsLog.c_str());

		i_len = _WideCharToMultiByte(932, 0, wsText.c_str(), -1, NULL, NULL, NULL, NULL);
		szJPN = (LPSTR)msvcrt_malloc((i_len + 1) * 3);
		if (szJPN == NULL)
		{
			SetLogText(L"memory allocation error.\n");
			return 0;
		}
		_WideCharToMultiByte(932, 0, wsText.c_str(), -1, szJPN, i_len, NULL, NULL);

		__asm
		{
			PUSH DWORD PTR DS : [szJPN]
			PUSH data0
			CALL apfnEzt[4 * 18]
			MOV DWORD PTR DS : [szKOR], EAX
		}

		msvcrt_free(szJPN);

		i_len = _MultiByteToWideChar(949, MB_PRECOMPOSED, szKOR, -1, NULL, NULL);
		lpKOR = (LPWSTR)msvcrt_malloc((i_len + 1) * 3);
		if (lpKOR == NULL)
		{
			SetLogText(L"memory allocation error.\n");
			return 0;
		}
		_MultiByteToWideChar(949, 0, szKOR, -1, lpKOR, i_len);

		wsText = lpKOR;
		msvcrt_free(szKOR);
		msvcrt_free(lpKOR);

		wsLog = replace_all(wsText, L"%", L"%%");
		WriteLog(L"[TRANS] %s\n\n", wsLog.c_str());

		pFilter->post(wsText);

		wsLog = replace_all(wsText, L"%", L"%%");
		WriteLog(L"[POST] %s\n\n", wsLog.c_str());

		wsLog = wsText;
		wsLog = replace_all(wsLog, L"%", L"%%");
		wsLog = replace_all(wsLog, L"\t", L" ");
		wsLog = replace_all(wsLog, L"\r\n", L"");
		WriteTextLog(L"%s\r\n", wsLog.c_str());
	}

	i_len = _WideCharToMultiByte(949, 0, wsText.c_str(), -1, NULL, NULL, NULL, NULL);
	szOut = (LPSTR)msvcrt_malloc((i_len + 1) * 3);
	if (szOut == NULL)
	{
		SetLogText(L"memory allocation error.\n");
		return 0;
	}
	_WideCharToMultiByte(949, 0, wsText.c_str(), -1, szOut, i_len, NULL, NULL);
	return (void *)szOut;
}
__declspec(naked) void J2K_GetJ2KMainDir(void)
{
	__asm JMP apfnEzt[4 * 19];
}

bool GetLoadPath(LPWSTR Path, int Size)
{
	GetModuleFileName(g_hInst, Path, Size);
	if (Path[0] == 0) return false;
	int i = wcslen(Path);
	while (i--)
	{
		if (Path[i] == L'\\')
		{
			Path[i] = 0;
			break;
		}
	}
	return true;
}

wstring replace_all(const wstring &str, const wstring &pattern, const wstring &replace)
{
	wstring result = str;
	wstring::size_type pos = 0, offset = 0;

	while ((pos = result.find(pattern, offset)) != wstring::npos)
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);
		offset = pos + replace.size();
	}
	return result;
}