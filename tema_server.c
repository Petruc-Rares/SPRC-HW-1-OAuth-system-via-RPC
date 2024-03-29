/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "tema.h"
#include "token.h"

// available resources on server
extern char **resources_db;
extern int no_resources;
// users known by server
extern char **users_known;
extern int no_users_known;
// users databes
extern user_db *user_database;
extern int size_database;
// approvals
extern approvals *list_approvals;
extern int no_approvals;
extern int crt_approval_no;

extern int no_operations_per_token;

// authz tokens with associated permissions
extern authz_token_permissions *authz_token_permissions_list;
extern int no_authz_token_permissions_list;

token *
request_authorization_1_svc(request_authorization_param *argp, struct svc_req *rqstp)
{
	static token  result;

	char *user_id = argp->user_id;

	printf("BEGIN %s AUTHZ\n", user_id);

	int user_found = 0;
	

	// check if user_id is one of the known users
	for (int i = 0; i < no_users_known; i++) {
		if (strncmp(users_known[i], user_id, strlen(users_known[i])) == 0) {
			user_found = 1;
		}
	}

	if (user_found == 0) {
		// create impossible values for token and # operations
		result.token_value = "USER_NOT_FOUND";
		result.no_available_operations = -1;
	} else {
		result.token_value = generate_access_token(user_id);
		result.no_available_operations = 0;
	}
	return &result;
}

approve_request_token_response *
approve_request_token_1_svc(token *argp, struct svc_req *rqstp)
{
	static approve_request_token_response  result;

	memcpy(&result.authz_token, argp, sizeof(token));

	// check no permissions
	if ((strncmp(list_approvals[crt_approval_no].list_permissions_val[0].resource, "*", 1) == 0) &&
		(strncmp(list_approvals[crt_approval_no].list_permissions_val[0].permissions, "-", 1) == 0)) {
		result.authz_token.user_signed = 0;
	} else {
		result.authz_token.user_signed = 1;
	}

	// there exists the chance that the authz_token already exists in the list so if that's the case
	// just replace the permissions associated with it
	int pos_to_add = no_authz_token_permissions_list;

	for (int i = 0; i < no_authz_token_permissions_list; i++) {
		if (strncmp(argp->token_value, authz_token_permissions_list[i].authz_token.token_value, SIZE_USER_ID) == 0) {
			pos_to_add = i;
			break;
		}	
	}

	// no same authz_token found before; then allocate new memory
	if (pos_to_add == no_authz_token_permissions_list) {
		authz_token_permissions_list = (authz_token_permissions*) realloc(authz_token_permissions_list, (no_authz_token_permissions_list + 1) * sizeof(authz_token_permissions));
		authz_token_permissions_list[no_authz_token_permissions_list].authz_token.token_value = calloc(SIZE_USER_ID + 1,sizeof(char));
		strcpy(authz_token_permissions_list[pos_to_add].authz_token.token_value, argp->token_value);
		no_authz_token_permissions_list++;
	}
	
	// get the new set of approvals in internal database
	authz_token_permissions_list[pos_to_add].list_permissions_val = list_approvals[crt_approval_no].list_permissions_val;
	authz_token_permissions_list[pos_to_add].list_permissions_len = list_approvals[crt_approval_no].no_resources_w_permissions;

	// also set the the approvals for the result
	result.list_permissions.list_permissions_len =  list_approvals[crt_approval_no].no_resources_w_permissions;
	result.list_permissions.list_permissions_val = list_approvals[crt_approval_no].list_permissions_val;

	// increment crt approval number
	crt_approval_no++;

	return &result;
}

request_access_token_response *
request_access_token_1_svc(request_access_token_param *argp, struct svc_req *rqstp)
{
	static request_access_token_response  result;

	int user_exists = 0;
	int position_to_add = size_database;

	// check if user does not already exist in database and if it does, replace anything but user_id
	for (int i = 0; i < size_database; i++) {
		if (strncmp(user_database[i].user_id, argp->user_id, SIZE_USER_ID) == 0) {
			user_exists = 1;
			position_to_add = i;
			break;
		}
	}

	if ((position_to_add != size_database) && (strncmp(argp->authz_token.token_value, user_database[position_to_add].refresh_token.token_value, SIZE_USER_ID) == 0)) {
		printf("BEGIN %s AUTHZ REFRESH\n", argp->user_id);
	} else {
		printf("  RequestToken = %s\n", argp->authz_token.token_value);
	}


	if (argp->authz_token.user_signed == 0) {
		result.fail = 1;
		return &result;
	}

	result.fail = 0;

	result.access_token.token_value = generate_access_token(argp->authz_token.token_value);
	result.access_token.no_available_operations = no_operations_per_token;
	printf("  AccessToken = %s\n", result.access_token.token_value);

	result.refresh_token.token_value = "INVALID_VALUE";

	if (argp->auto_refresh) {
		result.refresh_token.token_value = generate_access_token(result.access_token.token_value);
		printf("  RefreshToken = %s\n", result.refresh_token.token_value);
	}

	char *prev_refresh_token_value = "default";

	if (user_exists == 0) {
		user_database = realloc(user_database, (size_database + 1) * sizeof(user_db));
		user_database[size_database].user_id = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
		user_database[size_database].access_token.token_value = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
		user_database[size_database].refresh_token.token_value = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
		strncpy(user_database[size_database].user_id, argp->user_id, SIZE_USER_ID);
		size_database++;
	} else {
		prev_refresh_token_value = (char *) calloc((SIZE_USER_ID + 1), sizeof(char));
		strncpy(prev_refresh_token_value, user_database[position_to_add].refresh_token.token_value, SIZE_USER_ID * sizeof(char));
	}

	strncpy(user_database[position_to_add].access_token.token_value, result.access_token.token_value, SIZE_USER_ID);
	user_database[position_to_add].access_token.no_available_operations = no_operations_per_token;
	strncpy(user_database[position_to_add].refresh_token.token_value, result.refresh_token.token_value, SIZE_USER_ID);

	// new permissions if authz_token differs from refresh_token
	// but if first time to add no refresh_token exists and refresh_token might be
	// equal to authz_token so add this condition as well
	if (strncmp(argp->authz_token.token_value, prev_refresh_token_value, SIZE_USER_ID) != 0) {
		for (int i = 0; i < no_authz_token_permissions_list; i++) {
			if (strncmp(authz_token_permissions_list[i].authz_token.token_value,
						argp->authz_token.token_value, SIZE_USER_ID) == 0) {
				user_database[position_to_add].list_permissions_val = authz_token_permissions_list[i].list_permissions_val;
				user_database[position_to_add].list_permissions_len = authz_token_permissions_list[i].list_permissions_len;
				break;
			}
		}
	}

	return &result;
}

char **
validate_delegated_action_1_svc(validate_delegated_action_param *argp, struct svc_req *rqstp)
{
	static char * result;

	int i;
	for (i = 0; i < size_database; i++) {
		if (strncmp(argp->access_token.token_value, user_database[i].access_token.token_value, SIZE_USER_ID) == 0) {
			break;
		}
	}

	// if invalid access token
	// not matching access token
	if ((argp->access_token.no_available_operations == -1) ||
		(i == size_database)) {
		// TBD if it's the case just for this printf
		printf("DENY (%s,%s,,0)\n", argp->action, argp->resource);
		result = "PERMISSION_DENIED";
		return &result;
	}

	// number of available operations left
	if (argp->access_token.no_available_operations == 0) {
		printf("DENY (%s,%s,,0)\n", argp->action, argp->resource);
		result = "TOKEN_EXPIRED";
		return &result;
	}

	user_database[i].access_token.no_available_operations--;

	// search for resource
	int j;
	for (j = 0; j < no_resources; j++) {
		if (strncmp(resources_db[j], argp->resource, BUFSIZE) == 0)
			break;
	}

	if (j == no_resources) {
		printf("DENY (%s,%s,%s,%d)\n", argp->action, argp->resource, argp->access_token.token_value, user_database[i].access_token.no_available_operations);
		result = "RESOURCE_NOT_FOUND";
		return &result;
	}

	int k;

	// look for permissions
	for (k = 0; k < user_database[i].list_permissions_len; k++) {
		// find the resource
		if (strncmp(user_database[i].list_permissions_val[k].resource, argp->resource, BUFSIZE) == 0) {
			// resource found; now check permissions
			int k_1 = 0;
			int look_at = 0;
			if (strncmp("EXECUTE", argp->action, strlen(argp->action)) == 0) {
				look_at = 1;
			}
			for (k_1; k_1 < strlen(user_database[i].list_permissions_val[k].permissions); k_1++) {
				
				if (argp->action[look_at] == user_database[i].list_permissions_val[k].permissions[k_1]) {
					break;
				}
			}

			if (k_1 == strlen(user_database[i].list_permissions_val[k].permissions)) {
				printf("DENY (%s,%s,%s,%d)\n", argp->action, argp->resource, argp->access_token.token_value, user_database[i].access_token.no_available_operations);
				result = "OPERATION_NOT_PERMITTED";
				return &result;
			}

			break;
		}
	}

	// resource not found in approvals
	if (k == user_database[i].list_permissions_len) {
		printf("DENY (%s,%s,%s,%d)\n", argp->action, argp->resource, argp->access_token.token_value, user_database[i].access_token.no_available_operations);
		result = "OPERATION_NOT_PERMITTED";
		return &result;
	}

	// all good
	printf("PERMIT (%s,%s,%s,%d)\n", argp->action, argp->resource, argp->access_token.token_value, user_database[i].access_token.no_available_operations);
	result="PERMISSION_GRANTED";

	return &result;
}
