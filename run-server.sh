# Creator:   VPR
# Created:   February 1st, 2022
# Updated:   February 16th, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

export HOST="127.0.0.1"
export PORT=8001

export IPV4=0
export TIMEOUT_MS=60000
export MAX_CONNECTIONS=127
export MAX_THREADS=4

if [ -f ./Bin/utopia-server.exe ];
then
    ./Bin/utopia-server.exe
else
    printf "'server.exe' not found.\n"
    exit
fi
