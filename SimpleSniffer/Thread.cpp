#include "stdafx.h"
#include "thread.h"
#include <pcap.h>

static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	::PostMessage(::AfxGetApp()->m_pMainWnd->m_hWnd, WM_TCATCH, (WPARAM)header, (LPARAM)pkt_data);
}

UINT ThreadProc(LPVOID param)
{
	pcap_t *adhandle=(pcap_t *)param;

	int loopreturn = pcap_loop(adhandle, 0, packet_handler, NULL);

	::PostMessage(::AfxGetApp()->m_pMainWnd->m_hWnd, WM_TEXIT, loopreturn, NULL);

	return 0;
}
