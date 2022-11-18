#!/bin/bash
#
# Exemplu rulare:
# ./check.sh 1   -> ruleaza test1
# ./check.sh 1 1 -> ruleaza test1 si afiseaza diferentele
# ./check.sh all -> ruleaza toate testele
#
# Completati/schimbati urmatoarele valori inainte de utilizare:
NO_OPERATIONS_TOKEN=(2 2 2 3 4 5 3)
SERVER_NAME="tema_server"
SERVER_PARAMS="tests/test$1/userIDs.db tests/test$1/resources.db tests/test$1/approvals.db"
CLIENT_NAME="tema_client"
CLIENT_PARAMS="tests/test$1/client.in"
SERVER_ADDR="localhost"

if [ $# -lt 1 ]; then
    echo "./check.sh testNo([0-7]|all) [showOutput([0-1])]"
    exit
fi

if [ "$SERVER_NAME" = "" ] || [ "$CLIENT_NAME" = "" ]; then
    echo "Change SERVER_NAME and CLIENT_NAME, and check SERVER_ADDR in check.sh file!"
    exit
fi

numberPattern='^[0-9]+$'
if [[ $1 =~ $numberPattern ]]; then
    ./$SERVER_NAME $SERVER_PARAMS ${NO_OPERATIONS_TOKEN[$i-1]} > server.out &
    SERVER_PID=$!
    sleep 1
    ./$CLIENT_NAME $SERVER_ADDR $CLIENT_PARAMS > client.out
    kill $SERVER_PID

    if [ $# -gt 1 ] && [ $2 -eq 1 ]; then
        diff server.out tests/test$1/expected_output/server.out
        if [[ $? = 1 ]]; then
            echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ SERVER OUTPUT DIFF"
            echo
        fi

        diff client.out tests/test$1/expected_output/client.out
        if [[ $? = 1 ]]; then
            echo "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ CLIENT OUTPUT DIFF"
            echo
        fi
    else
        diff server.out tests/test$1/expected_output/server.out > /dev/null
        diff client.out tests/test$1/expected_output/client.out > /dev/null
    fi

    diff server.out tests/test$1/expected_output/server.out > /dev/null
    if [[ $? = 0 ]]; then
        echo "Test $1 - Server Output: OK"
    else
        echo "Test $1 - Server Output: FAILED"
    fi

    diff client.out tests/test$1/expected_output/client.out > /dev/null
    if [[ $? = 0 ]]; then
        echo "Test $1 - Client Output: OK"
    else
        echo "Test $1 - Client Output: FAILED"
    fi
else
    for i in {1..7}
    do
        SERVER_PARAMS_ALL=${SERVER_PARAMS//testall/test$i}
        CLIENT_PARAMS_ALL=${CLIENT_PARAMS//testall/test$i}

        ./$SERVER_NAME $SERVER_PARAMS_ALL ${NO_OPERATIONS_TOKEN[$i-1]} > server.out &
        SERVER_PID=$!
        sleep 1
        ./$CLIENT_NAME $SERVER_ADDR $CLIENT_PARAMS_ALL > client.out
        kill $SERVER_PID

        diff server.out tests/test$i/expected_output/server.out > /dev/null
        if [[ $? = 0 ]]; then
            echo "Test $i - Server Output: OK"
        else
            echo "Test $i - Server Output: FAILED"
        fi

        diff client.out tests/test$i/expected_output/client.out > /dev/null
        if [[ $? = 0 ]]; then
            echo "Test $i - Client Output: OK"
        else
            echo "Test $i - Client Output: FAILED"
        fi
    done
fi