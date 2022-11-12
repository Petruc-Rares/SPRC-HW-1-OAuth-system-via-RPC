/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "tema.h"

bool_t
xdr_token (XDR *xdrs, token *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->token_value, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->no_available_operations))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->user_signed))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_resource_permissions (XDR *xdrs, resource_permissions *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->resource, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->permissions, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_approve_request_token_response (XDR *xdrs, approve_request_token_response *objp)
{
	register int32_t *buf;

	 if (!xdr_token (xdrs, &objp->authz_token))
		 return FALSE;
	 if (!xdr_array (xdrs, (char **)&objp->list_permissions.list_permissions_val, (u_int *) &objp->list_permissions.list_permissions_len, ~0,
		sizeof (resource_permissions), (xdrproc_t) xdr_resource_permissions))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_request_authorization_param (XDR *xdrs, request_authorization_param *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->user_id, ~0))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->auto_refresh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_request_access_token_param (XDR *xdrs, request_access_token_param *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->user_id, ~0))
		 return FALSE;
	 if (!xdr_token (xdrs, &objp->authz_token))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->auto_refresh))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_request_access_token_response (XDR *xdrs, request_access_token_response *objp)
{
	register int32_t *buf;

	 if (!xdr_token (xdrs, &objp->access_token))
		 return FALSE;
	 if (!xdr_token (xdrs, &objp->refresh_token))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->fail))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_validate_delegated_action_param (XDR *xdrs, validate_delegated_action_param *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->user_id, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->action, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->resource, ~0))
		 return FALSE;
	 if (!xdr_token (xdrs, &objp->access_token))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_validate_delegated_action_response (XDR *xdrs, validate_delegated_action_response *objp)
{
	register int32_t *buf;

	 if (!xdr_token (xdrs, &objp->authz_token))
		 return FALSE;
	 if (!xdr_token (xdrs, &objp->access_token))
		 return FALSE;
	 if (!xdr_token (xdrs, &objp->refresh_token))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->availability_period))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->response, ~0))
		 return FALSE;
	return TRUE;
}
