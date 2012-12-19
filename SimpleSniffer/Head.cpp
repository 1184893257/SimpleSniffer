#include "stdafx.h"
#include <iostream>
#include <string.h>
#include "Head.h"

using namespace std;

extern int packet_kind;
extern unsigned char m_SIP[4];
extern unsigned char m_DIP[4];
extern unsigned char m_SIPv6[16];
extern unsigned char m_DIPv6[16];
extern int ipv6;	

const CString sign_ip="0800";
const CString sign_arp="0806";
const CString sign_ipv6="86DD";

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
	else if(m_kind.Compare(sign_ipv6) == 0)
	{
		next=new Head_IPv6();
		next->analysis(pkt_data+14);
	}
	else
	{
		next=NULL;
		packet_kind=0;
	}
}

CString Head_Ethernet::my_print()
{
	CString m_SMac;
	CString m_DMac;
	CString m_Kind;

	m_SMac.Format("源MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",S_Mac[0],S_Mac[1],S_Mac[2],S_Mac[3],S_Mac[4],S_Mac[5]);
	m_DMac.Format("目的MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",D_Mac[0],D_Mac[1],D_Mac[2],D_Mac[3],D_Mac[4],D_Mac[5]);
	m_Kind.Format("类型: %02X%02X\r\n",kind[0],kind[1]);

	return "Ethernet首部\r\n"+m_SMac+m_DMac+m_Kind;
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
	else if(m_kind.Compare(sign_ipv6) == 0)
	{
		next=new Head_IPv6();
		next->analysis(pkt_data+14);
	}
	else
	{
		next=NULL;
		packet_kind=1;
	}
}

CString Head_802_3::my_print()
{
	CString m_SMac;
	CString m_DMac;
	CString m_Kind;

	m_SMac.Format("源MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",S_Mac[0],S_Mac[1],S_Mac[2],S_Mac[3],S_Mac[4],S_Mac[5]);
	m_DMac.Format("目的MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",D_Mac[0],D_Mac[1],D_Mac[2],D_Mac[3],D_Mac[4],D_Mac[5]);
	m_Kind.Format("类型: %02X%02X\r\n",kind[0],kind[1]);

	return "802.3帧首部\r\n"+m_SMac+m_DMac+m_Kind;
}

void Head_ARP::analysis(u_char *pkt_data)
{
	memcpy(op,pkt_data+6,2);
	memcpy(S_Mac,pkt_data+8,6);
	memcpy(S_IP,pkt_data+14,4);
	
	memcpy(D_Mac,pkt_data+18,6);
	memcpy(D_IP,pkt_data+24,4);

	memcpy(m_SIP,pkt_data+14,4);
	memcpy(m_DIP,pkt_data+24,4);
	ipv6=0;
	next=NULL;						//ARP就到头了
	packet_kind=2;
}

CString Head_ARP::my_print()
{
	CString m_OP;
	CString m_SMac;
	CString m_SIP;
	CString m_DMac;
	CString m_DIP;
	int mOP=0;
	mOP=op[0]<<8 | op[1];
	m_OP.Format("操作字段:%d\r\n",mOP);
	m_SMac.Format("源MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",S_Mac[0],S_Mac[1],S_Mac[2],S_Mac[3],S_Mac[4],S_Mac[5]);
	m_DMac.Format("目的MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n",D_Mac[0],D_Mac[1],D_Mac[2],D_Mac[3],D_Mac[4],D_Mac[5]);
	m_SIP.Format("源IP: %u.%u.%u.%u\r\n",S_IP[0],S_IP[1],S_IP[2],S_IP[3]);
	m_DIP.Format("目的IP: %u.%u.%u.%u\r\n",D_IP[0],D_IP[1],D_IP[2],D_IP[3]);
	
	return "ARP首部\r\n"+m_OP+m_SMac+m_SIP+m_DMac+m_DIP;
}

void Head_IP::analysis(u_char *pkt_data)
{
	version=(pkt_data[0] & 0xf0) >> 4;
	len=pkt_data[0] & 0x0f;
	memcpy(sign,pkt_data+4,2);
	TTL=pkt_data[8];
	//memcpy(TTl,pkt_date+8,1);
	protocol=pkt_data[9] & 0xff;
	memcpy(S_IP,pkt_data+12,4);
	memcpy(D_IP,pkt_data+16,4);
	//设置全局变量
	memcpy(m_SIP,pkt_data+12,4);
	memcpy(m_DIP,pkt_data+16,4);
	ipv6=0;

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
		packet_kind=3;
	}
}

CString Head_IP::my_print()
{
	CString m_version_len;
	CString m_sign;
	CString m_TTL;
	CString m_SIP;
	CString m_DIP;
	int mSign=0;
	mSign=sign[0]<<8 | sign[1];
	m_version_len.Format("版本: %d   长度: %d\r\n",version,len);
	m_sign.Format("标识符: %d\r\n",mSign);
	m_TTL.Format("存活时间: %u\r\n",TTL);
	m_SIP.Format("源IP: %u.%u.%u.%u\r\n",S_IP[0],S_IP[1],S_IP[2],S_IP[3]);
	m_DIP.Format("目的IP: %u.%u.%u.%u\r\n",D_IP[0],D_IP[1],D_IP[2],D_IP[3]);

	return "IP首部\r\n"+m_version_len+m_sign+m_TTL+m_SIP+m_DIP;
}

void Head_ICMP::analysis(u_char *pkt_data)
{
	kind=pkt_data[0] & 0xff;
	code=pkt_data[1] & 0xff;

	next=NULL;  //ICMP就到头了
	packet_kind=4;
}

CString Head_ICMP::my_print()
{
	CString m_kind;
	CString m_code;

	m_kind.Format("类型: %d\r\n",kind);
	m_code.Format("代码: %d\r\n",code);

	return "ICMP首部\r\n"+m_kind+m_code;
}

void Head_UDP::analysis(u_char *pkt_data)
{
	memcpy(S_Port,pkt_data,2);
	memcpy(D_Port,pkt_data+2,2);
	
	int sPort=S_Port[0]<<8 | S_Port[1];
	int dPort=D_Port[0]<<8 | D_Port[1];
	if(sPort == 53 || dPort == 53)
	{
		next=new Head_DNS();
		next->analysis(pkt_data+8);
	}
	else
	{
		next=NULL; 
		packet_kind=5;
	}
}

CString Head_UDP::my_print()
{
	CString m_SPort;
	CString m_DPort;
	int sPort=0,dPort=0;
	sPort=S_Port[0]<<8 | S_Port[1];
	dPort=D_Port[0]<<8 | D_Port[1];
	//m_SPort.Format("源端口: %02X%02X\r\n",S_Port[0],S_Port[1]);
	//m_DPort.Format("目的端口: %02X%02X\r\n",D_Port[0],D_Port[1]);
	m_SPort.Format("源端口: %d\r\n",sPort);
	m_DPort.Format("目的端口: %d\r\n",dPort);

	return "UDP首部\r\n"+m_SPort+m_DPort;
}

void Head_IGMP::analysis(u_char *pkt_data)
{
	version=3;						//抓到的好像都是IGMPv3
	type=pkt_data[0];
	memcpy(Multicast,pkt_data+4,4);

	next=NULL;						//到头了
	packet_kind=6;
}

CString Head_IGMP::my_print()
{
	CString m_version;
	CString m_type;
	CString m_Multicast;

	m_version.Format("版本: %d\r\n",version);
	m_type.Format("类型: %u\r\n",type);
	m_Multicast.Format("D类IP地址: %u.%u.%u.%u\r\n",Multicast[0],Multicast[1],Multicast[2],Multicast[3]);
	
	return "IGMP首部\r\n"+m_version+m_type+m_Multicast;
}

void Head_TCP::analysis(u_char *pkt_data)
{
	memcpy(S_Port,pkt_data,2);
	memcpy(D_Port,pkt_data+2,2);
	memcpy(SYN,pkt_data+4,4);
	memcpy(ACK,pkt_data+8,4);
	memcpy(Size_Window,pkt_data+14,2);
	
	int sPort=S_Port[0]<<8 | S_Port[1];
	int dPort=D_Port[0]<<8 | D_Port[1];

	if(sPort == 80 || dPort == 80)
	{
		next=new Head_HTTP();
		next->analysis(pkt_data+20);
	}
	else if(sPort == 21 || dPort == 21)
	{
		next=new Head_FTP();
		next->analysis(pkt_data+20);
	}
	else
	{
		next=NULL;
		packet_kind=7;
	}
}

CString Head_TCP::my_print()
{
	CString m_SPort;
	CString m_DPort;
	CString m_SYN;
	CString m_ACK;
	CString m_Size_Window;

	int sPort=0,dPort=0;
	int mSYN=0,mACK=0;
	int mSize_Window;
	sPort=S_Port[0]<<8 | S_Port[1];
	dPort=D_Port[0]<<8 | D_Port[1];
	mSYN=SYN[0]<<24 | SYN[1]<<16 | SYN[2]<<8 | SYN[3];
	mACK=ACK[0]<<24 | ACK[1]<<16 | ACK[2]<<8 | ACK[3];
	mSize_Window=Size_Window[0]<<8 | Size_Window[1];

	m_SPort.Format("源端口: %d\r\n",sPort);
	m_DPort.Format("目的端口: %d\r\n",dPort);
	//m_SYN.Format("SYN: %d\r\n",mSYN);
	//m_ACK.Format("ACK: %d\r\n",mACK);
	m_Size_Window.Format("窗口大小: %d\r\n",mSize_Window);

	return "TCP首部\r\n"+m_SPort+m_DPort+m_SYN+m_ACK+m_Size_Window;
}

void Head_IPv6 :: analysis(u_char *pkt_data)
{
	version=(pkt_data[0] & 0xf0) >> 4;
	protocol=pkt_data[6] & 0xff;
	memcpy(S_IPv6,pkt_data+8,16);
	memcpy(D_IPv6,pkt_data+24,16);
	//设置全局变量
	memcpy(m_SIPv6,pkt_data+8,16);
	memcpy(m_DIPv6,pkt_data+24,16);
	ipv6=1;

	//下一层协议判断
	if(protocol == 6)
	{
		next= new Head_TCP();
		next->analysis(pkt_data+40);
	}
	else if(protocol == 17)
	{
		next= new Head_UDP();
		next->analysis(pkt_data+40);
	}
	else if(protocol == 58)
	{
		next= new Head_ICMP();
		next->analysis(pkt_data+40);
	}
	else if(protocol == 2)
	{
		next=new Head_IGMP();
		next->analysis(pkt_data+40);
	}
	else if(protocol ==89)
	{
		next=new Head_OSPF();
		next->analysis(pkt_data+40);
	}
	else
	{
		next=NULL;
		packet_kind=8;
	}
}

CString Head_IPv6:: my_print()
{
	CString m_version;
	CString m_protocol;
	CString m_SIP;
	CString m_DIP;

	m_version.Format("版本: %d\r\n",version);
	m_protocol.Format("协议层协议值: %d\r\n",protocol);
	m_SIP.Format("源地址:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\r\n",S_IPv6[0],S_IPv6[1],S_IPv6[2],S_IPv6[3],S_IPv6[4],S_IPv6[5],S_IPv6[6],S_IPv6[7],S_IPv6[8],S_IPv6[9],S_IPv6[10],S_IPv6[11],S_IPv6[12],S_IPv6[13],S_IPv6[14],S_IPv6[15]);
	m_DIP.Format("目的地址:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X\r\n",D_IPv6[0],D_IPv6[1],D_IPv6[2],D_IPv6[3],D_IPv6[4],D_IPv6[5],D_IPv6[6],D_IPv6[7],D_IPv6[8],D_IPv6[9],D_IPv6[10],D_IPv6[11],D_IPv6[12],D_IPv6[13],D_IPv6[14],D_IPv6[15]);
	
	return "IPv6首部\r\n"+m_version+m_protocol+m_SIP+m_DIP;
}

void Head_OSPF::analysis(u_char *pkt_data)
{
	version=pkt_data[0] & 0xff;
	type=pkt_data[1] & 0xff;
	memcpy(Router_ID,pkt_data+4,4);
	memcpy(Area_ID,pkt_data+8,4);

	next=NULL;
	packet_kind=9;
}

CString Head_OSPF::my_print()
{
	CString m_version;
	CString m_type;
	CString m_RouterID;
	CString m_AreaID;

	m_version.Format("版本: %d\r\n",version);
	m_type.Format("类型: %d\r\n",type);
	m_RouterID.Format("路由器ID: %u.%u.%u.%u\r\n",Router_ID[0],Router_ID[1],Router_ID[2],Router_ID[3]);
	m_AreaID.Format("区域ID: %u.%u.%u.%u\r\n",Area_ID[0],Area_ID[1],Area_ID[2],Area_ID[3]);

	return "OSPF首部\r\n"+m_version+m_type+m_RouterID+m_AreaID;
}

void Head_DNS::analysis(u_char *pkt_data)
{
	memcpy(ID,pkt_data,2);
	Question=pkt_data[0]<<8 ||pkt_data[1];

	next=NULL;
	packet_kind=10;
}

CString Head_DNS::my_print()
{
	CString m_ID;
	CString m_Question;

	m_ID.Format("标识: 0x%02x%02x\r\n",ID[0],ID[1]);
	m_Question.Format("问题数: %d\r\n",Question);

	return "DNS首部\r\n"+m_ID+m_Question;
}

void Head_HTTP::analysis(u_char *pkt_data)
{
	next=NULL;
	packet_kind=11;
}

CString Head_HTTP::my_print()
{
	return "HTTP首部\r\n";
}

void Head_FTP::analysis(u_char *pkt_data)
{
	next=NULL;
	packet_kind=12;
}

CString Head_FTP::my_print()
{
	return "FTP首部\r\n";
}