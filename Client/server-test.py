#!/usr/bin/env python3

import sys
import requests

if __name__ == "__main__":
    resp = requests.get("http://127.0.0.1:8001")
    print(resp.status_code)
    print(resp.text)
