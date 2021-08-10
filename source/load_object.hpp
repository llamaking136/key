//
// load_object.hpp
//
// created at 24/07/2021 17:21:06
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


#if !defined(LOAD_OBJECT_HPP)
#define LOAD_OBJECT_HPP

#include <string>
#include <vector>
#include <errno.h>
#include "error.hpp"

#if defined(__APPLE__) || defined(__linux__)
# include <dlfcn.h>
#elif defined(__WIN32)
# error Your computer does not support the neccicary libraries. Upgrade to macOS or get a real Linux computer.
#endif // __APPLE__ || __linux__

#if defined(KEY_LIB)
extern const char* KEY_LIB_SYMBOLS[]; // XXX: future feature
#endif // KEY_LIB

struct Library {
	std::string name;
	void* handle;
};

extern std::vector<Library> loaded_objects;

void* load_symbol(const char*, const char*);
// void (*)() load_function(const char*, const char*);
void close_libs();

#endif // LOAD_OBJECT_HPP
