#include "stdafx.h"
#include "SimpleSniffer.h"
#include "thread.h"
#include <pcap.h>

// pcap_loop ����һ�����󽫰����ݸ���һ�� �� ����WM_TCATCH��Ϣ
static void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct pcap_pkthdr *new_header = new struct pcap_pkthdr;
	u_char *new_data = new u_char[header->len];

	if(param) // param ���� NULL, �ʹ����ļ�
		pcap_dump(param, header, pkt_data);

	// ��������, ������Ϣ
	*new_header = *header;
	memcpy(new_data, pkt_data, header->len);
	::PostMessage(theApp.m_display, WM_TCATCH, (WPARAM)new_header, (LPARAM)new_data);
}

// ץ���̵߳�ʵ��
UINT ThreadProc(LPVOID param)
{
	ThreadParam *p = (ThreadParam*)param;

	// ѭ�������, ѭ�����Ա� pcap_breakloop ��ֹ
	int loopreturn = pcap_loop(p->m_dev, 0, packet_handler, (unsigned char*)p->m_dumper);
	delete p;

	// �˳�ǰ���� WM_TEXIT ��Ϣ
	::PostMessage(theApp.m_control, WM_TEXIT, loopreturn, NULL);

	return 0;
}
