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

#define BUFSIZE 100
#define SIZE_USER_ID 15

struct token {
	char *token_value;
	int no_available_operations;
	int user_signed;
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
	char *user_id;
};
typedef struct request_authorization_param request_authorization_param;

struct request_access_token_param {
	char *user_id;
	token authz_token;
	int auto_refresh;
};
typedef struct request_access_token_param request_access_token_param;

struct request_access_token_response {
	token access_token;
	token refresh_token;
	int fail;
};
typedef struct request_access_token_response request_access_token_response;

struct validate_delegated_action_param {
	char *action;
	char *resource;
	token access_token;
};
typedef struct validate_delegated_action_param validate_delegated_action_param;

typedef struct user_db {
	char *user_id;
	token access_token;
	token refresh_token;
	resource_permissions *list_permissions_val;
	int list_permissions_len;
} user_db;
// list of authz token with permissions associated
typedef struct authz_token_permissions {
	token authz_token;
	resource_permissions *list_permissions_val;
	int list_permissions_len;
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
extern  char ** validate_delegated_action_1(validate_delegated_action_param *, CLIENT *);
extern  char ** validate_delegated_action_1_svc(validate_delegated_action_param *, struct svc_req *);
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
extern  char ** validate_delegated_action_1();
extern  char ** validate_delegated_action_1_svc();
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

#else /* K&R C */
extern bool_t xdr_token ();
extern bool_t xdr_resource_permissions ();
extern bool_t xdr_approve_request_token_response ();
extern bool_t xdr_request_authorization_param ();
extern bool_t xdr_request_access_token_param ();
extern bool_t xdr_request_access_token_response ();
extern bool_t xdr_validate_delegated_action_param ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_TEMA_H_RPCGEN */
