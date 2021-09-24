#ifndef DEBUG_H
#define DEBUG_H


#define LogInfo(message,...) fprintf(stdout,"~INFO~ : ["UNIT"] "message"\n",__VA_ARGS__)


#define LogErr(message,...) \
			{\
				fprintf(stderr,"~ERROR~ : ["UNIT"] "message"\n",__VA_ARGS__);\
				exit(EXIT_FAILURE);\
			}

#define LogWarr(message,...) fprintf(stderr,"~WARNING~ : ["UNIT"] "message"\n",__VA_ARGS__)


#endif //DEBUG_H
