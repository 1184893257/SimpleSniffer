#ifndef __MY_INFO__
#define __MY_INFO__

class Info{
public:
	struct pcap_pkthdr *header;	//ץ���������ݰ�һЩ��Ϣ��ʱ�䡢���ȣ�
	u_char *pkt_data;			//ץ���������ݰ�����ͷָ��
	u_char *information;		//�������ݵ��׵�ַ
	int len;					//�������ݵĳ���
};

#endif