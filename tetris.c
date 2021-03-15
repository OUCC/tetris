/***

tetris v1.0
Copyright (C) 2021 Yuri213212
Site:https://github.com/Yuri213212/tetris
Email: yuri213212@vip.qq.com
License: CC BY-NC-SA 4.0
https://creativecommons.org/licenses/by-nc-sa/4.0/

***/

#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <commctrl.h>

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// Workaround for wrong macro definitions in CeGCC.
#ifdef UNDER_CE
#if SW_MAXIMIZE != 12
#undef SW_MAXIMIZE
#define SW_MAXIMIZE 12
#endif
#if SW_MINIMIZE != 6
#undef SW_MINIMIZE
#define SW_MINIMIZE 6
#endif
#if WS_MINIMIZEBOX != 0x00010000L
#undef WS_MINIMIZEBOX
#define WS_MINIMIZEBOX 0x00010000L
#endif
#if WS_MAXIMIZEBOX != 0x00020000L
#undef WS_MAXIMIZEBOX
#define WS_MAXIMIZEBOX 0x00020000L
#endif
#endif

#ifdef LANG_CH
#ifdef NOUTF8
#include "lang-ch/tetris_ui_gb2312.h"
#include "lang-ch/tetris_help_gb2312.h"
#include "lang-ch/resource_gb2312.h"
#else
#include "lang-ch/tetris_ui.h"
#include "lang-ch/tetris_help.h"
#include "lang-ch/resource.h"
#endif
#elif defined LANG_JP
#ifdef NOUTF8
#include "lang-jp/tetris_ui_sjis.h"
#include "lang-jp/tetris_help_sjis.h"
#include "lang-jp/resource_sjis.h"
#else
#include "lang-jp/tetris_ui.h"
#include "lang-jp/tetris_help.h"
#include "lang-jp/resource.h"
#endif
#else
#include "lang/tetris_ui.h"
#include "lang/tetris_help.h"
#include "lang/resource.h"
#endif

#define tbuflen		1024
#define clwidth		288
#define clheight	370
#define SampleRate	44100
#define BufferLength	(SampleRate/15)	//15fps

wchar_t wbuf[tbuflen];
int cxScreen,cyScreen,width,height,vol;
#ifdef UNDER_CE
HWND hCmdBar;
int cmdBarHeight;
#endif
HINSTANCE hInst;
HDC hdcMem;
HBRUSH hBrushBg,hBrushRed,hBrushOrange,hBrushYellow,hBrushGreen,hBrushCyan,hBrushBlue,hBrushPurple;
RECT bgRect={0,0,clwidth,clheight},rect={199,0,279,0};
short outBuffer[2][BufferLength]={0};
WAVEHDR WaveHdr[2]={
	{(LPSTR)outBuffer[0],BufferLength*2,0,0,0,0,0,0},
	{(LPSTR)outBuffer[1],BufferLength*2,0,0,0,0,0,0}
};
WAVEFORMATEX waveformat={WAVE_FORMAT_PCM,1,SampleRate,SampleRate*2,2,16,0};

#ifdef UNDER_CE
#define myDefWindowProc DefWindowProcW  // WinCE doesn't have the bug
#else
#include "defproc.h"
#include "drawicon.h"
#endif
#include "sound.h"
#include "board.h"

#ifdef UNDER_CE
int myMessageBox(HWND hWnd, HINSTANCE hInst, const wchar_t *lpText, const wchar_t *lpCaption, unsigned uType) {
  UNREFERENCED_PARAMETER(hInst);
  return MessageBoxW(hWnd, lpText, lpCaption, uType);
}
#else
// The function pointer type for TaskDialog API.
typedef HRESULT(__stdcall *TaskDialog_t)(HWND hwndOwner, HINSTANCE hInstance, const wchar_t *pszWindowTitle,
                                         const wchar_t *pszMainInstruction, const wchar_t *pszContent,
                                         int dwCommonButtons, const wchar_t *pszIcon, int *pnButton);

int myMessageBox(HWND hWnd, HINSTANCE hInst, const wchar_t *lpText, const wchar_t *lpCaption, unsigned uType) {
  // Tests whether uType uses some features that TaskDialog doesn't support.
  if (uType & ~(MB_ICONMASK | MB_TYPEMASK)) goto mbfallback;

  int buttons;
  switch (uType & MB_TYPEMASK) {
    case MB_OK:
      buttons = 1;
      break;
    case MB_OKCANCEL:
      buttons = 1 + 8;
      break;
    case MB_RETRYCANCEL:
      buttons = 16 + 8;
      break;
    case MB_YESNO:
      buttons = 2 + 4;
      break;
    case MB_YESNOCANCEL:
      buttons = 2 + 4 + 8;
      break;
    default:  // Not supported by TaskDialog.
      goto mbfallback;
  }

  wchar_t *icon;
  switch (uType & MB_ICONMASK) {
    case 0:
      icon = NULL;
      break;
    case MB_ICONWARNING:  // Same value as MB_ICONEXCLAMATION.
      icon = MAKEINTRESOURCEW(-1);
      break;
    case MB_ICONERROR:  // Same value as MB_ICONSTOP and MB_ICONHAND.
      icon = MAKEINTRESOURCEW(-2);
      break;
    default:  // Substitute anything else for the information icon.
      icon = MAKEINTRESOURCEW(-3);
  }

  {
    // Tries to load the TaskDialog API which is a newer substitite of MessageBoxW.
    // This API is per monitor DPI aware but doesn't exist before Windows Vista.
    // To make the system select version 6 comctl32.dll, we don't use the full path here.
    HMODULE comctl32 = LoadLibraryW(L"comctl32.dll");
    if (!comctl32) goto mbfallback;

    TaskDialog_t taskDialog = (TaskDialog_t)(void *)GetProcAddress(comctl32, "TaskDialog");
    if (!taskDialog) {
      FreeLibrary(comctl32);
      goto mbfallback;
    }

    int result;
    taskDialog(hWnd, hInst, lpCaption, L"", lpText, buttons, icon, &result);
    FreeLibrary(comctl32);
    return result;
  }

mbfallback:
  return MessageBoxW(hWnd, lpText, lpCaption, uType);
}
#endif

void dotmain(HDC hdc,int x,int y){
	Rectangle(hdcMem,x*18+6,348-y*18,x*18+23,365-y*18);
	SelectObject(hdcMem,GetStockObject(GRAY_BRUSH));
	Rectangle(hdcMem,x*18+10,352-y*18,x*18+19,361-y*18);
}

void dotnext(HDC hdc,int x,int y){
	Rectangle(hdcMem,x*18+204,96-y*18,x*18+221,113-y*18);
	SelectObject(hdcMem,GetStockObject(GRAY_BRUSH));
	Rectangle(hdcMem,x*18+208,100-y*18,x*18+217,109-y*18);
}

void redraw(){
	int i,j,temp;

	FillRect(hdcMem,&bgRect,hBrushBg);
	wsprintfW(wbuf,L"%d",score);
	rect.top=186;
	rect.bottom=202;
	DrawTextW(hdcMem,wbuf,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_RIGHT|DT_VCENTER);
	rect.top=240;
	rect.bottom=256;
	DrawTextW(hdcMem,szUI_Modes[mode],-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	wsprintfW(wbuf,L"%d",level);
	rect.top=294;
	rect.bottom=310;
	DrawTextW(hdcMem,wbuf,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_RIGHT|DT_VCENTER);
	if (pause){
		rect.top=348;
		rect.bottom=364;
		DrawTextW(hdcMem,szMenu_Pause,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	}
	for (i=2;i<22;++i){
		for (j=4;j<14;++j){
			if ((fullline&1)&&(fullline&(1<<i))) continue;
			if (board[i]&(1<<j)){
				SelectObject(hdcMem,hBrushRed);
				dotmain(hdcMem,j-4,i-2);
			}
		}
	}
	if (gameover>0){
		if (gameover<20){
			temp=gameover+2;
		}else{
			temp=42-gameover;
		}
		for (i=2;i<temp;++i){
			for (j=4;j<14;++j){
				SelectObject(hdcMem,hBrushRed);
				dotmain(hdcMem,j-4,i-2);
			}
		}
	}
	if (next>=0){
		for (i=0;i<4;++i){
			for (j=0;j<4;++j){
				if (piece[next*4+i]&(1<<j)){
					switch (next>>2){
					case 15:
					case 14:
					case 13:
						SelectObject(hdcMem,hBrushPurple);
						break;
					case 12:
						SelectObject(hdcMem,hBrushGreen);
						break;
					default:
						SelectObject(hdcMem,hBrushBlue);
						break;
					}
					dotnext(hdcMem,j,i);
				}
			}
		}
	}
	if (bulletRowD>=1&&bulletRowD<21){
		SelectObject(hdcMem,hBrushCyan);
		dotmain(hdcMem,bulletShiftD-3,bulletRowD-1);
	}
	if (bulletRowA>=1&&bulletRowA<21){
		SelectObject(hdcMem,GetStockObject(BLACK_BRUSH));
		dotmain(hdcMem,bulletShiftA-3,bulletRowA-1);
	}
	if (current>=0){
		for (i=0;i<4;++i){
			if (i+row>=22) continue;
			if (i+row<2) continue;
			for (j=0;j<4;++j){
				if (piece[current*4+i]&(1<<j)){
					switch (current>>2){
					case 16:
						SelectObject(hdcMem,hBrushOrange);
						break;
					case 15:
					case 14:
					case 13:
						SelectObject(hdcMem,hBrushPurple);
						break;
					case 12:
						if (board_hittest(current,row,shift)){
							SelectObject(hdcMem,hBrushYellow);
						}else{
							SelectObject(hdcMem,hBrushGreen);
						}
						break;
					default:
						SelectObject(hdcMem,hBrushBlue);
						break;
					}
					dotmain(hdcMem,j+shift-4,i+row-2);
				}
			}
		}
	}
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){
	static int endflag=0;
	static HWAVEOUT hwo=NULL;
	static HBITMAP hBitmap;

	HDC hdc;

	switch (message){
	case WM_CREATE: {
	  SCROLLINFO vsi={sizeof(SCROLLINFO),SIF_DISABLENOSCROLL|SIF_PAGE|SIF_POS|SIF_RANGE,0,271,16,0,0};

		InitCommonControls();
#ifdef UNDER_CE
		hCmdBar=CommandBar_Create(hInst,hwnd,1);
		CommandBar_InsertMenubarEx(hCmdBar,hInst,TEXT("menu"),0);
		CommandBar_Show(hCmdBar,TRUE);
		cmdBarHeight=CommandBar_Height(hCmdBar);
		height=clheight+GetSystemMetrics(SM_CYCAPTION)+cmdBarHeight+2;
		MoveWindow(hwnd,(cxScreen-width)/2,(cyScreen-height)/2,width,height,TRUE);
		vol=0;
#else
		vol=64;
#endif
		hBrushRed=CreateSolidBrush(RGB(255,0,0));
		hBrushOrange=CreateSolidBrush(RGB(255,128,0));
		hBrushYellow=CreateSolidBrush(RGB(255,255,0));
		hBrushGreen=CreateSolidBrush(RGB(0,255,0));
		hBrushCyan=CreateSolidBrush(RGB(0,255,255));
		hBrushBlue=CreateSolidBrush(RGB(0,0,255));
		hBrushPurple=CreateSolidBrush(RGB(128,0,255));
		hdc=GetDC(NULL);
		hdcMem=CreateCompatibleDC(hdc);
		hBitmap=CreateCompatibleBitmap(hdc,clwidth,clheight);
		ReleaseDC(NULL,hdc);
		SelectObject(hdcMem,hBitmap);
		FillRect(hdcMem,&bgRect,GetStockObject(WHITE_BRUSH));
		SelectObject(hdcMem,GetStockObject(NULL_PEN));
		SelectObject(hdcMem,GetStockObject(BLACK_BRUSH));
		Rectangle(hdcMem,0,0,191,371);
		Rectangle(hdcMem,198,36,281,119);
		SelectObject(hdcMem,GetStockObject(WHITE_BRUSH));
		Rectangle(hdcMem,4,4,187,367);
		Rectangle(hdcMem,202,40,277,115);
#ifdef SYSTEM_FIXED_FONT
		SelectObject(hdcMem,GetStockObject(SYSTEM_FIXED_FONT));
#else
		SelectObject(hdcMem,GetStockObject(SYSTEM_FONT));
#endif
		SetBkMode(hdcMem,TRANSPARENT);
		SetTextColor(hdcMem,RGB(0,0,0));
		rect.top=6;
		rect.bottom=22;
		DrawTextW(hdcMem,szUI_Next,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		rect.top=168;
		rect.bottom=184;
		DrawTextW(hdcMem,szUI_Score,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		rect.top=222;
		rect.bottom=238;
		DrawTextW(hdcMem,szUI_Mode,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		rect.top=276;
		rect.bottom=292;
		DrawTextW(hdcMem,szUI_Level,-1,&rect,DT_NOPREFIX|DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		hBrushBg=CreatePatternBrush(hBitmap);
	  vsi.nPos=256-vol;
		SetScrollInfo(hwnd,SB_VERT,&vsi,TRUE);
		SendMessageW(hwnd,WM_COMMAND,IDM_RESET,0);
		if (waveOutOpen(&hwo,WAVE_MAPPER,&waveformat,(DWORD_PTR)hwnd,0,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
			myMessageBox(NULL,hInst,szErr_AudioDevice,szTitle,MB_ICONERROR);
			DestroyWindow(hwnd);
			return 0;
		}
		waveOutPrepareHeader(hwo,&WaveHdr[0],sizeof(WAVEHDR));
		waveOutPrepareHeader(hwo,&WaveHdr[1],sizeof(WAVEHDR));
#ifdef UNDER_CE  // Prevents a system freeze on WinCE devices
		SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_BELOW_NORMAL);
#else
		SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);
#endif
		return 0;
	}
#ifndef UNDER_CE
	case WM_ERASEBKGND:
		return TRUE;
#endif
	case WM_PAINT: {
#ifdef UNDER_CE
		PAINTSTRUCT ps;
    hdc=BeginPaint(hwnd, &ps);
		redraw();
		BitBlt(hdc,0,cmdBarHeight,clwidth,clheight,hdcMem,0,0,SRCCOPY);
		EndPaint(hwnd, &ps);
#else
		redraw();
		hdc=GetDC(hwnd);
		BitBlt(hdc,0,0,clwidth,clheight,hdcMem,0,0,SRCCOPY);
		ReleaseDC(hwnd,hdc);
		ValidateRect(hwnd,NULL);
#endif
		return 0;
		}
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam)<0){
			vol-=16;
		}else{
			vol+=16;
		}
		if (vol>256){
			vol=256;
		}
		if (vol<0){
			vol=0;
		}
		SetScrollPos(hwnd,SB_VERT,256-vol,TRUE);
		return 0;
	case WM_VSCROLL:
		switch(LOWORD(wParam)){
		case SB_TOP:
			vol=256;
			break;
		case SB_BOTTOM:
			vol=0;
			break;
		case SB_LINEUP:
			vol+=1;
			break;
		case SB_PAGEUP:
			vol+=16;
			break;
		case SB_LINEDOWN:
			vol-=1;
			break;
		case SB_PAGEDOWN:
			vol-=16;
			break;
		case SB_THUMBTRACK:
			vol=256-HIWORD(wParam);
			break;
		default:
			return 0;
		}
		if (vol>256){
			vol=256;
		}
		if (vol<0){
			vol=0;
		}
		SetScrollPos(hwnd,SB_VERT,256-vol,TRUE);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case IDM_RESET:
			sound_init();
			board_init();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case IDM_START:
			board_newgame();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case IDM_PAUSE:
			pause^=1;
			sound_event(ST_pause);
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case IDM_HELP:
			pause|=2;
			InvalidateRect(hwnd,NULL,FALSE);
			myMessageBox(hwnd,hInst,szHelp,szTitle,MB_ICONINFORMATION);
			pause&=~2;
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam){
		case VK_LEFT:
			board_left();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case VK_RIGHT:
			board_right();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case VK_UP:
			board_rotate();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case VK_DOWN:
			board_accelerate();
			InvalidateRect(hwnd,NULL,FALSE);
			return 0;
		case VK_PRIOR://Page Up
			SendMessageW(hwnd,WM_VSCROLL,SB_PAGEUP,0);
			return 0;
		case VK_NEXT://Page Down
			SendMessageW(hwnd,WM_VSCROLL,SB_PAGEDOWN,0);
			return 0;
		case VK_HOME:
			SendMessageW(hwnd,WM_VSCROLL,SB_TOP,0);
			return 0;
		case VK_END:
			SendMessageW(hwnd,WM_VSCROLL,SB_BOTTOM,0);
			return 0;
		case VK_RETURN://Enter
			SendMessageW(hwnd,WM_COMMAND,IDM_START,0);
			return 0;
		case VK_ESCAPE://Esc
			SendMessageW(hwnd,WM_COMMAND,IDM_RESET,0);
			return 0;
		case L' ':
			SendMessageW(hwnd,WM_COMMAND,IDM_PAUSE,0);
			return 0;
		default:
			return 0;
		}
		return 0;
	case MM_WOM_OPEN:
		waveOutWrite(hwo,&WaveHdr[0],sizeof(WAVEHDR));
		waveOutWrite(hwo,&WaveHdr[1],sizeof(WAVEHDR));
		return 0;
	case MM_WOM_DONE:
		if (endflag){
			waveOutClose(hwo);
		}else{
			FillBuffer((short *)((PWAVEHDR)lParam)->lpData);
			waveOutWrite(hwo,(PWAVEHDR)lParam,sizeof(WAVEHDR));
			board_next();
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return 0;
	case MM_WOM_CLOSE:
		waveOutUnprepareHeader(hwo,&WaveHdr[0],sizeof(WAVEHDR));
		waveOutUnprepareHeader(hwo,&WaveHdr[1],sizeof(WAVEHDR));
		DestroyWindow(hwnd);
		return 0;
	case WM_CLOSE:
		endflag=1;
		waveOutReset(hwo);
		return 0;
	case WM_DESTROY:
#ifndef UNDER_CE
		SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
#endif
		KillTimer(hwnd,1);
		DeleteObject(hBrushBg);
		DeleteObject(hBrushRed);
		DeleteObject(hBrushOrange);
		DeleteObject(hBrushYellow);
		DeleteObject(hBrushGreen);
		DeleteObject(hBrushCyan);
		DeleteObject(hBrushBlue);
		DeleteObject(hBrushPurple);
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return myDefWindowProc(hwnd,message,wParam,lParam);
}

#ifdef UNDER_CE
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,wchar_t *lpCmdLine,int iCmdShow){
	WNDCLASSW wndclass;
	HWND hwnd;
	MSG msg;
	LARGE_INTEGER l;

	hInst=hInstance;
#else
int main(){
	int argc;
	wchar_t **argv;
	int iCmdShow;
	STARTUPINFOW si;

	WNDCLASSW wndclass;
	HWND hwnd;
	HICON hIcon;
	MSG msg;
	LARGE_INTEGER l;

	argv=CommandLineToArgvW(GetCommandLineW(),&argc);
	hInst=GetModuleHandleW(NULL);
	GetStartupInfoW(&si);
	iCmdShow=si.dwFlags&STARTF_USESHOWWINDOW?si.wShowWindow:SW_SHOWNORMAL;
	hIcon=drawIcon();
#endif

	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc=WndProc;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hInstance=hInst;
#ifdef UNDER_CE
	wndclass.hIcon=NULL;
	wndclass.hCursor=NULL;
	wndclass.lpszMenuName=NULL;
#else
	wndclass.hIcon=hIcon;
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.lpszMenuName=L"menu";
#endif
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName=szAppName;
	if (!RegisterClassW(&wndclass)){
#ifdef UNDER_CE
		myMessageBox(NULL,hInst,szErr_RegisterClass,szAppName,MB_ICONERROR);
#else
		myMessageBox(NULL,hInst,szErr_RegisterClass,argv[0],MB_ICONERROR);
		DestroyIcon(hIcon);
#endif
		return 0;
	}

	QueryPerformanceCounter(&l);
	srand(l.LowPart%RAND_MAX+1);
	cxScreen=GetSystemMetrics(SM_CXSCREEN);
	cyScreen=GetSystemMetrics(SM_CYSCREEN);
#ifdef UNDER_CE
	width=clwidth+GetSystemMetrics(SM_CXVSCROLL);
	height=clheight+GetSystemMetrics(SM_CYCAPTION)+24;  // 24 is the temporal command bar height, which will be corrected on WM_CREATE.
#else
	width=clwidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2+GetSystemMetrics(SM_CXVSCROLL);
	height=clheight+GetSystemMetrics(SM_CYFIXEDFRAME)*2+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYMENU);
#endif
	hwnd=CreateWindowW(szAppName,szTitle,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_VSCROLL,(cxScreen-width)/2,(cyScreen-height)/2,width,height,NULL,NULL,hInst,NULL);
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);
	while (GetMessageW(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

#ifndef UNDER_CE
	DestroyIcon(hIcon);
	LocalFree(argv);
#endif

	return (int)msg.wParam;
}
