#ifndef __SIMPLE_THREAD__
#define __SIMPLE_THREAD__

#define WM_TCATCH	WM_USER + 100
#define WM_TEXIT	WM_USER + 101

// 抓包线程的声明
UINT ThreadProc(LPVOID param);

#include <pcap.h>

// 封装传给线程的参数
class ThreadParam{
public:
	pcap_t *m_dev;			// 监听的网卡设备
	pcap_dumper_t *m_dumper;// 保存dump信息的文件

	ThreadParam(pcap_t *dev, pcap_dumper_t *dumper)
	{
		m_dev = dev;
		m_dumper = dumper;
	}
};

#endif
