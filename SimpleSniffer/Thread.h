#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

#define WM_TCATCH	WM_USER + 100
#define WM_TEXIT	WM_USER + 101

UINT ThreadProc(LPVOID param);

#endif
