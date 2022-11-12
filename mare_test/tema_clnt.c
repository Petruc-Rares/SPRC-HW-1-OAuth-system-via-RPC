/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "tema.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

token *
request_authorization_1(request_authorization_param *argp, CLIENT *clnt)
{
	static token clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, request_authorization,
		(xdrproc_t) xdr_request_authorization_param, (caddr_t) argp,
		(xdrproc_t) xdr_token, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

approve_request_token_response *
approve_request_token_1(token *argp, CLIENT *clnt)
{
	static approve_request_token_response clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, approve_request_token,
		(xdrproc_t) xdr_token, (caddr_t) argp,
		(xdrproc_t) xdr_approve_request_token_response, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

request_access_token_response *
request_access_token_1(request_access_token_param *argp, CLIENT *clnt)
{
	static request_access_token_response clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, request_access_token,
		(xdrproc_t) xdr_request_access_token_param, (caddr_t) argp,
		(xdrproc_t) xdr_request_access_token_response, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

validate_delegated_action_response *
validate_delegated_action_1(validate_delegated_action_param *argp, CLIENT *clnt)
{
	static validate_delegated_action_response clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, validate_delegated_action,
		(xdrproc_t) xdr_validate_delegated_action_param, (caddr_t) argp,
		(xdrproc_t) xdr_validate_delegated_action_response, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
