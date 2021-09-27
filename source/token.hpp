//
// token.hpp
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


#if !defined(TOKEN_HPP)
#define TOKEN_HPP

#include <string>

#if !defined(LineNo)
typedef unsigned int LineNo;
#endif // LineNo

enum TokenType {
	BOOL_TYPE,
	CHAR_TYPE,
	INT_TYPE,
	FLOAT_TYPE,
	STR_TYPE,
	CUSTOM_TYPE,

	IDENTIFIER,

	ASSIGN,

	BOOL_VALUE,
	CHAR_VALUE,
	INT_VALUE,
	FLOAT_VALUE,
	STR_VALUE,
	NULL_VALUE,
	CUSTOM_VALUE,

	PLUS_EQUALS,
	MINUS_EQUALS,
	DIVIDE_EQUALS,
	TIMES_EQUALS,
	MOD_EQUALS,

	PLUS,
	MINUS,
	DIVIDE,
	TIMES,
	MOD,

	GREATER,
	SMALLER,
	GREATER_EQUAL,
	SMALLER_EQUAL,

	NOT,
	OR,
	AND,

	BIT_OR,
	BIT_AND,
	BIT_XOR,
	BIT_NOT,
	BIT_SHIFT_L,
	BIT_SHIFT_R,

	POWER_OF,

	EQUALS,
	NOT_EQUALS,

	OPEN_BRACKET,
	CLOSE_BRACKET,
	
	OPEN_SQUARE,
	CLOSE_SQUARE,

	OPEN_CURLY,
	CLOSE_CURLY,

	IF,
	ELSEIF,
	ELSE,

	RETURN,

	WHILE,
	FOR,

	COMMA,
	SEMICOLON,

	COLON,
	KEYWORD,

	EOL,
	_EOF,

	INCLUDE,

	FUNCDEF,

	STRUCTDEF,

	NAMESPACE,

	TRUE_T,
	FALSE_T,

	DOT_OP,
	ARROW_OP,

	VAR_ASSIGN,

	CONST_ASSIGN,

	NUM_RANGE,

	CONTINUE,
	BREAK,

	NEW,
	AUTO,

	TRY,
	CATCH,
	THROW,

	TYPEOF,
	SIZEOF,

	_NULL // XXX: do not remove!
};

struct Token {
	std::string filename;
	LineNo pos;
	LineNo line;
	TokenType type;
	std::string data;
};

#endif // TOKEN_HPP
