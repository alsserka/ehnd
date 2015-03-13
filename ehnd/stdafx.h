// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define EHND_VER "V3.00.150219"
// Windows 헤더 파일:
#include <windows.h>
#include <WinBase.h>
#include <windef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <Psapi.h>

#include <iostream>
#include <vector>
#include <regex>

using namespace std;
#define PREFILTER 1
#define POSTFILTER 2

#define NORMAL_LOG 0
#define DETAIL_LOG 10
#define TIME_LOG 20
#define SKIPLAYER_LOG 30

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "ehnd.h"
#include "hook.h"
#include "log.h"
#include "filter.h"
#include "watch.h"
#include "config.h"

extern HINSTANCE g_hInst;
extern filter *pFilter;
extern watch *pWatch;
extern config *pConfig;
extern int g_initTick;
extern char g_DicPath[MAX_PATH];

extern LPBYTE lpfnRetn;
extern LPBYTE lpfnfopen;
extern LPBYTE lpfnwc2mb;
extern LPBYTE lpfnmb2wc;
extern HMODULE hEzt, hMsv;

#ifdef _UNICODE
#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#else
#define WIDEN(x)
#endif