#!/bin/bash

# Creator:   VPR
# Created:   February 16th, 2022
# Updated:   March 6th, 2022

# Description:
#     Testing thingy-majingy

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

LOG_DIR="logs"
LOG_FILE="tests.log"

###############################################
##### DEFAULT ENVIRONMENT VARIABLES START #####
###############################################

#export AUTH_USER="username"
#export AUTH_PASS="password"

#export INTERNET_PROTOCOL=0
#export USE_DUAL_STACK=0
#export PORT=8080

#export MAX_THREAD_STACK_SIZE=0
#export MAX_THREADS=$(( $(nproc) * 4 ))
#export N_THREADS=$(( $(nproc) - 1 ))

#export CONTENT_SIZE_LIMIT=-1
#export PER_CONNECTION_IP=10
#export MAX_CONNECTIONS=127
#export MEMORY_LIMIT=32768
#export TIMEOUT=30

#export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
#export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

#############################################
##### DEFAULT ENVIRONMENT VARIABLES END #####
#############################################

function python-tests {
    if [ -f ./Client/server-test.py ];
    then
        export AUTH_USER="username"
        export AUTH_PASS="password"
        export INTERNET_PROTOCOL=0
        export USE_DUAL_STACK=0
        export PORT=8080
        export MAX_THREAD_STACK_SIZE=0
        export MAX_THREADS=$(( $(nproc) * 4 ))
        export N_THREADS=$(( $(nproc) - 1 ))
        export CONTENT_SIZE_LIMIT=$(( 1024 * 1024 * 100))
        export PER_CONNECTION_IP=10
        export MAX_CONNECTIONS=127
        export MEMORY_LIMIT=32768
        export TIMEOUT=30
        export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
        export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

        python3 ./Client/server-test.py
        python3 ./Client/latency.py

        unset AUTH_USER
        unset AUTH_PASS
        unset INTERNET_PROTOCOL
        unset USE_DUAL_STACK
        unset PORT
        unset MAX_THREAD_STACK_SIZE
        unset MAX_THREADS
        unset N_THREADS
        unset CONTENT_SIZE_LIMIT
        unset PER_CONNECTION_IP
        unset MAX_CONNECTIONS
        unset MEMORY_LIMIT
        unset TIMEOUT
        unset MEM_CERT
        unset MEM_KEY
    fi
}

function server-test-one {
    export TEST_MODE=1
    unset AUTH_USER
    unset AUTH_PASS
    unset INTERNET_PROTOCOL
    unset USE_DUAL_STACK
    unset PORT
    unset MAX_THREAD_STACK_SIZE
    unset MAX_THREADS
    unset N_THREADS
    unset CONTENT_SIZE_LIMIT
    unset PER_CONNECTION_IP
    unset MAX_CONNECTIONS
    unset MEMORY_LIMIT
    unset TIMEOUT
    set MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
    set MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

    exec ./Bin/utopia-server-tests.exe

    unset TEST_MODE
    unset AUTH_USER
    unset AUTH_PASS
    unset INTERNET_PROTOCOL
    unset USE_DUAL_STACK
    unset PORT
    unset MAX_THREAD_STACK_SIZE
    unset MAX_THREADS
    unset N_THREADS
    unset CONTENT_SIZE_LIMIT
    unset PER_CONNECTION_IP
    unset MAX_CONNECTIONS
    unset MEMORY_LIMIT
    unset TIMEOUT
    export MEM_CERT
    export MEM_KEY
}

function server-test-two {
    export TEST_MODE=2
    export AUTH_USER="username"
    export AUTH_PASS="password"
    export INTERNET_PROTOCOL=0
    export USE_DUAL_STACK=0
    export PORT=8081
    export MAX_THREAD_STACK_SIZE=0
    export MAX_THREADS=$(( $(nproc) * 4 ))
    export N_THREADS=$(( $(nproc) - 1 ))
    export CONTENT_SIZE_LIMIT=$(( 1024 * 1024 * 100))
    export PER_CONNECTION_IP=10
    export MAX_CONNECTIONS=127
    export MEMORY_LIMIT=32768
    export TIMEOUT=30
    export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
    export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

    exec ./Bin/utopia-server-tests.exe

    unset TEST_MODE
    unset AUTH_USER
    unset AUTH_PASS
    unset INTERNET_PROTOCOL
    unset USE_DUAL_STACK
    unset PORT
    unset MAX_THREAD_STACK_SIZE
    unset MAX_THREADS
    unset N_THREADS
    unset CONTENT_SIZE_LIMIT
    unset PER_CONNECTION_IP
    unset MAX_CONNECTIONS
    unset MEMORY_LIMIT
    unset TIMEOUT
    unset MEM_CERT
    unset MEM_KEY
}

function server-tests {
    if [ -f ./Bin/utopia-server-tests.exe ];
    then
        server-test-one
        server-test-two
    else
        printf "'run-tests' not found.\n"
        exit 1
    fi
}

#######################
##### Main Script #####
#######################


if ! [ -f ./Bin/utopia-server.exe ];
then
    printf "'utopia-server.exe' not found.\n"
    exit 1
elif ! [ -f ./Bin/utopia-server-tests.exe ];
then
    printf "'utopia-server-tests.exe' not found.\n"
    exit 1
fi

if ! [ "$(ps -e | grep 'utopia-server')" ];
then
    printf "Server is not currently running..."
    exit 1
fi

python-tests  > "${LOG_DIR}/${LOG_FILE}"
server-tests >> "${LOG_DIR}/${LOG_FILE}"
