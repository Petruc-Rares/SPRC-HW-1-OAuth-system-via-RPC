# SERVER:

# Those will be read from file:
user_ids_file = "<placeholder>"
permissions_resources="<placeholder>"
resources="<placeholder>"

# variable read from command prompt
availability_period=2

users=[]
authz_permissions=[]


# token is struct: ['token': 'token_value', 'availability_period': 'availability_period_value']
# resources is array of strings: ['Files', 'UserData', 'SystemData', ...]
# permissions_resources is array of struct: [{'resource': 'resource_value', 'permission_resource': 'permission_resource_value'}]
# user_ids_file is array of strings: ['user_id_1', ...]
# auth_permissions is array of structs: [{'authz_token': 'authz_token_value', 'permissions:' 'permissions'}]


def func(x):
    pass

def operation_execute(id_ut, operation, option):
    pass

def request_authorization(user_id):
    print("Begin <user_id> AUTHZ")

    if user_id not in user_ids_file:
        return "USER_NOT_FOUND"

    # return authorization token
    return func(user_id)

def approve_request_token(authz_token):
    set_permissions = permissions_resources.next_row()

    if set_permissions == "*,-":
        authz_token.signed = False;
    else:
        authz_token.signed = True;

    authz_permissions.append({
        'authz_token': authz_token,
        'perms': set_permissions})

    return authz_token, set_permissions

def request_access_token(user_id, authz_token, option):
    print("  RequestToken = <authz_token>")
    if authz_token.signed == False:
        return None, None, None

    # valid token    
    access_token  = func(authz_token)
    access_token.availability_period = availability_period

    refresh_token = None

    if option == 1:
        refresh_token = func(refresh_token)

    print("  AccessToken= <access_token>")
    print("  RefreshToken = <refresh_token>")

    perms = [authz_permission for authz_permission in authz_permissions if authz_permission['authz_token'] == authz_token][0]['perms']

    users.append({
        'user_id': user_id,
        'access_token':access_token,
        'refresh_token': refresh_token,
        'perms': perms})

    # TODO if time: Now you can delete authz_permission containing authz_token

    return access_token, refresh_token, availability_period