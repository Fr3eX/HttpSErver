#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <stdbool.h>

#include "debug.h"
#include "utility.h"
#include "file.h"

#define UNIT "FILE"

static unsigned DEFAUTL_BUFFER_SIZE = 51200; //50KB


SFile* load_file(const char* filename)
{
	if(!filename)
		return NULL;
	
	struct stat* fStat = malloc(sizeof(struct stat));

	if(!fStat)
		RAmsg(fStat);		
	
	if(stat(filename,fStat))	
	{
		LogWarr("(file : %s) : %s",filename,__$errno());
		free(fStat);
		return NULL;
	}

	/*
	 *	-st_mode contains file type and mode (man stat);
	 *	-Checking if it's a regular file .
	 * */
	if(! fStat->st_mode & S_IFREG ) 
	{
		LogWarr("(file : %s) : Is not a regular file",filename);
		free(fStat);
		return NULL;			
	}
	
	FILE* file = fopen(filename,"rb");
	if(!file)
	{
		LogWarr("(file : %s) : %s",filename,__$errno());
		free(fStat);
		return NULL;
	}


	unsigned long file_size = fStat->st_size,curr_read=0,byte_read=0;
	void *buffer = malloc(file_size),*pointer = buffer;
	unsigned char block_size = sizeof(unsigned char);

	while((curr_read = fread(pointer,block_size,file_size,file)),curr_read && file_size > 0)
	{
		if(curr_read < 0)
		{
			free(buffer);
			free(fStat);
			fclose(file);
			return NULL;
		}

		pointer+=curr_read;
		byte_read+=curr_read;
		file_size-=curr_read;
	
		printf("%ld\n",curr_read);	
	}
		
	
	SFile* loaded_file = malloc(sizeof(SFile));
	
	if(!loaded_file)
		RAmsg(loaded_file);	

	loaded_file->fSize = byte_read;
	
	if(byte_read == 0)
		free(buffer);
	else	
		loaded_file->buffer = buffer;	
			
	//We shouldn't free the buffer (buffer)  because our structure member above point to it
	free(fStat);
	fclose(file);
		


	return loaded_file;
}

void free_file(SFile* loaded_file)
{
	if(!loaded_file)
		return;

	free(loaded_file->buffer);		
	free(loaded_file);
}
