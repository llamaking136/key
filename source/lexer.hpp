//
// lexer.hpp
//
// created at 24/07/2021 15:14:55
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


#if !defined(LEXER_HPP)
#define LEXER_HPP

#include "token.hpp"
#include "error.hpp"

#include <string>
#include <vector>
#include <regex>
#include <utility>
#include <map>
#include <unordered_map>
#include <cstdarg>

#define DIGITS "0123456789."
#define LETTERS "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_"

// using namespace parser;

typedef std::vector<Token> TokenArr;
typedef std::vector<std::pair<std::string, TokenType> > TokenExpr;

bool contains(char, std::string);

std::string str_repr(std::string);

namespace lexer {

std::vector<std::string> splitBy(std::string, char);
TokenArr Lexer(std::string, std::string);
bool checkForKeyword(std::string);
TokenType checkIdentType(std::string);
extern const char* tokenMap[];

}

#endif // LEXER_HPP
