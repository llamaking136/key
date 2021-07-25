//
// lexer.cpp
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


#include "lexer.hpp"

bool contains(char to, std::string base) {
	return base.find(to) != std::string::npos;
}

namespace lexer {

std::vector<std::string> splitBy(std::string base, char by) {
	std::stringstream ss(base);
	std::string to;
	std::vector<std::string> result;

	while (std::getline(ss, to, by)){
		result.push_back(to);
	}
	return result;
}

TokenArr Lexer(std::string filename, std::string filedata) {
	TokenArr result;

	std::vector<std::string> filedataArr = splitBy(filedata, '\n');
	std::string current_line;

	LineNo pos = 0;
	LineNo l_pos = 0;
	LineNo line = 0;
	bool is_num = false;
	bool is_str = false;
	bool is_com = false;
	bool is_name = false;
	bool is_char = false;

	int bracket_num = 0;
	int square_num = 0;
	int curly_num = 0;

	std::string num_str = "";
	std::string str_str = "";
	std::string name_str = "";

	int num_dot_count = 0;
	char char_str = '\0';

	// std::string current_line_text;

	char cur_chr;

	for (pos = 0; pos < filedata.length(); pos++) {
		cur_chr = filedata[pos];
		current_line = filedataArr[line];

		// comment handling
		if (!is_com && cur_chr == '/' && filedata[pos + 1] == '*') { // begining of comments
			is_com = true;
			l_pos++;
			continue;
		}
		if (is_com && cur_chr == '*' && filedata[pos + 1] == '/') { // end of comments
			is_com = false;
			pos++;
			l_pos += 2;
			continue;
		} else if (is_com) { // during comments | during chars
			l_pos++;
			continue;
		} else if (!is_com && cur_chr == '*' && filedata[pos + 1] == '/') { // comment error
			// error::code_error("unmatched comment", std::string("*/"), line, l_pos, filename);
			error::basic_error("unmatched comment", current_line, line, l_pos, filename);
			exit(1);
		}

		// chars
		else if (cur_chr == '\'' && !is_char) { // begining of char
			// if (filedata[pos + 1] == '\\' && filedata[pos + 3] == '\'') 
			if (filedata[pos + 2] != '\'') {
				// error::code_error("reached EOL when parsing char val.", "EOL", line, l_pos + 2, filename);
				error::basic_error("unexpected EOL while parsing char", current_line, line, l_pos + 2, filename);
				exit(1);
			}
			is_char = true;
			l_pos++;
			continue;
		} else if (cur_chr == '\'' && is_char) { // end of char
			char_str = filedata[pos - 1];
			
			is_char = false;
			result.push_back(Token{ filename, l_pos - 2, line, TokenType::CHAR_VALUE, std::string(1, char_str) });
			l_pos++;

			char_str = '\0';
			continue;
		} else if (is_char) { // during char
			l_pos++;
			continue;
		}

		// strings
		if (cur_chr == '"' && !is_str) { // begining of string
			is_str = true;
			// l_pos++;
			continue;
		}
		if (cur_chr == '"' && is_str) { // end of string
			if (filedata[pos - 1] == '\\') {
				str_str.erase(str_str.length());
				str_str += cur_chr;
				continue;
			}
			is_str = false;
			result.push_back(Token{ filename, l_pos, line, TokenType::STR_VALUE, str_str });
			l_pos += str_str.length() + 2;
			str_str = "";
			// l_pos++;
			continue;
		}
		if (is_str && cur_chr == '\\') { // during string and checking for escape sequences
			switch (filedata[pos + 1]) {
				case 'n':
					str_str += "\n";
					pos++;
					continue;
					break;
				case 't':
					str_str += "\t";
					pos++;
					continue;
					break;
				case 'r':
					str_str += "\r";
					pos++;
					continue;
					break;
				case 'a':
					str_str += "\a";
					pos++;
					continue;
					break;
				case 'b':
					str_str += "\b";
					pos++;
					continue;
					break;
				case 'e':
					str_str += "\e";
					pos++;
					continue;
					break;
				case 'f':
					str_str += "\f";
					pos++;
					continue;
					break;
				case 'v':
					str_str += "\v";
					pos++;
					continue;
					break;
				case '\\':
					str_str += "\\";
					pos++;
					continue;
					break;
				case '"':
					continue;
					break;
				default:
					error::basic_error("unknown escape sequence: \\" + std::string(1, filedata[pos + 1]), current_line, line, l_pos + str_str.length() + 2, filename);
					exit(1);
			}
		}
		if (is_str) { // during string
			if (cur_chr == '\n') {
				// error::code_error("unexpected EOL while parsing string", "EOL", line, l_pos, filename);
				error::basic_error("unexpected EOL while parsing string", current_line, line, l_pos, filename);
				exit(1);
			}
			str_str += cur_chr;
			// l_pos++;
			continue;
		}

		// identifiers
		if (strchr(LETTERS, cur_chr) && !is_name) { // ident start
			is_name = true;
			name_str += cur_chr;
			continue;
		}
		if (!strchr(LETTERS, cur_chr) && is_name) { // ident end
			if (strchr(DIGITS, cur_chr) && cur_chr != '.') {
				name_str += cur_chr;
				continue;
			}

			/* if (checkForKeyword(name_str)) {
				is_name = false;
				result.push_back(Token{ filename, l_pos, line, TokenType::KEYWORD, name_str });
				l_pos += name_str.length();
				pos--;
				name_str = "";
				continue;
			} else */ if (checkIdentType(name_str) != _NULL) {
				is_name = false;
				result.push_back(Token{ filename, l_pos, line, checkIdentType(name_str), name_str });
				l_pos += name_str.length();
				pos--;
				name_str = "";
				continue;
			}

			is_name = false;
			result.push_back(Token{ filename, l_pos, line, TokenType::IDENTIFIER, name_str });
			l_pos += name_str.length();
			pos--;
			name_str = "";
			continue;
		}
		if (is_name) { // during ident
			if (checkForKeyword(name_str)) { // end of ident
				is_name = false;
				result.push_back(Token{ filename, l_pos, line, TokenType::KEYWORD, name_str });
				l_pos += name_str.length();
				pos--;
				name_str = "";
				continue;
			} /* else if (checkIdentType(name_str) != _NULL) { // end of ident
				is_name = false;
				result.push_back(Token{ filename, l_pos, line, checkIdentType(name_str), name_str });
				l_pos += name_str.length();
				pos--;
				name_str = "";
				continue;
			} */
			name_str += cur_chr;
			continue;
		}

		// numbers
		if (strchr(DIGITS, cur_chr) && !is_num) { // number start
			if (cur_chr == '.') {
				if (num_str.length() <= 0) {
					result.push_back(Token{ filename, l_pos, line, TokenType::DOT_OP, std::string(".") });
					l_pos++;
					continue;
				}
				error::basic_error("invalid syntax", current_line, line, l_pos, filename);
				exit(1);
			}
			is_num = true;
			num_str += cur_chr;
			continue;
		}
		if (!strchr(DIGITS, cur_chr) && is_num) { // number end
			if (contains('.', num_str) && num_str.length() <= 2) {
				error::basic_error("float cannot end with dot", current_line, line, l_pos, filename);
				exit(1);
			}
			is_num = false;
			result.push_back(Token{ filename, l_pos, line, contains('.', num_str) ? TokenType::FLOAT_VALUE : TokenType::INT_VALUE, num_str });
			l_pos += num_str.length();
			pos--;
			num_str = "";
			continue;
		}
		if (is_num) { // during number
			if (cur_chr == '.' && num_dot_count == 2) {
				error::basic_error("cannot have more than two dots in float", current_line, line, l_pos, filename);
				exit(1);
			} else if (cur_chr == '.') {
				num_dot_count++;
			}
			num_str += cur_chr;
			continue;
		}

		// ignoring chars
		if (strchr(" \t\r", cur_chr)) {
			l_pos++;
			continue;
		}
		if (cur_chr == '\n') {
			line++;
			l_pos = 0;
			continue;
		}

		// basic math operators
		if (cur_chr == '+') { // +
			if (filedata[pos + 1] == '=') { // +=
				result.push_back(Token{ filename, l_pos, line, TokenType::PLUS_EQUALS, std::string("+=") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::PLUS, std::string("+") });
			l_pos++;
			continue;
		} else if (cur_chr == '-') { // -
			if (filedata[pos + 1] == '=') { // -=
				result.push_back(Token{ filename, l_pos, line, TokenType::MINUS_EQUALS, std::string("-=") });
				pos++;
				l_pos += 2;
				continue;
			} else if (filedata[pos + 1] == '>') { // ->
				result.push_back(Token{ filename, l_pos, line, TokenType::ARROW_OP, std::string("->") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::MINUS, std::string("-") });
			l_pos++;
			continue;
		} else if (cur_chr == '*') { // *
			if (filedata[pos + 1] == '=') { // *=
				result.push_back(Token{ filename, l_pos, line, TokenType::TIMES_EQUALS, std::string("*=") });
				pos++;
				l_pos += 2;
				continue;
			} else if (filedata[pos + 1] == '*') { // **
				result.push_back(Token{ filename, l_pos, line, TokenType::POWER_OF, std::string("**") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::TIMES, std::string("*") });
			l_pos++;
			continue;
		} else if (cur_chr == '/') { // /
			if (filedata[pos + 1] == '=') { // /=
				result.push_back(Token{ filename, l_pos, line, TokenType::DIVIDE_EQUALS, std::string("/=") });
				pos++;
				l_pos += 2;
				continue;
			} 
			result.push_back(Token{ filename, l_pos, line, TokenType::DIVIDE, std::string("/") });
			l_pos++;
			continue;
		} else if (cur_chr == '%') { // %
			if (filedata[pos + 1] == '=') { // %=
				result.push_back(Token{ filename, l_pos, line, TokenType::MOD_EQUALS, std::string("%=") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::MOD, std::string("%") });
			l_pos++;
			continue;
		} else if (cur_chr == '<') { // <
			if (filedata[pos + 1] == '=') { // <=
				result.push_back(Token{ filename, l_pos, line, TokenType::SMALLER_EQUAL, std::string("<=") });
				pos++;
				l_pos += 2;
				continue;
			} else if (filedata[pos + 1] == '<') { // <<
				result.push_back(Token{ filename, l_pos, line, TokenType::BIT_SHIFT_L, std::string("<<") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::SMALLER, std::string("<") });
			l_pos++;
			continue;
		} else if (cur_chr == '>') { // >
			if (filedata[pos + 1] == '=') { // >=
				result.push_back(Token{ filename, l_pos, line, TokenType::GREATER_EQUAL, std::string(">=") });
				pos++;
				l_pos += 2;
				continue;
			} else if (filedata[pos + 1] == '>') { // >>
				result.push_back(Token{ filename, l_pos, line, TokenType::BIT_SHIFT_R, std::string(">>") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::GREATER, std::string(">") });
			l_pos++;
			continue;
		}

		// brackets
		else if (cur_chr == '(') { // (
			result.push_back(Token{ filename, l_pos, line, TokenType::OPEN_BRACKET, std::string("(") });
			bracket_num++;
			l_pos++;
			continue;
		} else if (cur_chr == ')') { // )
			if (bracket_num == 0) {
				// error::code_error("unmatched round bracket(s)", "EOF", line, l_pos, filename);
				error::basic_error("unmatched round bracket(s)", current_line, line, l_pos, filename);
				exit(1);
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::CLOSE_BRACKET, std::string(")") });
			bracket_num--;
			l_pos++;
			continue;
		} else if (cur_chr == '[') { // [
			result.push_back(Token{ filename, l_pos, line, TokenType::OPEN_SQUARE, std::string("[") });
			square_num++;
			l_pos++;
			continue;
		} else if (cur_chr == ']') { // ]
			if (square_num == 0) {
				// error::code_error("unmatched square bracket(s)", "EOF", line, l_pos, filename);
				error::basic_error("unmatched square bracket(s)", current_line, line, l_pos, filename);
				exit(1);
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::CLOSE_SQUARE, std::string("]") });
			square_num--;
			l_pos++;
			continue;
		} else if (cur_chr == '{') { // {
			result.push_back(Token{ filename, l_pos, line, TokenType::OPEN_CURLY, std::string("{") });
			curly_num++;
			l_pos++;
			continue;
		} else if (cur_chr == '}') { // }
			if (curly_num == 0) {
				// error::code_error("unmatched curly bracket(s)", "eof", line, l_pos, filename);
				error::basic_error("unmatched curly bracket(s)", current_line, line, l_pos, filename);
				exit(1);
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::CLOSE_CURLY, std::string("}") });
			curly_num--;
			l_pos++;
			continue;
		}

		// other operators
		else if (cur_chr == '=') { // =
			if (filedata[pos + 1] == '=') { // ==
				result.push_back(Token{ filename, l_pos, line, TokenType::EQUALS, std::string("==") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::ASSIGN, std::string("=") });
			l_pos++;
			continue;
		} else if (cur_chr == '!') { // !
			if (filedata[pos + 1] == '=') { // !=
				result.push_back(Token{ filename, l_pos, line, TokenType::NOT_EQUALS, std::string("!=") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::NOT, std::string("!") });
			l_pos++;
			continue;
		} else if (cur_chr == ':') { // :
			if (filedata[pos + 1] == ':') { // ::
				result.push_back(Token{ filename, l_pos, line, TokenType::NAMESPACE, std::string("::") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::COLON, std::string(":") });
			l_pos++;
			continue;
		} else if (cur_chr == ';') { // ;
			result.push_back(Token{ filename, l_pos, line, TokenType::SEMICOLON, std::string(";") });
			l_pos++;
			continue;
		} else if (cur_chr == '.') { // .
			if (filedata[pos + 1] == '.' && filedata[pos + 2] == '.') { // ...
				result.push_back(Token{ filename, l_pos, line, TokenType::NUM_RANGE, std::string("...") });
				pos += 2;
				l_pos += 3;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::DOT_OP, std::string(".") });
			l_pos++;
			continue;
		}

		// bitwise operators
		else if (cur_chr == '|') { // |
			if (filedata[pos + 1] == '|') { // ||
				result.push_back(Token{ filename, l_pos, line, TokenType::OR, std::string("||") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::BIT_OR, std::string("|") });
			l_pos++;
			continue;
		} else if (cur_chr == '&') { // &
			if (filedata[pos + 1] == '&') { // &&
				result.push_back(Token{ filename, l_pos, line, TokenType::AND, std::string("&&") });
				pos++;
				l_pos += 2;
				continue;
			}
			result.push_back(Token{ filename, l_pos, line, TokenType::BIT_AND, std::string("&") });
			l_pos++;
			continue;
		} else if (cur_chr == '^') { // ^
			result.push_back(Token{ filename, l_pos, line, TokenType::BIT_XOR, std::string("^") });
			l_pos++;
			continue;
		} else if (cur_chr == '~') { // ~
			result.push_back(Token{ filename, l_pos, line, TokenType::BIT_NOT, std::string("~") });
			l_pos++;
			continue;
		}

		/*
		// chars
		else if (cur_chr == '\'' && !is_char) { // begining of char
			if (filedata[pos + 2] != '\'') {
				error::code_error("reached EOL when parsing char val.", "EOL", line, l_pos + 2, filename);
				exit(1);
			}
			is_char = true;
			l_pos++;
			continue;
		} else if (cur_chr == '\'' && is_char) { // end of char
			char_str = filedata[pos - 1];
			
			is_char = false;
			result.push_back(Token{ filename, l_pos - 1, line, TokenType::CHAR_VALUE, std::string(1, char_str) });
			l_pos++;

			char_str = '\0';
			continue;
		}
		*/

		// if anything else is forbidden
		else { // whatever else
			// error::code_error("invalid character", std::string(1, cur_chr), line, l_pos, filename);
			error::basic_error("invalid character", current_line, line, l_pos, filename);
			exit(1);
		}
	}

	if (is_com) {
		// error::code_error("unmatched comment", "*/", line, l_pos, filename);
		error::basic_error("unmatched comment", current_line, line, l_pos, filename);
		exit(1);
	}

	// checking for any loose open brackets
	// if (bracket_num != 0) {
	// 	// error::code_error("unmatched round bracket(s)", "EOF", line, l_pos, filename);
	// 	error::basic_error("unmatched round bracket(s)", current_line, line, l_pos, filename);
	// 	exit(1);
	// } else if (square_num != 0) {
	// 	// error::code_error("unmatched square bracket(s)", "EOF", line, l_pos, filename);
	// 	error::basic_error("unmatched square bracket(s)", current_line, line, l_pos, filename);
	// 	exit(1);
	// } else if (curly_num != 0) {
	// 	// error::code_error("unmatched curly bracket(s)", "eof", line, l_pos, filename);
	// 	error::basic_error("unmatched curly bracket(s)", current_line, line, l_pos, filename);
	// 	exit(1);
	// }
	
	if (is_str) {
		error::basic_error("unexpected EOF while parsing string", current_line, line, l_pos, filename);
		exit(1);
	}

	return result;
}

bool checkForKeyword(std::string input) {
	std::vector<std::string> keywords = {
		"var",
		"const",
		"return",
		"func",
		"struct",
		"continue",
		"break",
		"if",
		"elseif",
		"else",
		"new",
		"auto",
		"while",
		"for",
		"try",
		"catch",
		"throw",
		"include",
		"typeof",
		"sizeof"
	};

	return (std::find(keywords.begin(), keywords.end(), input) != keywords.end());
}

TokenType checkIdentType(std::string input) {
	// names
	if (input == "true") {
		return TRUE_T;
	} else if (input == "false") {
		return FALSE_T;
	} else if (input == "var") {
		return VAR_ASSIGN;
	} else if (input == "const") {
		return CONST_ASSIGN;
	} else if (input == "return") {
		return RETURN;
	} else if (input == "func") {
		return FUNCDEF;
	} else if (input == "struct") {
		return STRUCTDEF;
	} else if (input == "continue") {
		return CONTINUE;
	} else if (input == "break") {
		return BREAK;
	} else if (input == "if") {
		return IF;
	} else if (input == "elseif") {
		return ELSEIF;
	} else if (input == "else") {
		return ELSE;
	} else if (input == "new") {
		return NEW;
	} else if (input == "auto") {
		return WHILE;
	} else if (input == "for") {
		return FOR;
	} else if (input == "try") {
		return TRY;
	} else if (input == "catch") {
		return CATCH;
	} else if (input == "throw") {
		return THROW;
	} else if (input == "include") {
		return INCLUDE;
	} else if (input == "typeof") {
		return TYPEOF;
	} else if (input == "sizeof") {
		return SIZEOF;
	}

	// types
	else if (input == "BOOL") {
		return BOOL_TYPE;
	} else if (input == "CHAR") {
		return CHAR_TYPE;
	} else if (input == "INT") {
		return INT_TYPE;
	} else if (input == "FLOAT") {
		return FLOAT_TYPE;
	} else if (input == "STR") {
		return STR_TYPE;
	} else if (input == "NULL") {
		return NULL_VALUE;
	} else {
		return _NULL;
	}
}

const char* tokenMap[] = {
	"bool type",
	"char type",
	"int type",
	"float type",
	"string type",

	"variable",

	"assignment",
	
	/*
	"plus assi",
	"minus assi",
	"divide assi",
	"times assi",
	"modulus assi",
	*/

	"bool value",
	"char value",
	"int value",
	"float value",
	"string value",
	"null value",

	"plus eaq",
	"minus eaq",
	"divide eaq",
	"times eaq",
	"modulus eaq",

	"plus",
	"minus",
	"divide",
	"times",
	"modulus",

	"greater",
	"smaller",
	"greater eaq",
	"smaller eaq",

	"not",
	"or",
	"and",
	
	"bitwise or",
	"bitwise and",
	"bitwise xor",
	"bitwise not",
	"bitwise shift left",
	"bitwise shift right",

	"power of",

	"eaq",
	"not eaq",
	
	"open bracket",
	"close bracket",

	"open square",
	"close square",

	"open curly",
	"close curly",

	"if",
	"else if",
	"else",

	"return",

	"while loop",
	"for loop",

	"comma",
	"semicolon",
	
	"colon",
	"keyword",

	"end of line",
	"end of file",
	
	"include",
	
	"function definition",

	"structure definition",

	"namespace",

	"true type",
	"false type",

	"dot operator",
	"arrow operator",

	"variable assignment",

	"constant variable assignment",

	"number range",

	"continue",
	"break",

	"new",
	"auto",

	"try",
	"catch",
	"throw",

	"NULL" // XXX: DO NOT DELETE THIS!!
};

}
