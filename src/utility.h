#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>
#include <errno.h>

#define __$errno() (errno == 0) ? "Success":strerror(errno)

#define LogInfo(message,...) fprintf(stdout,"~INFO~ : "message"\n",__VA_ARGS__)

#define LogErr(message,...) \
			{\
				fprintf(stderr,"~ERROR~ : "message"\n",__VA_ARGS__);\
				exit(EXIT_FAILURE);\
			}
		

#define LogWarr(message,...) fprintf(stderr,"~WARNING~ : "message"\n",__VA_ARGS__)



/* Custom method for deleting request and response structure*/
#define delete(var,prop) if(var && var->prop) \
				free(var->prop);


/*Msg error in case the allocation didn't go well */
#define ErrAmsg(var) LogWarr("[REQUEST] Not enough memory (%p)",var); \
		    return NULL



void* Bzero(void *,size_t);
#endif //UTILITY_H
