//
// load_object.cpp
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


#include "load_object.hpp"

std::vector<Library> loaded_objects = {};

bool lib_already_loaded(std::string name) {
	for (unsigned long i = 0; i < loaded_objects.size(); i++) {
		if (loaded_objects[i].name == name) return true;
	}
	return false;
}

long get_library_index(std::string name) {
	for (unsigned long i = 0; i < loaded_objects.size(); i++) {
		if (loaded_objects[i].name == name) return i;
	}
	return -1;
}

void* load_symbol(const char* symbol_name, const char* lib_name) {
	void* lib;
	bool lib_is_loaded = false;
	if (lib_already_loaded(std::string(lib_name))) {
		lib_is_loaded = true;
		lib = loaded_objects[get_library_index(std::string(lib_name))].handle;
	} else {
		lib = dlopen(lib_name, RTLD_LAZY);
		if (lib == NULL) {
			error::error("could not load the library " + std::string(lib_name) + ": \33[31m" + std::string(dlerror()) + "\33[0m");
			return nullptr;
		}
	}

	void* symbol = dlsym(lib, symbol_name);
	if (symbol == NULL) {
		error::error("could not load the symbol " + std::string(symbol_name) + ": \33[1m" + std::string(dlerror()) + "\33[0m");
		dlclose(lib);
		return nullptr;
	}
	if (lib_is_loaded) {
		std::cout << "Loaded symbol" << symbol_name << "\n";
		goto _return;
	}

	loaded_objects.push_back(Library{ std::string(lib_name), lib });

	std::cout << "Loaded symbol " << symbol_name << " and " << lib_name << "\n";

_return:
	return symbol;
}

// void (*)() load_function(const char* function_name, const char* lib_name) {
//	return reinterpret_cast<void (*)()>load_symbol(function_name, lib_name);
// }

void close_libs() {
	for (unsigned long i; i < loaded_objects.size(); i++) {
		std::cout << "Closing library " << loaded_objects[i].name << "\n";
		dlclose(loaded_objects[i].handle);
	}
}
