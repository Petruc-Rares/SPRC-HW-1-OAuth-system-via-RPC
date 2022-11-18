/* generic token containing info relevant to authz_token, access_token and refresh_token */
struct token{
    /* field used in any of the 3 mentioned above */
    string token_value<>;
    /* field used for access_token to mark how many operations can be done using it */
    /* also used for marking invalid token; in that case it is equal to -1 */
    int no_available_operations;
    /* equals to 0 (No) if approvals given by user are "*,-", otherwise equals to 1 (Yes) for the scope of this app */
    int user_signed;
};

/* contains resource with its associated permissions */
struct resource_permissions{
    /* name of the resource */
    string resource<>;
    /* permissions associated with the above resource */
    string permissions<>;
};


/* return type for approve_request_token procedure */
/* as mentioned in homework guide: "Primeste jetonul pt autorizarea cererii si ii ataseaza setul de permisiuni pt fiecare resursa disponibila pe server" */
struct approve_request_token_response {
    /* the token signed or not by user */
    token authz_token;
    /* list of resources and permissions given by the user */
    resource_permissions list_permissions<>;
};

/* parameter in request_authorization procedure */
/* as mentioned in homework guide: "Primeste de la client ID-ul asociat utilizatorului" */
struct request_authorization_param {
    string user_id<>;
};

/* parameter in request_access_token procedure */
/* as mentioned in homework guide: "Primeste de la client ID-ul utilizatorului si jetonul pentru autorizarea cererii de acces" */
/* and as shown in the "schema_logica.png" the authorization token can be signed or not; also option to specify whether */
/* refresh_token is wanted or not is present */
struct request_access_token_param {
    string user_id<>;
    token authz_token;
    /* 0 if refresh_token is not wanted; 1 otherwise */
    int auto_refresh;
};

/* return type for request_access_token procedure */
struct request_access_token_response {
    token access_token;
    token refresh_token;
    /* marks whether authz_token is valid or not (0 - No) (1 - Yes) */
    int fail;
};

/* parameter in validate_delegated_action procedure */
struct validate_delegated_action_param {
    /* tipul operatiei */
    string action<>;
    /* resursa accesata */
    string resource<>;
    /* jetonul de acces */
    token access_token;
};

program CHEKPROG {
  version CHECKVERS {
    /* returns authorization token if user exists in userIDs.db */
    token request_authorization(request_authorization_param) = 1;
    /* simulation of server-user interaction; provides permissions and signs (or not) the authorization token provided */
    approve_request_token_response approve_request_token(token) = 2;
    /* first checks validity of authz_token provided in param; if valid computes access_token and eventually refresh_token if auto_refresh = 1;  */
    request_access_token_response request_access_token(request_access_token_param) = 3;
    /* performs any action specified by client on server and return the result of the action */
    string validate_delegated_action(validate_delegated_action_param) = 4;
  } = 1;
} = 0x31234567;