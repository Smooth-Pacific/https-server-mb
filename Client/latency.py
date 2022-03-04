#!/usr/bin/env python3

# Creator: VPR
# Created: March 4th, 2022
# Updated: March 4th, 2022

import subprocess

HOST="https://127.0.0.1"
PORT=8080

def launch_curl() -> None:
    command  = [ "curl" ]
    command += [ "-v", "--digest" ]
    command += [ "-u", "username:password" ]
    command += [ f"{HOST}:{PORT}/" ]

    p = subprocess.Popen(command, stdout=subprocess.PIPE);
    p.wait()

    print(*p.communicate())

if __name__ == "__main__":
    launch_curl()
