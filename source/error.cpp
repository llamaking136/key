//
// error.cpp
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


#include "error.hpp"

namespace error {
    void basic_error(std::string message, std::string data, LineNo line, unsigned int where, std::string filename) {
		std::replace(data.begin(), data.end(), '\t', ' ');
        std::cerr << filename << ":" << line + 1 << ":" << where + 1 << ": error: " << message << "\n";
        std::cerr << "    " << line + 1 << " | " << data << "\n    ";
		for (int i = 0; i < std::to_string(line + 1).length(); i++) {
			std::cerr << " ";
		}
		std::cerr << " | ";
        for (int i = 0; i < where; i++) {
            std::cerr << " ";
        }   
        std::cerr << "^\n";
    }

    void spaced_error(std::string message, std::string data, LineNo line, unsigned int from, unsigned int to, std::string filename) {
		std::replace(data.begin(), data.end(), '\t', ' ');
        std::cerr << filename << ":" << line + 1 << ":" << from + 1 << ": error: " << message << "\n";
        std::cerr << "    " << line + 1 << " | " << data << "\n    ";
		for (int i = 0; i < std::to_string(line + 1).length(); i++) {
			std::cerr << " ";
		}
		std::cerr << " | ";
        for (int i = 0; i < from; i++) {
            std::cerr << " ";
        }
        for (int i = from; i < to + 1; i++) {
            std::cerr << "~";
        }
        std::cerr << "\n";
    }

    void fatal_error(std::string message) {
        std::cerr << "fatal error: " << message << "\n";
    }

    void error(std::string message) {
        std::cerr << "error: " << message << "\n";
    }

	void code_error(std::string message, LineNo line, LineNo where, std::string filename) {
		std::cerr << filename << ":" << line + 1 << ":" << where + 1 << ": error: " << message << "\n";
	}
}
