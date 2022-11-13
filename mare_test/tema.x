/* contains token value and the number of operations available associated with it*/
struct token{
    string token_value<>;
    int no_available_operations;
    int user_signed;
};

/* contains resource with its associated permissions */
struct resource_permissions{
    string resource<>;
    string permissions<>;
};


/* return type for approve_request_token procedure */
struct approve_request_token_response {
    token authz_token;
    resource_permissions list_permissions<>;
};

/* parameter in request_authorization procedure */
struct request_authorization_param {
    string user_id<>;
    int auto_refresh;
};

/* parameter in request_access_token procedure */
struct request_access_token_param {
    string user_id<>;
    token authz_token;
    int auto_refresh;
};

/* return type for request_access_token procedure */
struct request_access_token_response {
    token access_token;
    token refresh_token;
    int fail;
};

/* parameter in validate_delegated_action procedure */
struct validate_delegated_action_param {
    string user_id<>;
    string action<>;
    string resource<>;
    token access_token;
};

program CHEKPROG {
  version CHECKVERS {
    token request_authorization(request_authorization_param) = 1;
    approve_request_token_response approve_request_token(token) = 2;
    request_access_token_response request_access_token(request_access_token_param) = 3;
    string validate_delegated_action(validate_delegated_action_param) = 4;
  } = 1;
} = 0x31234567;