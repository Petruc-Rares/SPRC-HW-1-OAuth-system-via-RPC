# SERVER:

# Those will be read from file:
user_ids_file = "<placeholder>"
permissions_resources="<placeholder>"
resources="<placeholder>"

# variable read from command prompt
availability_period=2

users=[]
authz_permissions=[]


# token is struct: ['token': 'token_value', 'availability_period': 'availability_period_value', 'signed': 'signed_value']
# resources is array of strings: ['Files', 'UserData', 'SystemData', ...]
# permissions_resources is array of struct: [{'resource': 'resource_value', 'permissions': 'permissions_value'}]
# user_ids_file is array of strings: ['user_id_1', ...]
# auth_permissions is array of structs: [{'authz_token': 'authz_token_value', 'permissions:' 'permissions'}]
# users is a list of structs: [{'user_id': 'user_id_value', 'access_token': 'access_token_value', 'refresh_token': 'refresh_token_value', 'perms': 'perms_value'}]

def func(x):
    pass

def operation_execute(id_ut, operation, option):
    pass

def request_authorization(user_id, auto_refresh):
    if auto_refresh:
        print("Begin <user_id> AUTHZ REFRESH")
    else:
        print("Begin <user_id> AUTHZ")

    if user_id not in user_ids_file:
        return "USER_NOT_FOUND"

    authz_token = func(user_id)

    # return authorization token
    return authz_token

def approve_request_token(authz_token):
    set_permissions = permissions_resources.next_row()

    if set_permissions == "*,-":
        authz_token.signed = False;
    else:
        authz_token.signed = True;

    authz_permissions.append({
        'authz_token': authz_token,
        'perms': set_permissions})

    return authz_token

def request_access_token(user_id, authz_token, auto_refresh):
    if authz_token.signed == False:
        return None, None, None

    # this might not be printed if refresh_token is used so you'll where you'll better write it
    print("  RequestToken = <authz_token>")

    # valid token    
    access_token  = func(authz_token)
    access_token.availability_period = availability_period

    refresh_token = None

    if auto_refresh == 1:
        refresh_token = func(refresh_token)

    print("  AccessToken= <access_token>")
    print("  RefreshToken = <refresh_token>")

    perms = [authz_permission for authz_permission in authz_permissions if authz_permission['authz_token'] == authz_token][0]['perms']

    users.append({
        'user_id': user_id,
        'access_token':access_token,
        'refresh_token': refresh_token,
        'perms': perms,
        })

    # TODO if time: Now you can delete authz_permission containing authz_token

    return access_token, refresh_token, availability_period

def validate_delegated_action(user_id, action, resource, access_token):
    user_to_retrieve = [user for user in users if user['user_id'] == user_id][0]

    # token is not associated with user_id in server
    # or user not found
    if user_to_retrieve["access_token"] != access_token or user_to_retrieve["access_token"] == None:
        if access_token == None:
            print("DENY (<action>,<resource>,,0)")
        else:
            print("DENY (<action>,<resource>,<access_token>,<access_token.availability_period>)")

        return None, None, None, 0, "PERMISSION_DENIED"
    
    if user_to_retrieve["access_token"].availability_period == 0:
        # check for auto-refresh
        if user_to_retrieve["refresh_token"] != None:
            new_authz_token = request_authorization(user_id, 1)
            new_access_token, new_refresh_token, availability_period = request_access_token(user_id, new_authz_token, 1)

            user_to_retrieve["authz_token"] = new_authz_token
            user_to_retrieve["access_token"] = new_access_token
            user_to_retrieve["refresh_token"] = new_refresh_token

        else:
            print("DENY (<action>, <resource>,, 0)")
            return user_to_retrieve["authz_token"], user_to_retrieve["access_token"], user_to_retrieve["refresh_token"], 0, "TOKEN_EXPIRED"

    user_to_retrieve["access_token"].availability_period--

    if resource not in resources.keys:
        print("DENY (<action>, <resource>, user_to_retrieve['access_token'], user_to_retrieve['access_token'].availability_period")
        return user_to_retrieve["authz_token"], user_to_retrieve["access_token"], user_to_retrieve["refresh_token"], user_to_retrieve["access_token"].availability_period,"RESOURCE_NOT_FOUND"

    if action not in user_to_retrieve["perms"]['permissions']:
        print("DENY (<action>, <resource>, user_to_retrieve['access_token'], user_to_retrieve['access_token'].availability_period")
        return user_to_retrieve["authz_token"], user_to_retrieve["access_token"], user_to_retrieve["refresh_token"], user_to_retrieve["access_token"].availability_period,"OPERATION_NOT_PERMITTED"

    
    print("PERMIT (<action>, <resource>, user_to_retrieve['access_token'], user_to_retrieve['access_token'].availability_period")

    return user_to_retrieve["authz_token"], user_to_retrieve["access_token"], user_to_retrieve["refresh_token"], user_to_retrieve["access_token"].availability_period, "PERMISSION_GRANTED"