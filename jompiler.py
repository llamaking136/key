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

stdlib = [
    "add",
    "exit",
    "out",
    "return",
]

if len(argv) == 1:
    print("usage: jompile <filename>")
    exit()

path = argv[1]

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
    exit()
if ext == "jem":
    with open(f"{path}", "r") as file:
        content = file.read().splitlines()
        i = 0
        error = 0
        tmp0 = 0
        while (i != len(content)):
            data = str(content[i])
            data = data.split()
            
            if (data[0] in stdlib):
                if (data[0] == "add"):
                    modadd = data[1].replace("<", "")
                    modadd = modadd.replace(">;", "")
                    if (modadd == "jem.jm"):
                        tmp0 = 1
                    else:
                        if (modadd == "syn.jm"):
                            tmp1 = 1
                        error+=1
                        print("\33[31mTraceback (most recent call last):")
                        print("\nline " + str(i + 1) + " - '" + " ".join(data) + "'")
                        print("module '" + modadd + "' not found")
                        if (tmp1 == 1):
                            print("maybe you meant 'jem.jm'?")
                        print("\nTerminating compilation.\33[0m")
                        exit(-1)
            # print(data[0])
            if (data[0] not in stdlib):
                if (data[0][0] == "/"):
                    pass
                else:
                    error+=1
                    print("\33[31mTraceback (most recent call last):")
                    print("\nline " + str(i + 1) + " - '" + " ".join(data) + "'")
                    print("func '" + data[0] + "' not defined")
                    print("\nTerminating compilation.\33[0m")
                    exit(-1)
            i+=1