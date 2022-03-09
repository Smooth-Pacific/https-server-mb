#!/bin/bash

# Creator:   VPR
# Created:   March 9th, 2022
# Updated:   March 9th, 2022

#LOG_DIR="logs"
#LOG_FILE="system-monior.log"

function system-monitoring-tests {
    ./System-Monitoring/apm.sh
    ./System-Monitoring/data-throughput.sh
    ./System-Monitoring/request-backlog.sh
}

system-monitoring-tests # >> "${LOG_DIR}/${LOG_FILE}"
