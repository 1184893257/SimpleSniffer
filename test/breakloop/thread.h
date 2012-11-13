#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

#define WM_TCATCH	WM_USER + 0
#define WM_TEXIT	WM_USER + 1

UINT ThreadProc(LPVOID param);

#endif
