# README TEMA 1 SPRC &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 344C1 PETRUC RARES # 

## Definirea interfetei care expune tipurile de date si metodele aplicatiei ##
Structura de baza a fisierelor cu extensia ".c" este realizata prin rularea "rpcgen -C -a tema.x"
## Descrierea specificiatiilor de functionare (prin comentarii in interfata) pentru toate tipurile de date si functiile definite in interfata ##
Exista comentarii in fisierul interfata tema.x
## Implementarea aplicatiei server ##
### *Gestionarea bazei de date cu informatiile utilizatorilor si ale clientilor* ###
**user_database** contine informatii despre identificatorii, tokenurile de acces, refresh (daca exista) si permisiuni ale utilizatorilor.

**user_database** este gestionat mai ales in **tema_server.c**, iar cateva exemple de utilizare ar fi:

*adaugarea unui nou utilizator in baza de date*:
```c
    user_database = realloc(user_database, (size_database + 1) * sizeof(user_db));
    user_database[size_database].user_id = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
    user_database[size_database].access_token.token_value = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
    user_database[size_database].refresh_token.token_value = (char *) calloc(SIZE_USER_ID + 1,sizeof(char));
    strncpy(user_database[size_database].user_id, argp->user_id, SIZE_USER_ID);
    size_database++;
```

*umplerea campurilor asociate unui utilizator in baza de date*:
```c
	strncpy(user_database[position_to_add].access_token.token_value, result.access_token.token_value, SIZE_USER_ID);
	user_database[position_to_add].access_token.no_available_operations = no_operations_per_token;
	strncpy(user_database[position_to_add].refresh_token.token_value, result.refresh_token.token_value, SIZE_USER_ID);
    ...
    user_database[position_to_add].list_permissions_val = authz_token_permissions_list[i].list_permissions_val;
    user_database[position_to_add].list_permissions_len = authz_token_permissions_list[i].list_permissions_len;

```

si evident este folosit in *operatiile delegate de client*, pentru:
- verificarea permisiunilor pentru anumite resurse
- scaderea numarului de operatii asociate cu un token
- compararea tokenurilor de acces existente din baza de date cu cel primit de la client
- etc.

### *Procesul de autorizare a clientilor* ###
Este reprezentat de functii definite in **tema_server.c**, apelate de client, anume:
```c
token *request_authorization_1_svc(request_authorization_param *argp, struct svc_req *rqstp)
approve_request_token_response *approve_request_token_1_svc(token *argp, struct svc_req *rqstp)
request_access_token_response *request_access_token_1_svc(request_access_token_param *argp, struct svc_req *rqstp)
```
Functiile respecta denumirea si descrierea din documentul pdf asociat temei.

### *Procesul de reinnoire a jetoanelor de acces* ###
Incepe prin urmatoarea secventa reprezentativa din functia **request_access_token_1_svc**:
```c
if ((position_to_add != size_database) && (strncmp(argp->authz_token.token_value, user_database[position_to_add].refresh_token.token_value, SIZE_USER_ID) == 0)) {
		printf("BEGIN %s AUTHZ REFRESH\n", argp->user_id);
	}
```
Aceasta verifica daca este vorba de un user deja existent in baza de date, care are valoarea tokenului de autentificare egala cu valoarea tokenului de refresh cunoscuta in baza de date. (ceea ce inseamna ca, clientul si-a incheiat sesiunea cu vechiul access_token si il folosete acum pe cel de refresh_token)

Mai departe, pasii sunt aceeasi ca in cazul generarii token access-ului in mod normal.

### *Procesul de verificare a operatiilor executate de clienti* ###
Implementarea verificarii operatiilor executate de client se realizeaza in:
```c
char **validate_delegated_action_1_svc(validate_delegated_action_param *argp, struct svc_req *rqstp)
```
si respecta intocmai ordinea expusa in documentul pdf asociat temei.

### *Procesul utilizatorului final de aprobare a cererii de autorizare* ###
Reprezentat prin secventa urmatoare din functia **approve_request_token_1_svc**:
```c
	// check no permissions
	if ((strncmp(list_approvals[crt_approval_no].list_permissions_val[0].resource, "*", 1) == 0) &&
		(strncmp(list_approvals[crt_approval_no].list_permissions_val[0].permissions, "-", 1) == 0)) {
		result.authz_token.user_signed = 0;
	} else {
		result.authz_token.user_signed = 1;
	}
```
Ulterior verificarii permisiunilor utilizatorului final (simulate prin citirea din fisierul approvals.db), se construieste un vector de un soi de dictionare cu cheile egale cu valoarea tokenului de autorizare, iar valorile reprezentand permisinile asociate acelei chei de autorizare.

## Implementatarea aplicatiei client ##
### Procesul de autorizare (obtinerea jetoanelor de acces, fara reinnoire) ###
Sunt apelate din:
```c
request_access_token_response execute_request_client(char *user_id, int auto_refresh, CLIENT* clnt)
```
pe rand procedurile din server:
- request_authorization_1
- approve_request_token_1
- request_access_token_1
  
### Procesul de reinnoire a jetoanelor de acces ###
Se execuat in functia urmatoare:
```c
int check_refresh_last_operation(token access_token, char *user_id, CLIENT* clnt)
```
unde se verifica daca clientul are asociate 0 operatii cu respectivul access_token si un refresh_token valid, caz in care datele sale de acces sunt regenerate cu ajutorul refresh_token-ului iar noile date de acces ii sunt alocate.

### Executa operatiile descrise in fisier ###
Da, se executa operatiile in ordinea din fisier, structura generala a codului ce releva asta fiind:

```c
FILE *fp = fopen(filename_operations, "r");
...
while (fgets(buf, BUFSIZE, fp)) {
    if (strncmp(operation, "REQUEST", strlen(operation)) == 0) {
        ...       
    } else {
        ...
    }
}
```

## Testare

- Am adaugat enter la final de fisiere ".out" din folderel expected_output al tuturor folderelor de test1..test7.

- Am scos optiunea de bufferaj la printf prin:
 ```c
 setvbuf(stdout, NULL, _IONBF, 0);
 ```

- Am adaugat in fisierul **check.sh** numarul de operatii per token (*NO_OPERATIONS_TOKEN=(2 2 2 3 4 5 3)*) pentru fiecare test analizand continutul fisierelor server.out de la fiecare test

lucru necesar pentru ca in urma rularii scriptului check.sh, scrierea outputului executabilului de server sa se realizeze in fisierul de output

## Verificare Tema
Nu trebuie decat sa dati **make** si sa rulati fisierul **check.sh** asa cum este specificat in
cadrul lui, liniile 4, 5, 6.

## Feedback
Tema interesanta; au fost pe alocuri neconcordante intre textul pdf-ului si pozele din el si schema logica atasata, dar dupa ce am luat-o la pasi marunti si cu ajutorul asistentilor pe forum, am dus-o la bun sfarsit.