#!/bin/bash

# Creator:   VPR
# Created:   February 16th, 2022
# Updated:   February 16th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

## Run without setting environment variables
#if [ -f ./Server/Bin/run-tests ];
#then
    #./Server/Bin/run-tests
#else
    #printf "'run-tests' not found.\n"
    #exit
#fi

export SET=1

export AUTH_USER="username"
export AUTH_PASS="password"

export INTERNET_PROTOCOL=0
export USE_DUAL_STACK=0
export PORT=8080

export MAX_THREAD_STACK_SIZE=0
export MAX_THREADS=$(( $(nproc) * 4 ))
export N_THREADS=$(( $(nproc) - 1 ))

export CONTENT_SIZE_LIMIT=-1
export PER_CONNECTION_IP=10
export MAX_CONNECTIONS=127
export MEMORY_LIMIT=32768
export TIMEOUT=30

export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

function python-tests {
    if [ -f ./Client/server-test.py ];
    then
        #python3 Client/server-test.py
        python3 Client/latency.py
    fi
}

function server-tests {
    if [ -f ./Server/Bin/run-tests ];
    then
        ./Server/Bin/run-tests
    else
        printf "'run-tests' not found.\n"
        exit
    fi
}

python-tests
#server-tests
