/** �ػ����ݰ������顣�ȴ�ӡ�������������������б�Ȼ��ѡ��
 * �����ĸ��������Ͻػ����ݰ���Ȼ��ͨ��pcap_loop()�������ػ�
 * �����ݰ������ص�����packet_handler()����
 
 * ͨ���ó�������˽���ʹ��winpcap�ػ����ݰ��Ĳ����Լ�һЩ��
 * �ػ����ݰ�ʱ�ǳ���Ҫ�ĺ����ͽṹ�塣
 * 2006-1-26
 */
#include <stdio.h>
#include <pcap.h>

/* Prototype of the packet handler */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

int main() {
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int inum;
	int i = 0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	
	/* Retrieve the devices list on the local machine */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1){
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	
	/* Print the list */
	for (d = alldevs; d; d = d->next){
		/* Print name */
		printf("%d. %s", ++ i, d->name);
		
		/* Print description */
		if (d->description){
			printf(" (%s)\n", d->description);
		}else{
			printf(" (No description available)\n");
		}
	}
	if (i == 0){
		printf("\nNo interfaces found! Make sure Winpcap is installed.\n");
		return -1;
	}
	
	/* Select an adapter */
	printf("Enter the interface number (1 - %d):", i);
	scanf("%d", &inum);
	if (inum < 1 || inum > i){
		printf("\nInterface number out of range.\n");		
		pcap_freealldevs(alldevs);/* Free the device list */
		return -1;
	}
	
	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, ++ i);
	
	/*Open the device */
	if ((adhandle = pcap_open(d->name, /* name of the device */
		65536,/* portion of the packet to capture , 65535 guarantees that the whole packet will be captured on all the link layers */
		PCAP_OPENFLAG_PROMISCUOUS,/* promiscuous mode */
		1000,/* read timeout */
		NULL,/* authentication on the remote machine */
		errbuf/* error buffer */)) == NULL)
	{
		fprintf(stderr, "\nnable to open the adapter. %s is not supported by Winpcap\n", d->name);
		pcap_freealldevs(alldevs);/* Free the devices list */
		return -1;
	}
	printf("\nlistening on %s...\n", d->description);
	
	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);
	
	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, NULL);
	
	return 1;
}

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct tm *ltime;
	char timestr[16];
	
	/* convert the timestamp to readable format */
	ltime = localtime(&header->ts.tv_sec);
	strftime(timestr, sizeof(timestr), "%H:%M:%S", ltime);
	
	printf("%s, %.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
}
