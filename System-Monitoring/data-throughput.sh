#!/bin/bash

# Creator:    VPR
# Created:    March 6th, 2022
# Updated:    March 9th, 2022

# Description:
#     Uses lsblk, blkid, ioping, fio

set -e pipefail
set -e errexit
set -e nounset
set -e xtrace

LOG_DIR="logs"
LOG_FILE="data-throughput.log"

if ! [ ioping ]
then
    printf "'ioping' not installed\n"
    exit 1
elif ! [ fio ]
then
    printf "'fio' not installed\n"
    exit 1
fi

# Get lsblk stats
function lsblk-stats {
    printf "[lsblk]\n"           >> "${LOG_DIR}/${LOG_FILE}"
    lsblk                        >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n"                  >> "${LOG_DIR}/${LOG_FILE}"
}

# Get blkid stats          
function blkid-stats {
    printf "[blkid]\n"           >> "${LOG_DIR}/${LOG_FILE}"
    blkid                        >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n"                  >> "${LOG_DIR}/${LOG_FILE}"
}

# Print ioping test          
function ioping-test {
    IOPING_OUT="/tmp/ioping.out"
    ioping -Y -c10 -s16  .        > "${IOPING_OUT}"
    printf "[ioping]\n"          >> "${LOG_DIR}/${LOG_FILE}"
    tail -n 4 ${IOPING_OUT}      >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n"                  >> "${LOG_DIR}/${LOG_FILE}"
}

# Perform random reads from sda with 1Mb block size.
function read-sda {
    RANDREAD_FILE="fio_randread.out"
    printf "[fio-randread-sda]\n"             >> "${LOG_DIR}/${LOG_FILE}"
    fio --name=randread --filename=/dev/sda \
        --size=2Gb --rw=randread --bs=1M    \
        --direct=1 --numjobs=8              \
        --ioengine=libaio --iodepth=8       \
        --group_reporting --runtime=30      \
        --startdelay=30 > "/tmp/${RANDREAD_FILE}"

    awk '/IOPS/ {print $2 $3 $4}' "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    tail -n 2 "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n" >> "${LOG_DIR}/${LOG_FILE}"
}

# Perform random reads from sdb with 1Mb block size.
function read-sdb {
    RANDREAD_FILE="fio_randread.out"
    printf "[fio-randread-sdb]\n"             >> "${LOG_DIR}/${LOG_FILE}"
    fio --name=randread --filename=/dev/sdb \
        --size=2Gb --rw=randread --bs=1M    \
        --direct=1 --numjobs=8              \
        --ioengine=libaio --iodepth=8       \
        --group_reporting --runtime=30      \
        --startdelay=30 > "/tmp/${RANDREAD_FILE}"

    awk '/IOPS/ {print $2 $3 $4}' "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    tail -n 2 "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n" >> "${LOG_DIR}/${LOG_FILE}"
}

# Perform random reads from sdb with 1Mb block size.
function read-write {
    if ! [ -d read_write_test ];
    then
        mkdir -p read_write_test
    fi

    RANDREAD_FILE="fio_readwrite.out"
    printf "[fio-read-write]\n"             >> "${LOG_DIR}/${LOG_FILE}"
    fio --name=readwrite --filename=read_write_test \
        --size=1Gb --rw=rw --bs=1M                  \
        --direct=1 --numjobs=8                      \
        --ioengine=libaio --iodepth=8               \
        --group_reporting --runtime=30s             \
        --startdelay=30 > "/tmp/${RANDREAD_FILE}"

    awk '/IOPS/ {print $2 $3 $4}' "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    tail -n 2 "/tmp/${RANDREAD_FILE}" >> "${LOG_DIR}/${LOG_FILE}"
    printf "\n" >> "${LOG_DIR}/${LOG_FILE}"

    rm -fr read_write_test
}

#########################
##### Begin Testing #####
#########################

# Add date of test to log
printf "[date]\n"            >> "${LOG_DIR}/${LOG_FILE}"
date +"%Y-%m-%d %H:%M:%S %Z" >> "${LOG_DIR}/${LOG_FILE}"

lsblk-stats
blkid-stats
ioping-test

if [ "$(lsblk | grep 'sda')" ]; then read-sda; fi
if [ "$(lsblk | grep 'sdb')" ]; then read-sdb; fi

read-write
