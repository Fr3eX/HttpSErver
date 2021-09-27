#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "debug.h"
#include "utility.h"
#include "config_parser.h"
#include "net.h"


#define UNIT "SERVER"

#define TRUE 1 
#define FALSE 0

#if defined(WIN32)
	#include <winsock2.h>
	typedef close(param) closesocket(param);
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#elif defined(linux)
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	
#endif

static void* handleClient(void *arg);


int main(int argc,char *argv[])
{	
	
	if(!argv[1])
		__ParseCfgFile("config");	
	else
		__ParseCfgFile(argv[1]);	
	
	#if defined (WIN32)
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2,2),&WSAData);
	#endif
	
	unsigned short sockfd;
	if(argc < 1)
		sockfd=__GetServerSocket(argv[1]);	
	else 
		sockfd=__GetServerSocket(argv[1]);

	struct sockaddr_in *cln_addr = malloc(sizeof(struct sockaddr_in));
	if(!cln_addr)	
		LogErr("Not enough memort for client address structure : %p",cln_addr);

	socklen_t cln_addr_size=sizeof(struct sockaddr_in);
	int cln_fd;

	Bzero(cln_addr,sizeof(cln_addr));
	Bzero(&cln_fd,sizeof(cln_fd));

	while(TRUE)
	{
		Bzero(cln_addr,sizeof(cln_addr));
		
		LogInfo("Waiting for connections ... Serverfd=%d",sockfd);
		cln_fd = accept(sockfd,(struct sockaddr*)cln_addr,&cln_addr_size);	
		
		if(cln_fd < 0)
			LogErr("Accept() : %s",__$errno())
		
		
		unsigned int *client_sock_fd = malloc(sizeof(unsigned int));
		if(!client_sock_fd)
		{
			LogWarr("Not enough memory for client_sock_fd : %d",cln_fd);
			close(cln_fd);
			continue;
		}

		*client_sock_fd = cln_fd;
		pthread_t thread;
		if(pthread_create(&thread,NULL,handleClient,client_sock_fd))
		{
			LogWarr("Cannot create thread for cln_fd : %d",cln_fd);
			close(cln_fd);
			free(client_sock_fd);
			continue;	
		}			
	}		

	#if defined(WIN32)
		WSACleanup();
	#endif
	return 0;
}

static void* handleClient(void *arg)
{
	unsigned int cln_fd = *(unsigned int*)arg;
	free(arg);
	
	const unsigned short BUFFER_SIZE = 8192;
	
	void* buffer = malloc(BUFFER_SIZE);
	
	
		
	return NULL;
}



