#!/usr/bin/python3

import os
from sys import argv

version = "0.2.0"

about = f"""
Key Compiler (keyc) Version {version}
Copyright Daniel Smith 2020.
Any replication of this work will be reported.
All rights reserved.
"""
true = True; false = False; null = None
class tcol:
    blue = '\033[34m'
    grn = '\033[32m'
    yell = '\033[33m'
    red = '\033[31m'
    reset = '\033[0m'
    bold = '\033[1m'
    undl = '\033[4m'

errors = [
    [
        "ValueError",
        "PackageAddingWarning",
        "SyntaxError",
        "FuncNotFoundError"
    ],
    [
        "adding syntax uneeded, but present",
        "parentheses are required",
        ""
    ]
]

def throwError(exception, exceptText, optionText = None):
    if (optionText):
        print(exception + ": " + exceptText + " " + optionText)
    if (not optionText):
        print(exception + ": " + exceptText + " error")

stdlib = [
    "add",
    "exit",
    "out",
    "return",
    #"str",
    "int"
]

try:
    path = argv[1]
except IndexError:
    print("usage: keyc <filename> <optional - filename of compiled source>")
    exit()

filename = path.replace(".ky", "")

try:
    filename = argv[2]
except IndexError:
    pass

if (path == "--version" or path == "-v"):
    print(f"""{tcol.bold}Key Compiler (keyc) Version {version}
Copyright Daniel Smith 2020.
Any replication of this work will be reported.
All rights reserved.{tcol.reset}""")
    exit()

if (not os.path.exists(path)):
    print(f"[{tcol.red}{tcol.bold}ERROR{tcol.reset}]: file inputted does not exist!")
    exit()

name = path.split(".")
tmp = name[::-1]
ext = tmp[0]

if (true): # FIXED // somewhat..
    with open(f"{path}", "r") as file: # FIX
        content = file.read().splitlines()
        i = 0
        error = 0
        warning = 0
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
                    modadd = data[1].replace("<", "") # trying to find the package to import
                    modadd = modadd.replace(">;", "") # trying to find the package to import
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
                    if (modadd == "syn.jm" or modadd == "std.jm"):
                        warning+=1
                        print(f"[{tcol.blue}{tcol.bold}WARNING{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4madd <" + modadd + ">;\33[0m'")
                        throwError(errors[0][0], errors[1][0], "warning")
                if (data[0] == "out"):
                    tmp2 = " ".join(data[1:]) # putting list into string to find data to print
                    ii = 0
                    tmp5 = list()
                    if (tmp2[0] != "("):
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        throwError(errors[0][2], errors[1][1])
                        # exit(-1)
                    while (ii != len(tmp2)): # continusly going through the data to find it all, thanks to the semicolon
                        tmp3 = tmp2[ii]
                        tmp4 = "".join(tmp3[0])
                        tmp5.append(tmp4) # put the data into a string
                        if (tmp3 == ";"):
                            break # stops when it finds the semicolon
                        ii+=1
                    tmp5 = "".join(tmp5) # combine it all to turn it into a string
                    #if ("\'" not in tmp5 or "\"" not in tmp5):
                    """
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print("data '" + data[0] + "' not defined")
                    """
                    #else:
                    tmp5 = tmp5.replace("(", "") # fixing up the data to read correctly
                    tmp5 = tmp5.replace("\'", "\"") # fixing up the data to read correctly
                    tmp5 = tmp5.replace(")", "") # fixing up the data to read correctly
                    tmp5 = tmp5.replace(";", "") # fixing up the data to read correctly
                    outdata = tmp5
                    f.write("cout << " + outdata + ";\n")
                if (data[0] == "return"):
                    try:
                        value = data[1]
                        value = value.replace("(", "")
                        value = value.replace(")", "")
                        value = value.replace(";", "")
                        value = int(value) # turn it into an int to make sure we're returning an int
                    except ValueError: # if it isnt an int then return an error
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print(f"ValueError: type 'int' required, not {type(data[1])}")
                    
                    """
                    if (type(value) != int):
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print(f"ValueError: type 'int' required, not {type(data[1])}")
                    """
                    f.write("return " + str(data[1]) + "\n")
                if (data[0] == "exit"):
                    try:
                        value = data[1]
                        value = value.replace("(", "")
                        value = value.replace(")", "")
                        value = value.replace(";", "")
                        value = int(value) # turn it into an int to make sure we're returning an int
                    except ValueError: # if it isnt an int then return an error
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print(f"ValueError: type 'int' required, not {type(data[1])}")
                    
                    """
                    if (type(value) != int):
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print(f"ValueError: type 'int' required, not {type(data[1])}")
                    """
                    f.write("exit" + str(data[1]) + "\n")
                if (data[0] == "str"):
                    strname = data[1]
                    if (strname[-1] != ";"):
                        pass # do nothing yet, too dumb to continue for now
                if (data[0] == "int"):
                    intname = data[1]
                    if (intname[-1] != ";"):
                        intdata = data[3]
                        if (";" not in intdata): # if there is no semiconon because there totally needs to be one:
                            error+=1
                            print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                            print("SyntaxError: int '" + intname + "' without semicolon")
                        intdata = intdata.replace(";", "")
                        f.write("int " + intname + " = " + intdata + ";\n") # add else
            if (data[0] not in stdlib):
                if (data[0][0] == "/"): # if there is a slash:
                    if (data[0][1] == "/"): # if there is another slash:
                        pass # do nothing because it's a comment
                    else: # so it's not a comment
                        error+=1
                        print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                        print("FuncNotFoundError: func '" + data[0] + "' not defined")
                else: # no comment
                    error+=1
                    print(f"[{tcol.bold}{tcol.red}ERROR{tcol.reset}]: line " +tcol.bold+ str(i + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
                    print("FuncNotFoundError: func '" + data[0] + "' not defined")
            i+=1
        f.write("}")
        f.close()
        # print(filename)
        print(str(warning) + " warnings and " + str(error) + " errors.")
        if (error >= 1):
            print(tcol.bold + "Terminating compilation." + tcol.reset)
            os.remove("/tmp/0.cpp")
            exit()
        os.system("g++ /tmp/0.cpp -o ./" + filename + " > .nobodycares") # this is bad..who knows if the right compiler is on the right machine?
        os.remove(".nobodycares")
        os.system("chmod +x ./" + filename)
        # os.system("cat /tmp/0.cpp")
        os.remove("/tmp/0.cpp")
        exit(0)
