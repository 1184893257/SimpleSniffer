#ifndef __MY_INFO__
#define __MY_INFO__
#include "Head.h"

// ������ץ����һ������������Ϣ
class Info{
public:
	struct pcap_pkthdr *header;	//ץ���������ݰ�һЩ��Ϣ��ʱ�䡢���ȣ�
	u_char *pkt_data;			//ץ���������ݰ�����ͷָ��
	//u_char *information;		//�������ݵ��׵�ַ
	//int len;					//�������ݵĳ���
	Head_Super* m_Head;			//��ײ�Э���PDU
};

#endif