#include <stdio.h>
#include <stdlib.h>

#include "net.h"
#include "utility.h"

#define SOCKET_ERROR -1

#if defined(WIN32)
	#include <winsock2.h>
	typedef close(param) closesocket(param);
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#elif defined(linux)
	#include <unistd.h>
	#include <sys/types.h>

	
#endif

int main(int argc,char *argv[])
{	
	#if defined (WIN32)
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2,2),&WSAData);
	#endif
	
	unsigned short sockfd;
	if(argc < 1)
		sockfd=__GetServerSocket(argv[1]);	
	else 
		sockfd=__GetServerSocket(argv[1]);

	

	#if defined(WIN32)
		WSACleanup();
	#endif
	return 0;
}
