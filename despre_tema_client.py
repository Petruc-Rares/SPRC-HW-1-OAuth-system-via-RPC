# CLIENT:

# users is a list of structs: [{'user_id': 'user_id_value', 'access_token': 'access_token_value', 'refresh_token': 'refresh_token_value', 'perms': 'perms_value'}]


def request_authorization(user_id, auto_refresh):
    # this function is useful to call server and return result
    authz_token = result_rpc_call

    if authz_token == "USER_NOT_FOUND":
        print("USER_NOT_FOUND")
        return None
    
    return authz_token

def approve_request_token(authz_token):
    # this function is useful just to call server and return result
    pass

def request_access_token(user_id, authz_token, auto_refresh):
    # this function is useful to call server and return result
    access_token, refresh_token, availability_period = result_rpc_call

    if access_token = None:
        print("REQUEST_DENIED")
        return None, None, None
    
    print("<authz_token> -> <access_token>")

    # if refresh token
    if auto_refresh == 1:       
        print(",<refresh_token")

    return access_token, refresh_token, availability_period


# just on client
def execute_request_client(user_id, auto_refresh):
    authz_token = request_authorization(user_id, 0)

    if authz_token = None:
        return None, None, None

    # user found
    # now ask for signing of token and permissions
    authz_token, set_permissions = approve_request_token(authz_token)

    # token approved by user
    # now ask for access token
    return request_access_token(user_id, authz_token, auto_refresh)

def validate_delegated_action(user_id, action, resource, access_token):
    user_to_retrieve = [user for user in users if user['user_id'] == user_id][0]
    
    useful_variable = 0

    if user_to_retrieve['refresh_token'] != None and user_to_retrieve['access_token'].availability_period == 0:
        useful_variable = 1

    user_to_retrieve['authz_token'], user_to_retrieve['access_token'], user_to_retrieve['refresh_token'], availability_period, response = response_rpc

    if useful_variable:
        print("<new_authz_token> -> <new_access_token>")

    print(response)



def execute_operation_client(user_id, operation, option):

    if operation == "REQUEST":
        access_token, refresh_token, availability_period = execute_request_client(user_id, option)
    
        if access_token != None:
            return

        users.append({
            'user_id': user_id,
            'access_token':access_token,
            'refresh_token': refresh_token,
            'availability_period': availability_period
        })

    elif operation IN ("Read", "Insert", "Modify", "Delete", "Execute"):
        access_token = [user for user in users if user['user_id'] == user_id][0]['access_token']
        
        validate_delegated_action(user_id, operation, option, access_token)

    else:
        pass

    return 0