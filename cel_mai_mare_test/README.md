## Definirea interfetei care expune tipurile de date si metodele aplicatiei ##

## Descrierea specificiatiilor de functionare (prin comentarii in interfata) pentru toate tipurile de date si functiile definite in interfata ##

## Implementarea aplicatiei server ##
### Gestionarea bazei de date cu informatiile utilizatorilor si ale clientilor ###
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

### Procesul de autorizare a clientilor ###

### Procesul de reinnoire a jetoanelor de acces ###

### Procesul de verificare a operatiilor executate de clienti ###

### Procesul utilizatorului final ed aprobare a cererii de autorizare ###

## Implementatarea aplicatiei client ##
### Procesul de autorizare (obtinerea jetoanelor de acces, fara reinnoire) ###

### Procesul de reinnoire a jetoanelor de acces ###

### Executa operatiile descrise in fisier ###


## Testare

Se va preciza cum s-a schimbat check.sh (sleep, nou array pentru # de operatii) si ca am adaugat enter la final in liniile de output din expected_output. Totodata, sa zici ca ai scos din main-ul de la server optiunea de printf buferat ca sa te asiguri ca se va face scrierea in fisierul in care se redirecteaza iesirea.

## Feedback