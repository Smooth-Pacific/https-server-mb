# Creator:   VPR
# Created:   February 1st, 2022
# Updated:   March 5, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

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

if [ -f ./Bin/utopia-server.exe ];
then
    exec Bin/utopia-server.exe
else
    printf "'server.exe' not found.\n"
    exit
fi
