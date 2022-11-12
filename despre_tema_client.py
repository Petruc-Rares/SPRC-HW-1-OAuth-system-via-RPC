# CLIENT:

def request_authorization(user_id):
    # this function is useful to call server and return result
    authz_token = result_rpc_call

    if authz_token == "USER_NOT_FOUND":
        print("USER_NOT_FOUND")
        return None
    
    return authz_token

def approve_request_token(authz_token):
    # this function is useful just to call server and return result
    pass

def request_access_token(user_id, authz_token, option):
    # this function is useful to call server and return result
    access_token, refresh_token, availability_period = result_rpc_call

    if access_token = None:
        print("REQUEST_DENIED")
        return None, None, None
    
    print("<authz_token> -> <access_token>")

    # if refresh token
    if option == 1:       
        print(",<refresh_token")

    return access_token, refresh_token, availability_period


# just on client
def execute_request_client():
    authz_token = request_authorization(user_id)

    if authz_token = None:
        return None, None, None

    # user found
    # now ask for signing of token and permissions
    authz_token, set_permissions = approve_request_token(authz_token)

    # token approved by user
    # now ask for access token
    return request_access_token(user_id, authz_token, option)

# just on client
def execute_rimdx_client():
    # TODO: check smth like if refresh_token is not None and availability for the token
    # is 0 => execute_request_client()

def execute_operation_client(user_id, operation, option):

    if operation == "REQUEST":
        access_token, refresh_token, availability_period = execute_request_client()
    elif operation IN ("Read", "Insert", "Modify", "Delete", "Execute"):
        execute_rimdx_client()
    else:
        pass

    return 0