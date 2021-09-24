#ifndef REQUEST_H
#define REQUEST_H


#define REQUEST_BUFFER_SIZE 65536 //64kb 

/*
 *		REQUEST STRUCTURE :
 *
 *		Request start line = METHOD URI HTTP-VERSION CRLF
 *		header1 : header1-value CRLF
 *		.
 *		.
 *		.
 *		headerN : headerN-value CRLF
 *		LF
 *		Optional body 
 * */

typedef enum
{
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE
}httpReqMethod;

typedef struct httpRequest
{
	
	/* Response headers*/
	
	httpReqMethod *method;
	char *uri;
	char *httpversion;
	char *accept;
	char *acceptCharset;
	char *acceptEncoding;
	char *acceptLanguage;
	char *authorization;
	char *except;
	char *from;
	char *host;
	char *cookie;
	char *ifMatch;
	char *ifModifiedSince;
	char *ifNoneMatch;
	char *ifRange;
	char *ifUnmodifiedSince;
	char *maxForwards;
	char *proxyAuthorization;
	char *range;
	char *referer;
	char *te;
	char *userAgent;
	
	/*******************/

	/* General headers */
	
	char *connection;
	char *cacheControl;
	char *date;
	char *pragma;
	char *upgrade;
	char *trailer;
	char *transferEncoding;
	char *via;
	char *warning;
	/******************/


	/* Entity headers  */
	
	char *contentEncoding;
	char *contentLanguage;	
	char *contentLength;
	char *contentLocation;
	char *contentMd5;
	char *contentRange;
	char *contentType;
	char *expires;
	char *lastModified;


	void *body;
}httpRequest;

httpRequest* newRequestObject(httpReqMethod,char*,char*);
void* freeRequestObject(httpRequest*);

#endif
