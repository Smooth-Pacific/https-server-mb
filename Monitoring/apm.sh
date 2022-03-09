#!/bin/bash

# Creator:    VPR
# Created:    March 5th, 2022
# Updated:    March 5th, 2022

# Description:
#     Uses valgrind

SERVER_SCRIPT="run-server.sh"
LOG_DIR="logs"
LOG_FILE="valgrind.log"

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file="${LOG_DIR}/${LOG_FILE}" "./${SERVER_SCRIPT}"
