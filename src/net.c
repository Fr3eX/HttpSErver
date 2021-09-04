#include <stdio.h>
#include <stdlib.h>

#include "net.h"
#include "utility.h"
#include "config_parser.h"

#define UNIT "SERVER"
#define DEFAULT_BACKLOG 5


#if defined(WIN32)



#elif defined(linux)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
#else
	#error "System not supported"
#endif

int __GetServerSocket(const char* filename)
{			
	unsigned short sockfd;
	struct sockaddr_in* ipv4_addr;
	socklen_t addr_size;
	char *srv_sport=NULL;
	char *srv_saddr=NULL;	
	char *srv_sbacklog=NULL;
	unsigned short srv_backlog;	
	unsigned int srv_port;	
	/*Loading file config data*/
	
	if(!filename)
		__ParseCfgFile("config");	
	else
		__ParseCfgFile(filename);	

	srv_sport = __Get("SERVER_PORT");
	srv_saddr = __Get("SERVER_IP");
	srv_sbacklog = __Get("SERVER_BACKLOG");	
	
	if(!srv_saddr)
		LogErr("No port number found in file %s",(!filename)?"config":filename)
	
	if(!srv_sport)
		LogErr("No port number found in file %s",(!filename)?"config":filename)
	else
	{
		srv_port = atoi(srv_sport);
		
		if(srv_port < MIN_PORTNUMBER || srv_port > MAX_PORTNUMBER)
			LogErr("Port number out of bounds (RANGE:%d-%d)",MIN_PORTNUMBER,MAX_PORTNUMBER)
	}		

	
	ipv4_addr = malloc(sizeof(struct sockaddr_in));
	if(!ipv4_addr)
		LogErr("No enough memory for address structure %p",ipv4_addr)
	
	Bzero(ipv4_addr,sizeof(struct sockaddr_in));//Zeroing ipv4_addr memory

	ipv4_addr->sin_family =AF_INET;
	ipv4_addr->sin_port = htons(srv_port);	
	
	if(!inet_aton(srv_saddr,&ipv4_addr->sin_addr))
		LogErr("Bad address (%s)",srv_saddr)

	if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		LogErr("socket() : %s",__$errno())
	
	unsigned char reuseAddr=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuseAddr,sizeof reuseAddr)<0)
		LogErr("setsockopt()() : %s",__$errno())


	addr_size=sizeof(struct sockaddr_in);
	
	if(bind(sockfd,(struct sockaddr*)ipv4_addr,addr_size)<0)
		LogErr("bind() : %s",__$errno())
	
	srv_backlog=(!srv_sbacklog)?DEFAULT_BACKLOG:atoi(srv_sbacklog);
	
	if(listen(sockfd,srv_backlog)<0)
		LogErr("listen() : %s",__$errno())
	
	LogInfo("%s:%s listening ...",srv_saddr,srv_sport);
	
	__FreePData();
	
	return sockfd;
}


/*
 *	Because send and recv functions don't guarantee the sending or receiving of all data that we need for that  to implement our own functions
 */


unsigned int __SendDATA(int sockfd,void* packet,size_t size)
{	
	char* pointer = (unsigned char*)packet;
	unsigned int sent_data=0,i=0;	
	while(size > 0)
	{
		if((i=send(sockfd,pointer,size,0)) < 0)
		{
			LogWarr("send() : %s on socket %d",__$errno(),sockfd);
			return sent_data;	
		}
		
		pointer += i;		
		sent_data += i;			
		size -= i;
	}
	return sent_data;	
}


void *__ReceiveDATA(int sockfd,void* packet,size_t* size)
{
	/*Zeroing memory*/
	Bzero(packet,*size);
	
	unsigned long byte_read=0,curr_read;
	
	/* PROBLEMS : 
	 * -We don't know the exact size of data that we're receiving
	 * -recv doesn't guarantee the reception of {{size}} data
	 */
	
	if(*size == 0)
	{
		/*If we dont knwo the size -> i'll just read 8kb (it can be any other size + or - ) and 
		 * i'll determine after  parsing the packet if i need more bytes
		 */

		const unsigned short buffer_size = 8192;
		
		if((curr_read=recv(sockfd,packet,buffer_size,0)<0))
		{
			LogWarr("recv() : %s on socket %d",__$errno(),sockfd);
			*size = 0;
		}
		else
			*size = curr_read;

		return packet;
	}	
	else
	{	
		/*If the size is known */	
		unsigned char* pointer = (unsigned char*)packet;
		while(size > 0)
		{
			if((curr_read = recv(sockfd,packet,*size,0))<0)
			{
				LogWarr("recv() : %s on socket %d",__$errno(),sockfd);
				*size = 0;
			}	
			pointer += curr_read;
			byte_read += curr_read;
			*size -= curr_read;
		}

		*size = byte_read;
		return packet;
	}		
}



