#include "stdafx.h"
#include "SimpleSniffer.h"
#include "thread.h"
#include <pcap.h>

static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct pcap_pkthdr *new_header = new struct pcap_pkthdr;
	u_char *new_data = new u_char[header->len];

	if(param) // param 不是 NULL, 就存入文件
		pcap_dump(param, header, pkt_data);

	*new_header = *header;
	memcpy(new_data, pkt_data, header->len);
	::PostMessage(theApp.m_display, WM_TCATCH, (WPARAM)new_header, (LPARAM)new_data);
}

UINT ThreadProc(LPVOID param)
{
	ThreadParam *p = (ThreadParam*)param;

	int loopreturn = pcap_loop(p->m_dev, 0, packet_handler, (unsigned char*)p->m_dumper);
	delete p;

	::PostMessage(theApp.m_control, WM_TEXIT, loopreturn, NULL);

	return 0;
}
