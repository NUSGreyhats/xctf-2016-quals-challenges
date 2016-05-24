#!/usr/bin/python3

import ctypes
import sys
import os

# I translated this from C so I'm using ctypes. I don't understand Python
# numbers...

FLAG = open("flag.txt", "r").read()
PASS = os.urandom(0xff)


def write(data, term="\n"):
    sys.stdout.write(data + term)
    sys.stdout.flush()


def auth(length, password):
    for i in range(length):
        if password[i] != PASS[i]:
            return False
    return True


def main():
    # Since we use urandom, possible passwords contain nulls and newlines...
    # We'll just get the length to read from the user!
    write("Please enter the length of password you want to send")
    length = ctypes.c_int32(int(sys.stdin.readline())).value
    password = ""
    for i in range(length):
        password += sys.stdin.read(1)
    if auth(length, password):
        write("You are authenticated! Here's your flag: %s" % FLAG)
    else:
        write("I'm sorry. You don't have the right password.")

if __name__ == "__main__":
    main()
