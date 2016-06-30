/* Daniel Kreider - 05-09-16

This simply requires an IP address as a parameter and then returns the hostname for that IP.

*/

#undef UNICODE

#define _WINSOCK_DEPRECATED_NO_WARNINGS  // Safe? Probably not compatible with IPv6.
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")


int main(int argc, char *argv[])
{

	//-----------------------------------------
	// Declare and initialize variables
	WSADATA wsaData;
	int result;
	int status;
	INT iRetval;
	struct addrinfo hints;
	struct addrinfo *res = 0;
	DWORD dwRetval;


	if (argc != 2) {
		printf("Please give me a server's IP.");
		return 0;
	}

	// Initialize Winsock
	if ((result = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		printf("WSA Started up failed with error: %d\n", result);
		return 1;
	}

	const char *ipstr = argv[1];
	struct in_addr ip;
	struct hostent *hp;

	if (!inet_pton(AF_INET, ipstr, &ip)) {
		printf("Error! Can't parse the ip.\n");
		return 1;
	}

	if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL) {
		printf("No name associated with %s.\n", ipstr);
		return 1;
	}
	else {
		printf("Name associated with %s is %s.\n", ipstr, hp->h_name);
	}


	WSACleanup();

	return 0;
}
