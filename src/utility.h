#ifndef UTILITY_H
#define UTILITY_H

#include <string.h>
#include <errno.h>


#define __$errno() (errno == 0) ? "Success":strerror(errno)


/* Custom method for deleting request and response props*/
#define delete(var,prop) if(var && var->prop) \
				free(var->prop);


/*Msg error in case the allocation didn't go well */
#define RAmsg(var) {\
		   	 LogWarr("Not enough memory (%p)",var); \
		   	 return NULL;\
	 	   }



void* Bzero(void *,size_t);
#endif //UTILITY_H
