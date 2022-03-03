# Creator:   VPR
# Created:   February 1st, 2022
# Updated:   February 16th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

export INTERNET_PROTOCOL=0
export PORT=8080

export TIMEOUT=30
export MAX_CONNECTIONS=127
export MAX_THREADS=$(nproc)
export N_THREADS=$(($(nproc) - 1))
export MEMORY_LIMIT=32768

export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

if [ -f ./Bin/utopia-server.exe ];
then
    ./Bin/utopia-server.exe
else
    printf "'server.exe' not found.\n"
    exit
fi
