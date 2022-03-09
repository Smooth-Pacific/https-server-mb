# Creator:   VPR
# Created:   March 3rd, 2022
# Updated:   March 3rd, 2022

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

(
    cd ./3rd-party/libhttpserver
    ./bootstrap
    mkdir -p build
    cd build
    ../configure
    make
    sudo make install
)
