#!/usr/bin/env python3

import os
from sys import argv

version = "0.2.0"

"""
Key Compiler (keyc) Version 0.2.0
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
    "return"
]

if len(argv) == 1:
    print("usage: keyc <filename>")
    exit()

path = argv[1]

if path == "--version" or path == "-v":
    print(f"""{tcol.bold}Key Compiler (keyc) Version {version}
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
if ext != "ky" or ext == "key":
    print(f"[{tcol.red}ERROR{tcol.reset}]: file inputted is not a key file!")
    exit()
if ext == "ky":
    with open(f"{path}", "r") as file:
        content = file.read().splitlines()
        i = 0
        error = 0
        tmp0 = 0
        f = open("/tmp/0.cpp", "w")
        f.write("#include <iostream>\n")
        f.write("#include <stdlib.h>\n")
        f.write("#include <unistd.h>\n")
        f.write("using namespace std;\n")
        f.write("int main() {\n")
        while (i != len(content)):
            data = str(content[i])
            data = data.split()
            
            if (data[0] in stdlib):
                if (data[0] == "add"):
                    modadd = data[1].replace("<", "")
                    modadd = modadd.replace(">;", "")
                    """
                    else:
                        error+=1
                        print("\33[31mTraceback (most recent call last):")
                        print("\nline " + str(i + 1) + " - '" + " ".join(data) + "'")
                        print("module '" + modadd + "' not found")
                        print("\nTerminating compilation.\33[0m")
                        f.close()
                        os.remove("/tmp/0.cpp")
                        exit(-1)
                    """
                if (data[0] == "out"):
                    tmp2 = " ".join(data[1:])
                    ii = 0
                    tmp5 = list()
                    if (tmp2[0] != "("):
                        print("error")
                        exit(-1)
                    while (ii != len(tmp2)):
                        tmp3 = tmp2[ii]
                        tmp4 = "".join(tmp3[0])
                        tmp5.append(tmp4)
                        if (tmp3 == ";"):
                            break
                        ii+=1
                    tmp5 = "".join(tmp5)
                    tmp5 = tmp5.replace("(", "")
                    tmp5 = tmp5.replace("\'", "\"")
                    tmp5 = tmp5.replace(")", "")
                    tmp5 = tmp5.replace(";", "")
                    outdata = tmp5
                    f.write("cout << " + outdata + ";\n")
                if (data[0] == "return"):
                    value = data[1]
                    f.write("return " + value + "\n")
                if (data[0] == "exit"):
                    value = data[1]
                    f.write("exit" + value + "\n")
            if (data[0] not in stdlib):
                if (data[0][0] == "/"):
                    pass
                else:
                    error+=1
                    print("\33[31mTraceback (most recent call last):")
                    print("\nline " + str(i + 1) + " - '" + " ".join(data) + "'")
                    print("func '" + data[0] + "' not defined")
                    print("\nTerminating compilation.\33[0m")
                    f.close()
                    os.remove("/tmp/0.cpp")
                    exit(-1)
            i+=1
        f.write("}")
        f.close()
        filename = path.replace(".ky", "")
        # print(filename)
        os.system("g++ /tmp/0.cpp -o ./" + filename)
        os.system("chmod +x ./" + filename)
        # os.system("cat /tmp/0.cpp")
        os.remove("/tmp/0.cpp")
        exit(0)
