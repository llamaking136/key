//
// autorelease.cpp
//
// created at 24/07/2021 17:45:13
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


#include "autorelease.hpp"

AutoreleasePool::AutoreleasePool() {}

AutoreleasePool::~AutoreleasePool() {
	this->drain();
}

unsigned long AutoreleasePool::size() {
	return this->releaseFunctions.size();
}

void AutoreleasePool::appendReleaseFunction(void (*function)()) {
	this->releaseFunctions.push_back(function);
}

void AutoreleasePool::drain() {
	void (*current_release_function)();

	for (unsigned long i = 0; i < this->releaseFunctions.size(); i++) {
		current_release_function = this->releaseFunctions[i];
		current_release_function();
	}
}
