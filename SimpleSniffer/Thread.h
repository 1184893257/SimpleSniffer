#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

#define WM_TCATCH	WM_USER + 100
#define WM_TEXIT	WM_USER + 101

// ץ���̵߳�����
UINT ThreadProc(LPVOID param);

#include <pcap.h>

// ��װ�����̵߳Ĳ���
class ThreadParam{
public:
	pcap_t *m_dev;			// �����������豸
	pcap_dumper_t *m_dumper;// ����dump��Ϣ���ļ�

	ThreadParam(pcap_t *dev, pcap_dumper_t *dumper)
	{
		m_dev = dev;
		m_dumper = dumper;
	}
};

#endif
