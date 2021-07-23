#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

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
}httpRMethod;

typedef struct httpRequest
{
	httpRMethod *method;
	char *uri;
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
	
	char *connection;
	char *cacheControl;
	char *date;
	char *pragma;
	char *upgrade;
	char *trailer;
	char *transferEncoding;
	char *via;
	char *warning;
	
	char *contentEncoding;
	char *contentLanguage;	
	char *contentLength;
	char *contentLocation;
	char *contentMd5;
	char *contentRange;
	char *contentType;
	char *expires;
	char *lastModified;
}httpRequest;
#endif
