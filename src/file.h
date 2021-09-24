#ifndef FILE_H
#define FILE_H


typedef struct
{
	unsigned long fSize;
	void* buffer;
}SFile;

extern SFile* load_file(const char*);
extern void free_file(SFile*);
//extern bool store_file(void*,const size_t);


#endif //FILE_H
