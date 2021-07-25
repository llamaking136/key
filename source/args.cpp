//
// args.cpp
//
// created at 24/07/2021 15:12:02
// written by llamaking136
//

// MIT License
//     
// Copyright (c) 2021 llamaking136
//     
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//     
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//     
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "args.hpp"

/*
char* slice(char* str, int base, int until) {
    char* temp;
    for (int i = base; i < until; i++) {
        strcat(temp, str[i]);
    }
    return temp;
}
*/

int helppage() {
    usage();
    std::cerr << "args:\n";
    std::cerr << " -h, --help: pull up this help page\n";
    std::cerr << " -v, --version: print the current version\n";
    return 1;
}

int printversion() {
    std::cout << PROGNME << " v" << VERSION << "\n";
    return 1;
}

int parseword(char* arg) {
    if (strcmp(arg, "--version") == 0) {
        return printversion();
    } else if (strcmp(arg, "--help") == 0) {
        return helppage();
    } else {
        error::error("unknown word option: " + std::string(arg));
        return 1;
    }
}

int parseargs(int argc, char** argv) {
    /*
    char* option;
    for (int i = 0; i < argc && argv[argc][0] == '-'; i++) {
        option = slice(argv[argc], 1, strlen(argv[argc]));
        switch (option) {
            case "h":
                return helppage();
                break;
            default:
                error::error("unknown option: " + std::to_string(option));
                return 1;
                break;
        }
    }
    */
    int optind;
    if (argc <= 1) {
        return usage();
    }

    for (optind = 1; optind < argc && argv[optind][0] == '-'; optind++) {
        switch (argv[optind][1]) {
            case 'h':
                return helppage();
                break;
            case 'v':
                return printversion();
                break;
            case '-':
                return parseword(argv[optind]);
                break;
            default:
                char unknown_char = argv[optind][1];
                std::string unknown(1, unknown_char);
                error::error("unknown option: -" + unknown);
                return 1;
                break;
        }
    }
    return 0;
}
