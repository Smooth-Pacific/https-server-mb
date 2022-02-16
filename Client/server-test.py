#!/usr/bin/env python3

import os
import sys
import requests

HOST = "127.0.0.1" 
PORT = 8080

if __name__ == "__main__":
    if os.environ.get("HOST"):
        host = os.environ.get("HOST")
    if os.environ.get("PORT"):
        port = os.environ.get("PORT")

    # Test / endpoint (root)
    resp = requests.get(f"https://{HOST}:{PORT}", verify=False)
    print(resp.status_code)
    print(resp.text, "\n")

    # Test /hello endpoint
    resp = requests.get(f"https://{HOST}:{PORT}/hello", verify=False)
    print(resp.status_code)
    print(resp.text)
