/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "tema.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

#define SIZE_USER_ID 15
#define BUFSIZE 100

// used for reading data into it
// and after that getting length of data read
// for further allocation of other variables
char buf[BUFSIZE];

// available resources on server
char **resources_db;
int no_resources;
// users known by server
char **users_known;
int no_users_known;
// users databes
user_db *user_database;
// authz tokens with associated permissions
authz_token_permissions *authz_token_permissions_list;
// approvals
approvals *list_approvals;
int no_approvals;
int crt_approval_no;

static void
chekprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		request_authorization_param request_authorization_1_arg;
		token approve_request_token_1_arg;
		request_access_token_param request_access_token_1_arg;
		validate_delegated_action_param validate_delegated_action_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case request_authorization:
		_xdr_argument = (xdrproc_t) xdr_request_authorization_param;
		_xdr_result = (xdrproc_t) xdr_token;
		local = (char *(*)(char *, struct svc_req *)) request_authorization_1_svc;
		break;

	case approve_request_token:
		_xdr_argument = (xdrproc_t) xdr_token;
		_xdr_result = (xdrproc_t) xdr_approve_request_token_response;
		local = (char *(*)(char *, struct svc_req *)) approve_request_token_1_svc;
		break;

	case request_access_token:
		_xdr_argument = (xdrproc_t) xdr_request_access_token_param;
		_xdr_result = (xdrproc_t) xdr_request_access_token_response;
		local = (char *(*)(char *, struct svc_req *)) request_access_token_1_svc;
		break;

	case validate_delegated_action:
		_xdr_argument = (xdrproc_t) xdr_validate_delegated_action_param;
		_xdr_result = (xdrproc_t) xdr_validate_delegated_action_response;
		local = (char *(*)(char *, struct svc_req *)) validate_delegated_action_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}


void read_known_users(char *filename_clients) {
	FILE *fp = fopen(filename_clients, "r");
	if (fp == NULL) {
		printf("Cannot open %s\n", filename_clients);
		exit(1);
	}

	fscanf(fp, "%d", &no_users_known);
	
	users_known = (char **) calloc(no_users_known, sizeof(char *));
	if (!users_known) {
		printf("Allocation of users_known failed\n");
		exit(1);
	}

	for (int i = 0; i < no_users_known; i++) {
		users_known[i] = (char *) calloc(SIZE_USER_ID, sizeof(char));
		if (!users_known[i]) {
			printf("Allocations of users_known[%d] failed\n", i);
			exit(1);
		}

		fscanf(fp, "%s", users_known[i]);
	}


	fclose(fp);
}

void read_resources(char *filename_resources) {
	FILE *fp = fopen(filename_resources, "r");
	if (fp == NULL) {
		printf("Cannot open %s\n", filename_resources);
		exit(1);
	}

	fscanf(fp, "%d", &no_resources);
	
	resources_db = (char **) calloc(no_resources, sizeof(char *));
	if (!resources_db) {
		printf("Allocation of resources_db failed\n");
		exit(1);
	}

	for (int i = 0; i < no_resources; i++) {
		memset(buf, 0, BUFSIZE);
		fscanf(fp, "%s", buf);

		resources_db[i] = (char *) calloc(strlen(buf) + 1, sizeof(char));
		if (!resources_db[i]) {
			printf("Allocations of resources_db[%d] failed\n", i);
			exit(1);
		}
		
		memcpy(resources_db[i], buf, strlen(buf));
	}


	fclose(fp);	
}

void read_approvals(char *filename_approvals) {
	FILE *fp = fopen(filename_approvals, "r");
	if (fp == NULL) {
		printf("Cannot open %s\n", filename_approvals);
		exit(1);
	}
	const char delimiter[2] = ",";
	char *resource;
	char *permissions;
	int crt_it = 0;

	no_approvals = 0;


	list_approvals = (approvals *) calloc((no_approvals + 1), sizeof(approvals));


	while (fgets(buf, BUFSIZE, fp)) {
		list_approvals = (approvals *) realloc(list_approvals, (no_approvals + 1) * sizeof(approvals));
		//printf("%s", buf);


		resource = strtok(buf, delimiter);
		permissions = strtok(NULL, delimiter);

		crt_it = 0;

		while(resource != NULL) {
			list_approvals[no_approvals].list_permissions_val = (resource_permissions *) realloc(list_approvals[no_approvals].list_permissions_val, (crt_it + 1) * sizeof(resource_permissions));

			list_approvals[no_approvals].list_permissions_val[crt_it].resource = (char *) calloc(strlen(resource) + 1, sizeof(char));	
			if (!list_approvals[no_approvals].list_permissions_val[crt_it].resource) {
				printf("failed allocating resource name in approval\n");
				exit(1);
			}
			
			memcpy(list_approvals[no_approvals].list_permissions_val[crt_it].resource, resource, strlen(resource));
			
			list_approvals[no_approvals].list_permissions_val[crt_it].permissions = (char *) calloc(strlen(permissions) + 1, sizeof(char));
			if (!list_approvals[no_approvals].list_permissions_val[crt_it].permissions) {
				printf("failed allocating permissions in approval\n");
				exit(1);
			}
						
			memcpy(list_approvals[no_approvals].list_permissions_val[crt_it].permissions, permissions, strlen(permissions));
			crt_it++;

			resource = strtok(NULL, delimiter);
			permissions = strtok(NULL, delimiter);
		}

		list_approvals[no_approvals].no_resources_w_permissions = crt_it;

		no_approvals++;
	}

	printf("%d\n", no_approvals);

	for (int i = 0; i < no_approvals; i++) {

		printf("Al %d-lea set de permisiuni:\n", i);

		for (int j = 0; j < list_approvals[i].no_resources_w_permissions; j++) {
			printf("resource: %s, permissions: %s\n", list_approvals[i].list_permissions_val[j].resource, list_approvals[i].list_permissions_val[j].permissions);
		}

	}

	fclose(fp);	
}


void read_input(char *filename_clients, char *filename_resources, char *filename_approvals) {
	read_known_users(filename_clients);
	read_resources(filename_resources);
	read_approvals(filename_approvals);
}

int
main (int argc, char **argv)
{
	if (argc != 5) {
		printf("Correct usage is: ./tema_server <fisier_clienti> <fisier_resurse> <fisier_aprobari> <valabiliate jetoane>\n");
		exit(1);
	}

	read_input(argv[1], argv[2], argv[3]);

	register SVCXPRT *transp;

	pmap_unset (CHEKPROG, CHECKVERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CHEKPROG, CHECKVERS, chekprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CHEKPROG, CHECKVERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CHEKPROG, CHECKVERS, chekprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CHEKPROG, CHECKVERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
