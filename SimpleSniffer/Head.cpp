#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "Head.h"

using namespace std;

const CString sign_ip="0800";
const CString sign_arp="0806";

void Head_Ethernet::analysis(u_char *pkt_data)
{
	CString m_kind;

	memcpy(D_Mac,pkt_data,6);
	memcpy(S_Mac,pkt_data+6,6);
	memcpy(kind,pkt_data+12,2);
	m_kind.Format("%02X%02X",kind[0],kind[1]);
	//判断下一层协议
	if(m_kind.Compare(sign_ip) == 0)
	{
		next=new Head_IP();
		next->analysis(pkt_data+14);
	}
	else if(m_kind.Compare(sign_arp) == 0)
	{
		next=new Head_ARP();
		next->analysis(pkt_data+14);
	}
	else
	{
		next=NULL;
	}
}

void Head_Ethernet::my_print()
{

}

void Head_802_3::analysis(u_char *pkt_data)
{
	CString m_kind;

	memcpy(D_Mac,pkt_data,6);
	memcpy(S_Mac,pkt_data+6,6);
	memcpy(kind,pkt_data+20,2);
	m_kind.Format("%02X%02X",kind[0],kind[1]);
	//判断下一层协议
	if(m_kind.Compare(sign_ip) == 0)
	{
		next=new Head_IP();
		next->analysis(pkt_data+22);
	}
	else if(m_kind.Compare(sign_arp) == 0)
	{
		next=new Head_ARP();
		next->analysis(pkt_data+22);
	}
	else
	{
		next=NULL;
	}
}

void Head_802_3::my_print()
{

}

void Head_ARP::analysis(u_char *pkt_data)
{
	memcpy(op,pkt_data+6,2);
	memcpy(S_Mac,pkt_data+8,6);
	memcpy(S_IP,pkt_data+14,4);
	memcpy(D_Mac,pkt_data+18,6);
	memcpy(D_IP,pkt_data+24,4);

	next=NULL;						//ARP就到头了
}

void Head_ARP::my_print()
{

}

void Head_IP::analysis(u_char *pkt_data)
{
	version=pkt_data[0] & 0x0f;
	len=pkt_data[0] & 0xf0;
	memcpy(sign,pkt_data+4,2);
	TTL=pkt_data[8];
	//memcpy(TTl,pkt_date+8,1);
	protocol=pkt_data[9] & 0xff;
	memcpy(S_IP,pkt_data+12,4);
	memcpy(D_IP,pkt_data+16,4);
	//下一层协议判断
	if(protocol == 1)
	{
		next=new Head_ICMP();
		next->analysis(pkt_data+len*4);
	}
	else if(protocol == 2)
	{
		next=new Head_IGMP();
		next->analysis(pkt_data+len*4);
	}
	else if(protocol == 6)
	{
		next=new Head_TCP();
		next->analysis(pkt_data+len*4);
	}
	else if(protocol == 17)
	{
		next=new Head_UDP();
		next->analysis(pkt_data+len*4);
	}
	else
	{
		next=NULL;
	}
}

void Head_IP::my_print()
{

}

void Head_ICMP::analysis(u_char *pkt_data)
{
	kind=pkt_data[0] & 0xff;
	code=pkt_data[1] & 0xff;

	next=NULL;  //ICMP就到头了
}

void Head_ICMP::my_print()
{

}

void Head_UDP::analysis(u_char *pkt_data)
{
	memcpy(S_Port,pkt_data,2);
	memcpy(D_Port,pkt_data,2);

	next=NULL; //现在只分析道这一层，所以下一层设置为NULL
}

void Head_UDP::my_print()
{

}

void Head_IGMP::analysis(u_char *pkt_data)
{
	version=3;						//抓到的好像都是IGMPv3
	type=pkt_data[0];
	memcpy(Multicast,pkt_data+4,4);

	next=NULL;						//到头了
}

void Head_IGMP::my_print()
{

}

void Head_TCP::analysis(u_char *pkt_data)
{
	memcpy(S_Port,pkt_data,2);
	memcpy(D_Port,pkt_data+2,2);
	memcpy(SYN,pkt_data+4,4);
	memcpy(ACK,pkt_data+8,4);
	memcpy(Size_Window,pkt_data+14,2);

	next=NULL;
}

void Head_TCP::my_print()
{

}