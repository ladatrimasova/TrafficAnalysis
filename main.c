//#include <stdlib.h>
//#include <ctype.h>
//#include <errno.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <map>

#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <new>
#include "class_sniff.h"
#include "StatisticAnalysis.h"
#include "SignatureAnalisator.h"


#define SNAP_LEN 1518
#define SIZE_ETHERNET 14
#define ETHER_ADDR_LEN 6
#define UDP_length 8

using namespace std;



int main(int argc, char **argv) {
	char protocol[] = "ip";
    allPackets p;
	if (argc == 2) {
			NetSniffer *obj = new NetSniffer(argv[1], protocol, 40);
			p = obj->StartSniff();
	}
	else if (argc > 2) {
			fprintf(stderr, "error: unrecognized command-line options\n\n");
			exit(EXIT_FAILURE);
	}
	else {
		NetSniffer *obj = new NetSniffer();
        p = obj->StartSniff();
	}

    p.PrintVector();

    SignatureAnalisator *sig_analys = new SignatureAnalisator();
    sig_analys->FormMap(p.v);
    sig_analys->PrintMap();
    StatisticAnalysis * statAnalysis = new StatisticAnalysis(p.v);
    printf("\nCapture complete.\n");

	return 0;
};
