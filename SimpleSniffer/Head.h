#ifndef __MY_HEAD__
#define __MY_HEAD__
#define u_char char
class Head_Super{
public:
	Head_Super* next;
	virtual void analysis(u_char *pkt_data)=0;
	virtual void my_print()=0;
};

class Head_Ethernet : public Head_Super{
public:
	u_char S_Mac[6];
	u_char D_Mac[6];
	u_char kind[2];   //0800:IP  0806:ARP
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_802_3 : public Head_Super{
public:
	u_char S_Mac[6];
	u_char D_Mac[6];
	u_char kind[2];   //0800:IP  0806:ARP
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_ARP : public Head_Super{
public:
	u_char op[2];  //require or answer
	u_char S_Mac[6];
	u_char S_IP[4];
	u_char D_Mac[6];
	u_char D_IP[4];
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_IP : public Head_Super{
public:
	int version;	//不能取IP首部第一个字节，只能取前4位
	int len;		//取接下来的4位
	u_char sign[2];	//标识符
	u_char TTL;		//存活时间
	int protocol;
	u_char S_IP[4];
	u_char D_IP[4];
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_ICMP : public Head_Super{
public:
	int kind;
	int code;
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_UDP : public Head_Super{
public:
	u_char S_Port[2];
	u_char D_Port[2];
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_IGMP : public Head_Super{
public:
	int version; // should be 3
	u_char type;
	u_char Multicast[4];
	void analysis(u_char *pkt_data);
	void my_print();
};

class Head_TCP : public Head_Super{
public:
	u_char S_Port[2];
	u_char D_Port[2];
	u_char SYN[4];
	u_char ACK[4];
	u_char Size_Window[2];
	void analysis(u_char *pkt_data);
	void my_print();
};
#endif