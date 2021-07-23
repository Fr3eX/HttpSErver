#ifndef RESPONSE_BUILDER_H
#define RESPONSE_BUILDER_H

/*
 *		RESPONSE STRUCTURE :
 *
 *		Response start line = HTTP-VERSION STATUS-CODE REASON PHRASE CRLF
 *		header1 : header1-value CRLF
 *		.
 *		.
 *		.
 *		headerN : headerN-value CRLF
 *		LF
 *		Optional body 
 *
 *		STATUS CODE :
 *		
 *		-1xx:Informational = means that the request has been received and the process is continuing. 
 *		-2xx:Sucess = means the action was successfully received,understood and accepted.
 *		-3xx:Redirection = means further action must be taken in order to complete the request.
 *		-4xx:Client Error = means the request contains incorrect syntax ir cannot be fulfilled.
 *		-5xx:Server Error  = means the server failed to fulfull an apparently valid request
 * */

typedef enum
{
	/*Informational Status Code */

	Continue=100,
	SwitchingProtocl,

	/*  Sucess Status Code */

	OK=200,
	Created,
	Accepted,
	NonAuthoritativeInformation,
	NoContent,
	ResetContent,
	PartialContent,
	
	/* Redirection Status Code */

	MultipleChoice=300,
	MovedPermanently,
	Found,
	SeeOther,
	NotModified,
	UseProxy,
	Unused,/*Was used in the previous version of the protocl but the is reserved*/
	TemporaryRedirect,

	/* Client Error Status Code */

	BadRequest=400,
	Unauthorized,
	PayementRequired, /*Not implemented*/
	Forbidden,
	NotFound,
	MethodeNotAllowed,
	NotAcceptable,
	ProxyAuthenticationRequired,
	RequestTimeout,
	Conflict,
	Gone,
	LengthRequired,
	PreconditionFailed,
	RequestEntityTooLong,
	RequestUrlTooLong,
	UnsupportedMediaType,
	RequestedRangeNotSatisfiable,
	ExpectationFailed,
	
	/* Server Error Status Code */

	InternalServerError=500,
	NotImpelemented,
	BadGateway,
	ServiceUnavailable,
	GatewayTimeout,
	HTTPVersionNotSupported

}httpRStatusCode;


typedef httpResponse
{
	HttpRStatusCode *statusCode;
	char *location;
	char *acceptRanges;
	char *age;
	char *eTag;
	char *location;
	char *proxyAuthenticate;
	char *retryAfter;
	char *server;
	char *vary;
	char *wwwAuthenticate;	
	char *setCookie;
	
	char *allow;
	char *contentEncoding;
	char *contentLanguage;	
	char *contentLength;
	char *contentLocation;
	char *contentMd5;
	char *contentRange;
	char *contentType;
	char *expires;
	char *lastModified;

	char *connection;
	char *cacheControl;
	char *date;
	char *pragma;
	char *upgrade;
	char *trailer;
	char *transferEncoding;
	char *via;
	char *warning;
}httpResponse;

#endif
