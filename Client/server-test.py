#!/usr/bin/env python3

# Creator: VPR
# Created: March 4th, 2022
# Updated: March 4th, 2022

# Notes:
#    Uses netcat

import os
import sys

from requests.auth import HTTPDigestAuth
from threading import Thread
from pathlib import Path

from requests import (
    Session
)

# from typing import (
    # Tuple
# )

#####################
## Setup variables ##
#####################

AUTH_USER="username1"
AUTH_PASS="password1"

HOST = "127.0.0.1" 
PORT = 8080

# CERT_MEM="/usr/local/share/ca-certificates/smoothstack_root.crt"
CERT_MEM = str(Path.home()) + "/certs/server_ca/certs/ca-chain-bundle.cert.pem"

####################
## Test functions ##
####################

def sendGetRequestToRoot() -> None:
    global n_passed, n_failed

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test "/" endpoint (root)
    resp = s.get(f"https://{HOST}:{PORT}/")
    s.close()

    if resp.status_code == 200:
        n_passed += 1
    else:
        n_failed += 1

def sendGetRequestToContent() -> None:
    global n_passed, n_failed

    s = Session()
    s.auth = HTTPDigestAuth(username=AUTH_USER, password=AUTH_PASS)
    s.verify = CERT_MEM

    # Test GET "/content" endpoint (root)
    resp = s.get(f"https://{HOST}:{PORT}/content")

    if resp.status_code == 200 and resp.text.strip() == "This is an example of a plain text resource.":
        n_passed += 1
    else:
        n_failed += 1

    # Test PUT "/content" endpoint (root)
    resp = s.put(f"https://{HOST}:{PORT}/content", "A" * 100_000)

    if resp.status_code == 200:
        n_passed += 1
    else:
        n_failed += 1

    # Test POST "/content" endpoint (root)
    resp = s.post(f"https://{HOST}:{PORT}/content", "A" * 100_000)

    if resp.status_code == 200:
        n_passed += 1
    else:
        n_failed += 1

    # Test DELETE "/content" endpoint (root)
    resp = s.delete(f"https://{HOST}:{PORT}/content")

    if resp.status_code == 200:
        n_passed += 1
    else:
        n_failed += 1

def perform_single_threaded_test(test_func, test_name: str, n_iterations: int) -> None:
    global n_passed, n_failed

    print(f"Test: {test_name} using {n_iterations} iterations")
    for _ in range(n_iterations):
        test_func()

    print(f"Passed: {n_passed}", f"Failed: {n_failed}", sep="\n", end="\n\n")

def perform_multi_threaded_test(test_func, test_name: str, n_iterations: int, n_threads: int) -> None:
    global n_passed, n_failed

    n_iterations = 10
    n_threads = 10

    print(f"Test: {test_name} using {n_iterations} iterations and {n_threads} threads per iteration")
    for _ in range(n_iterations):
        threads = [ ]
        for _ in range(n_threads):
            threads.append(Thread(target=test_func))
            threads[-1].start()

        for thread in threads:
            thread.join()

    print(f"Passed: {n_passed}", f"Failed: {n_failed}", sep="\n", end="\n\n")

if __name__ == "__main__":

    # Set global variables
    if int(os.environ.get("INTERNET_PROTOCOL")) == 1:
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
    n_passed, n_failed = 0, 0
    n_iterations = 100
    perform_single_threaded_test(sendGetRequestToRoot,
            "Single-threaded stress test of '/'", n_iterations)

    n_passed, n_failed = 0, 0
    n_iterations = 10
    n_threads = 10
    perform_multi_threaded_test(sendGetRequestToRoot,
            "Multi-threaded stress test of '/'", n_iterations, n_threads)

    n_passed, n_failed = 0, 0
    n_iterations = 10
    perform_single_threaded_test(sendGetRequestToContent,
            "Single-threaded stress test of '/content'", n_iterations)

 # 1317  curl -v -k -XPUT -F text=`python3 -c "print('A' * 100_000)"` https://127.0.0.1:8080/content
 # 1319  curl -v -k -XPOST -F text=`python3 -c "print('A' * 100_000)"` https://127.0.0.1:8080/content
 # 1321  curl -v -k -XDELETE  https://127.0.0.1:8080/content
