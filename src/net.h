#ifndef NET_H
#define NET_H

#define MAX_PORTNUMBER 65000
#define MIN_PORTNUMBER 1050

int __GetServerSocket();
unsigned int __SendDATA(int,void*,size_t);
void *__ReceiveDATA(int,void*,size_t*);


#endif //NET_H
