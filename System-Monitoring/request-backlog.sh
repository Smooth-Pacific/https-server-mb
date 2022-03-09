#!/bin/bash

# Creator:    VPR
# Created:    March 9th, 2022
# Updated:    March 9th, 2022

LOG_DIR="logs"
LOG_FILE="backlog.log"

function send-test {
    _res=$(curl -v --digest -u username:password --cacert ~/certs/server_ca/certs/ca-chain-bundle.cert.pem https://127.0.0.1:8080/ 2>&1)
    _code=$?
    netstat -i >> "${LOG_DIR}/${LOG_FILE}"
    if [ $_code -ne 0 ];
    then
        printf "Failed to send request. Return code = ${_code}\n"
    fi
}

for i in {1..100};
do
    printf "Sending test ${i}\n"
    send-test "$i" &
done
