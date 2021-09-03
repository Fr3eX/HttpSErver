#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utility.h"


void* Bzero(void* buffer,size_t length)
{
	#ifdef DEBUG
		LogInfo("Zeroing Memory zone : %p",buffer);	
	#endif

	return memset(buffer,0,length);
}


