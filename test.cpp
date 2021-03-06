/***
  Copyright (c) 2014 Mirco Tischler

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
***/

#include "range.h"

#include <iostream>
#include <vector>

int main() {
        std::vector<int> v {1, 3, 5, 7, 9};

        auto r = range::make_range(v);

        range::for_each(r, [](const int &i) {
                std::cout << i << std::endl;
        });

        auto s = range::divide(r, 3);

        std::cout << range::has(r, 5) << std::endl;

        for(int i: r)
                std::cout << i << std::endl;


        std::cout << "First: " << range::front(r) << std::endl;
        std::cout << "Last: " << range::back(r) << std::endl;

        return 0;
}
