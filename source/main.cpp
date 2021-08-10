//
// main.cpp
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


#include "main.hpp"

#if defined(MS_WINDOWS)
// # error WINDOWS SUCKS!!!
// Okay, maybe I shouldn't be too hard on the people who can't afford Linux
# error Sorry, Windows isn't supported by key
#endif // MS_WINDOWS

bool save_compiled_bytecode = false;

void pool_drain() {
	close_libs();
}

int usage() {
    std::cerr << "usage: key <filename> [args]\n";
    return 1;
}

int main(int argc, char** argv) {
	AutoreleasePool pool;
	pool.appendReleaseFunction(pool_drain);

    int return_value = parseargs(argc, argv);
    if (return_value != 0) {
        return return_value;
    }

    std::string filename(argv[1]);
    std::string filedata = lib::fileread(filename);

    TokenArr tokens = lexer::Lexer(filename, filedata);

	// TODO: make this in the pre-proccessor
	if (DEBUG_MODE)
		goto printTokens;
	else
		goto afterPrintTokens;

printTokens:
	if (tokens.size()) {
		std::cout << "tokens:\n";
	}
    for (Token x: tokens) {
        std::cout << "'" << x.data << "' -> " << lexer::tokenMap[x.type] << ", line " << x.line << " on char " << x.pos << "\n";
    }
	if (tokens.size()) {
		std::cout << "\n";
	}
afterPrintTokens:

	// std::vector<parser::statement> statements = parser::Parser(tokens, filedata, filename, true);

    return 0;
}
