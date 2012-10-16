#include <stdio.h>
#include <pcap.h>

int main() {
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];

	/* Retrieve the device list from the local machine*/
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1){
		printf("Error in pcap_findalldevs_ex: %s\n", errbuf);
		exit(1);
	}

	/* Print the list */
	for (d = alldevs; d != NULL; d = d->next){
		/* Print the device's name */
		printf("%d. %s", ++ i, d->name);

		/* Print the device's dscription */
		if (d->description){
			printf("(%s)\n", d->description);
		}else{
			printf("(No description available)\n");
		}
	}

	if (i == 0){
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return 0;
	}

	/* We don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);
	return 1;
}