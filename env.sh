# Creator:   VPR
# Created:   February 1, 2022
# Updated:   February 1, 2022

set -e errexit
set -e pipefail
set -e nounset

export HOST="127.0.0.1"
export PORT=8080
export MAX_CONNECTIONS=5
export TIMEOUT_MS=0

if [ -f ./Bin/server.exe ];
then
    ./Bin/server.exe
else
    printf "'server.exe' not found.\n"
fi
