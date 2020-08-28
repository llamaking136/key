#!/usr/bin/python3

import os
from sys import argv
from time import sleep

version = "0.2.5"

about = f"""
Key Compiler (keyc) Version {version}
Copyright llamaking136 2020.
Any replication of this work will be reported.
All rights reserved.
Licence: https://raw.githubusercontent.com/llamaking136/key/master/LICENSE
"""
abouthelp = f"""
Key Compiler (keyc)
-o - use other output filename
-h - view (this) help page
-v - view version and about page
-save-temps - save the temporrary files used
"""

error = 0

warning = 0

def terminateCompile():
    print(tcol.bold + "Terminating compilation." + tcol.reset)
    try:
        os.remove("/tmp/0.cpp")
    except FileNotFoundError:
        pass
    exit()

true = True; false = False; null = None
class tcol:
    blue = '\033[34m'
    grn = '\033[32m'
    yell = '\033[33m'
    red = '\033[31m'
    reset = '\033[0m'
    bold = '\033[1m'
    undl = '\033[4m'

packages = ["stdio.h", "std.jm", "syn.jm"]

args = ["-o", "-save-temps", "-version", "-help"]

errors = [
    [
        "Exception",
        "ValueError",
        "PackageAddingWarning",
        "SyntaxError",
        "FuncNotFoundError",
        "PackageNotFoundError"
    ],
    [
        "adding syntax uneeded, but present",
        "parentheses are required",
        "package not found in stdlib"
    ]
]

def fatal(text, after = "terminateCompile()"):
    print(f"[{tcol.red}{tcol.bold}FATAL ERROR{tcol.reset}]: {text}")
    exec(after)

def throwError(exception, exceptText, data, line, isWarning = False):
    global error, warning
    if (isWarning):
        warning+=1
        print(f"[{tcol.blue}{tcol.bold}WARNING{tcol.reset}]: line " +tcol.bold+ str(line + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
        print(exception + ": " + exceptText)
    if (not isWarning):
        error+=1
        print(f"[{tcol.red}{tcol.bold}ERROR{tcol.reset}]: line " +tcol.bold+ str(line + 1) +tcol.reset+ ", file " +tcol.bold+filename+".ky"+tcol.reset+ " - '\33[4m" + " ".join(data) + "\33[0m'")
        print(exception + ": " + exceptText)

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
    fatal("no file inputted!")

filestuff = path.split(".")
filename = filestuff[0]
extention = filestuff[-1]

"""
if ("-o" in argv): # do they want a different compiled output name?
    filename = argv[argv.index("-o") + 1]

SAVE_TEMPS = False

if ("-save-temps" in argv): # do they want to save the temporrary files?
    SAVE_TEMPS = True

if (path == "-version" or path == "-v"): # are they finding the version?
    print(about)
    exit()

if ("-help" in argv or "-h" in argv): # are they finding help?
    print(abouthelp)
    exit()
"""

for i in argv:
    if (i.startswith("-")):
        if ()

if (not os.path.exists(path)): # does the file exist?
    fatal("file inputted does not exist!")

if (os.path.isdir(path)): # is the file a dir?
    fatal("file inputted is a directory!")

try:
    f = open(path)
    f.close()
except PermissionError:
    fatal("current user does not have permission to view file inputted!")

storage = {}

comment = "//" # was "#"

file = open(path)
content = file.read().splitlines()

# to remove comments
for ii in range(0, len(content)):
    for i in content:
        if (i.startswith(comment)):
            content.remove(i)

