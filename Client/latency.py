#!/usr/bin/env python3

# Creator: VPR
# Created: March 4th, 2022
# Updated: March 6th, 2022

import os
import sys

from requests.auth import HTTPDigestAuth
from pathlib import Path

from requests import (
    Session
)

from typing import (
    Union,
    Tuple
)

#####################
## Setup variables ##
#####################

MICRO_MS_CONSTANT = 1000

AUTH_USER="username"
AUTH_PASS="password"

HOST = "127.0.0.1" 
PORT = 8080

CERT_MEM = str(Path.home()) + "/certs/server_ca/certs/ca-chain-bundle.cert.pem"

####################
## Test functions ##
####################

def sendGetRequestToContent(n_iterations: int) -> Tuple[Union[int, float], Union[int, float], float]:
    total_time = 0
    min_time   = 1e6
    max_time   = -1e6

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test "/" endpoint (root) for n_iterations
    for _ in range(n_iterations):
        resp = s.get(f"https://{HOST}:{PORT}/content")

        total_time += resp.elapsed.microseconds

        if resp.elapsed.microseconds < min_time:
            min_time = resp.elapsed.microseconds
        if resp.elapsed.microseconds > max_time:
            max_time = resp.elapsed.microseconds
    s.close()

    return ( min_time / MICRO_MS_CONSTANT, max_time / MICRO_MS_CONSTANT, (total_time/(n_iterations * MICRO_MS_CONSTANT)) )

def sendPutRequestToContent(n_iterations: int) -> Tuple[Union[int, float], Union[int, float], float]:
    total_time = 0
    min_time   = 1e6
    max_time   = -1e6

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test "/" endpoint (root) for n_iterations
    for _ in range(n_iterations):
        resp = s.put(f"https://{HOST}:{PORT}/content", 'A' * 1_000_000)

        total_time += resp.elapsed.microseconds

        if resp.elapsed.microseconds < min_time:
            min_time = resp.elapsed.microseconds
        if resp.elapsed.microseconds > max_time:
            max_time = resp.elapsed.microseconds
    s.close()

    return ( min_time / MICRO_MS_CONSTANT, max_time / MICRO_MS_CONSTANT, (total_time/(n_iterations * MICRO_MS_CONSTANT)) )

def sendPostRequestToContent(n_iterations: int) -> Tuple[Union[int, float], Union[int, float], float]:
    total_time = 0
    min_time   = 1e6
    max_time   = -1e6

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test "/" endpoint (root) for n_iterations
    for _ in range(n_iterations):
        resp = s.post(f"https://{HOST}:{PORT}/content", 'A' * 1_000_000)

        total_time += resp.elapsed.microseconds

        if resp.elapsed.microseconds < min_time:
            min_time = resp.elapsed.microseconds
        if resp.elapsed.microseconds > max_time:
            max_time = resp.elapsed.microseconds
    s.close()

    return ( min_time / MICRO_MS_CONSTANT, max_time / MICRO_MS_CONSTANT, (total_time/(n_iterations * MICRO_MS_CONSTANT)) )

def sendDeleteRequestToContent(n_iterations: int) -> Tuple[Union[int, float], Union[int, float], float]:
    total_time = 0
    min_time   = 1e6
    max_time   = -1e6

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test "/" endpoint (root) for n_iterations
    for _ in range(n_iterations):
        resp = s.delete(f"https://{HOST}:{PORT}/content")

        total_time += resp.elapsed.microseconds

        if resp.elapsed.microseconds < min_time:
            min_time = resp.elapsed.microseconds
        if resp.elapsed.microseconds > max_time:
            max_time = resp.elapsed.microseconds
    s.close()

    return ( min_time / MICRO_MS_CONSTANT, max_time / MICRO_MS_CONSTANT, (total_time/(n_iterations * MICRO_MS_CONSTANT)) )

if __name__ == "__main__":

    # Set global variables
    if os.environ.get("INTERNET_PROTOCOL") is not None:
        if os.environ.get("INTERNET_PROTOCOL") == 1:
            HOST = "[::1]"
        else:
            HOST = "127.0.0.1"
    if os.environ.get("PORT"):
        PORT = os.environ.get("PORT")
    if os.environ.get("AUTH_USER"):
        AUTH_USER = os.environ.get("AUTH_USER")
    if os.environ.get("AUTH_PASS"):
        AUTH_PASS = os.environ.get("AUTH_PASS")
    if os.environ.get("CERT_MEM"):
        CERT_MEM = os.environ.get("CERT_MEM")

    # Check if server is running
    if os.system(f"nc -vz {HOST} {PORT}"):
        sys.stderr.write("Could not ping server...\n")
        sys.exit(1)

    # Being testing
    n_iterations = 100
    min_time, max_time, average_time = sendGetRequestToContent(n_iterations)
    print(f"Testing GET request to '/content'",
          f"Min time\t: {min_time} ms",
          f"Max time\t: {max_time} ms",
          f"Average time\t: {average_time} ms\n",
          sep="\n")

    n_iterations = 100
    min_time, max_time, average_time = sendPutRequestToContent(n_iterations)
    print(f"Testing PUT request to '/content'",
          f"Min time\t: {min_time} ms",
          f"Max time\t: {max_time} ms",
          f"Average time\t: {average_time} ms\n",
          sep="\n")

    n_iterations = 100
    min_time, max_time, average_time = sendPostRequestToContent(n_iterations)
    print(f"Testing POST request to '/content'",
          f"Min time\t: {min_time} ms",
          f"Max time\t: {max_time} ms",
          f"Average time\t: {average_time} ms\n",
          sep="\n")

    n_iterations = 100
    min_time, max_time, average_time = sendDeleteRequestToContent(n_iterations)
    print(f"Testing DELETE request to '/content'",
          f"Min time\t: {min_time} ms",
          f"Max time\t: {max_time} ms",
          f"Average time\t: {average_time} ms\n",
          sep="\n")
