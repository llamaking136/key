#!/usr/bin/python3

import os
from sys import argv
"""
Jem Compiler (Jompiler) Version 0.1.8
Copyright Daniel Smith 2020.
Any replication of this work will be reported.
All rights reserved.
"""
class tcol:
    blue = '\033[34m'
    grn = '\033[32m'
    yell = '\033[33m'
    red = '\033[31m'
    reset = '\033[0m'
    bold = '\033[1m'
    undl = '\033[4m'

std = ["add", "exit"]
stdlib = [
  "out",
  "return"
]

if len(argv) == 1:
    print("usage: jompile <filename>")
    exit()
def main(path):
    if path == "--version" or path == "-v":
        print(f"""{tcol.bold}Jem Compiler (Jompiler) Version 0.1.8
Copyright Daniel Smith 2020.
Any replication of this work will be reported.
All rights reserved.{tcol.reset}""")
        exit()
    check = os.path.exists(path)
    if check == False:
        print(f"[{tcol.red}ERROR{tcol.reset}]: file inputted does not exist!")
        exit()
    name = path.split(".")
    tmp = name[::-1]
    ext = tmp[0]
    if ext != "jem":
        print(f"[{tcol.red}ERROR{tcol.reset}]: file inputted is not a jem file!")
        main()
    if ext == "jem":
        with open(f"{path}", "r") as file:
            content = file.read().splitlines()
            i = 0
            error = 0
            while (i != len(content)):
                data = str(content[i])
                data = data.split()
                if (data[0] in std):
                    pass
                elif (data[0] not in std):
                    error+=1
                    print("\33[31mTraceback (most recent call last):")
                    print("\nline " + str(i + 1) + " - '" + " ".join(data) + "'")
                    print("func " + data[0] + " not found")
                    print("\nTerminating compilation.\33[0m")
                    exit(-1)
                i+=1
main(argv[1])
