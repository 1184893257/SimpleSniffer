#ifndef __MY_INFO__
#define __MY_INFO__
#include "Head.h"

// 保存了抓到的一个包的所有信息
class Info{
public:
	struct pcap_pkthdr *header;	//抓包所得数据包一些信息（时间、长度）
	u_char *pkt_data;			//抓包所得数据包内容头指针
	//u_char *information;		//数据内容的首地址
	//int len;					//数据内容的长度
	Head_Super* m_Head;			//最底层协议的PDU
};

#endif