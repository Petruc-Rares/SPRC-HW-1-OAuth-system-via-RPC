/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _TEMA_H_RPCGEN
#define _TEMA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

struct token {
	char *token_value;
	int no_available_operations;
};
typedef struct token token;

struct resource_permissions {
	char *resource;
	char *permissions;
};
typedef struct resource_permissions resource_permissions;

struct approve_request_token_response {
	token authz_token;
	struct {
		u_int list_permissions_len;
		resource_permissions *list_permissions_val;
	} list_permissions;
};
typedef struct approve_request_token_response approve_request_token_response;

struct request_authorization_param {
	int user_id;
	int auto_refresh;
};
typedef struct request_authorization_param request_authorization_param;

struct request_access_token_param {
	int user_id;
	token authz_token;
	token auto_refresh;
};
typedef struct request_access_token_param request_access_token_param;

struct request_access_token_response {
	token access_token;
	token refresh_token;
	int availability_period;
};
typedef struct request_access_token_response request_access_token_response;

struct validate_delegated_action_param {
	int user_id;
	char *action;
	char *resource;
	token access_token;
};
typedef struct validate_delegated_action_param validate_delegated_action_param;

struct validate_delegated_action_response {
	token authz_token;
	token access_token;
	token refresh_token;
	int availability_period;
	char *response;
};
typedef struct validate_delegated_action_response validate_delegated_action_response;

typedef struct user_db {
	int user_id;
	token access_token;
	token refresh_token;
	resource_permissions *list_permissions_val;
} user_db;
// list of authz token with permissions associated
typedef struct authz_token_permissions {
	token authz_token;
	resource_permissions *list_permissions_val;
} authz_token_permissions;

typedef struct approvals {
	resource_permissions *list_permissions_val;
	int no_resources_w_permissions;
} approvals;

#define CHEKPROG 0x31234567
#define CHECKVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define request_authorization 1
extern  token * request_authorization_1(request_authorization_param *, CLIENT *);
extern  token * request_authorization_1_svc(request_authorization_param *, struct svc_req *);
#define approve_request_token 2
extern  approve_request_token_response * approve_request_token_1(token *, CLIENT *);
extern  approve_request_token_response * approve_request_token_1_svc(token *, struct svc_req *);
#define request_access_token 3
extern  request_access_token_response * request_access_token_1(request_access_token_param *, CLIENT *);
extern  request_access_token_response * request_access_token_1_svc(request_access_token_param *, struct svc_req *);
#define validate_delegated_action 4
extern  validate_delegated_action_response * validate_delegated_action_1(validate_delegated_action_param *, CLIENT *);
extern  validate_delegated_action_response * validate_delegated_action_1_svc(validate_delegated_action_param *, struct svc_req *);
extern int chekprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define request_authorization 1
extern  token * request_authorization_1();
extern  token * request_authorization_1_svc();
#define approve_request_token 2
extern  approve_request_token_response * approve_request_token_1();
extern  approve_request_token_response * approve_request_token_1_svc();
#define request_access_token 3
extern  request_access_token_response * request_access_token_1();
extern  request_access_token_response * request_access_token_1_svc();
#define validate_delegated_action 4
extern  validate_delegated_action_response * validate_delegated_action_1();
extern  validate_delegated_action_response * validate_delegated_action_1_svc();
extern int chekprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_token (XDR *, token*);
extern  bool_t xdr_resource_permissions (XDR *, resource_permissions*);
extern  bool_t xdr_approve_request_token_response (XDR *, approve_request_token_response*);
extern  bool_t xdr_request_authorization_param (XDR *, request_authorization_param*);
extern  bool_t xdr_request_access_token_param (XDR *, request_access_token_param*);
extern  bool_t xdr_request_access_token_response (XDR *, request_access_token_response*);
extern  bool_t xdr_validate_delegated_action_param (XDR *, validate_delegated_action_param*);
extern  bool_t xdr_validate_delegated_action_response (XDR *, validate_delegated_action_response*);

#else /* K&R C */
extern bool_t xdr_token ();
extern bool_t xdr_resource_permissions ();
extern bool_t xdr_approve_request_token_response ();
extern bool_t xdr_request_authorization_param ();
extern bool_t xdr_request_access_token_param ();
extern bool_t xdr_request_access_token_response ();
extern bool_t xdr_validate_delegated_action_param ();
extern bool_t xdr_validate_delegated_action_response ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_TEMA_H_RPCGEN */
