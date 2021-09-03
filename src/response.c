#include <stdio.h>
#include <stdlib.h>

#include "response.h"
#include "utility.h"

httpResponse *newResponseObject(httpRespStatusCode* code,char* reason,char*httpversion)
{
	httpResponse *response = malloc(sizeof(httpResponse));

	if(!response)
		ErrAmsg(response);

	response->statusCode = malloc(sizeof(httpRespStatusCode));
	response->reason = malloc((strlen(reason)+1) * sizeof(char));
	response->httpversion = malloc((strlen(httpversion)+1) * sizeof(char));
	
	if(!response->statusCode)
		ErrAmsg(response->statusCode);
	
	if(!response->httpversion)
		ErrAmsg(response->httpversion);

	if(!response->reason)
		ErrAmsg(response->reason);

	
	return response;
}


void *freeResponseObject(httpResponse* response)
{
	delete(response,statusCode);	
	delete(response,reason);
	delete(response,httpversion);
	delete(response,location);
	delete(response,acceptRanges);
	delete(response,age);
	delete(response,eTag);
	delete(response,proxyAuthenticate);
	delete(response,retryAfter);
	delete(response,server);
	delete(response,vary);
	delete(response,wwwAuthenticate);
	delete(response,setCookie);

	delete(response,allow);
	delete(response,contentEncoding);
	delete(response,contentLanguage);
	delete(response,contentLength);
	delete(response,contentLocation);
	delete(response,contentMd5);
	delete(response,contentRange);
	delete(response,contentType);
	delete(response,expires);
	delete(response,lastModified);

	delete(response,connection);
	delete(response,cacheControl);
	delete(response,date);
	delete(response,pragma);
	delete(response,upgrade);
	delete(response,trailer);
	delete(response,transferEncoding);
	delete(response,via);
	delete(response,warning);
	
	
	free(response);

	return NULL;
}


