# Creator:   VPR
# Created:   February 1, 2022
# Updated:   February 1, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

export HOST="127.0.0.1"
export PORT=8001
export IPV4=1
export IPV6=0
export TIMEOUT_MS=0
export MAX_CONNECTIONS=5

if [ -f ./Bin/server.exe ];
then
    ./Bin/server.exe
else
    printf "'server.exe' not found.\n"
    exit
fi
