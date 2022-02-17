# Creator:   VPR
# Created:   February 16th, 2022
# Updated:   February 16th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

# Run without setting environment variables
if [ -f ./Server/Bin/run-tests ];
then
    ./Server/Bin/run-tests
else
    printf "'run-tests' not found.\n"
    exit
fi

export SET=1

export HOST="127.0.0.1"
export PORT=8080

export IPV4=0
export MAX_CONNECTIONS=127
export MAX_THREADS=8
export N_THREADS=4
export TIMEOUT=30
export MEMORY_LIMIT=32768

export MEM_CERT="${HOME}/certs/server_ca/certs/smoothstack_server.crt"
export MEM_KEY="${HOME}/certs/server_ca/private/smoothstack_server.key"

# Run with environment variables set
if [ -f ./Server/Bin/run-tests ];
then
    ./Server/Bin/run-tests
else
    printf "'run-tests' not found.\n"
    exit
fi
