/***
  Copyright 2014 Mirco Tischler

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE./***
***/

#ifndef RANGE_H_
#define RANGE_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <utility>

namespace range {

template <class Iterator>
class range {
    public:
        typedef Iterator iterator;

        range() = delete;
        range(const Iterator& begin, const Iterator& end);

        constexpr Iterator begin() const;
        constexpr Iterator end() const;

        constexpr bool empty() const;
        constexpr size_t size() const;

    private:
        const iterator first;
        const iterator last;
};

template <class Iterator>
range<Iterator>::range(const Iterator& begin, const Iterator& end)
    : first(begin), last(end) {}

template <class Iterator>
constexpr Iterator range<Iterator>::begin() const {
        return first;
}

template <class Iterator>
constexpr Iterator range<Iterator>::end() const {
        return last;
}

template <class Iterator>
constexpr bool range<Iterator>::empty() const {
        return first == last ? true : false;
}

template <class Iterator>
constexpr size_t range<Iterator>::size() const {
        return std::distance(first, last);
}

template <class C>
constexpr auto size(const C& c) -> decltype(c.size()) {
        return c.size();
}

template <class C>
constexpr auto empty(const C& c) -> decltype(c.empty()) {
        return c.empty();
}

template <class C>
constexpr auto front(const C& c) -> decltype(*std::begin(c)) { // undefined behaviour if c is empty
        return *std::begin(c);
}

template <class C>
constexpr auto back(const C& c) -> decltype(*--std::end(c)) { // undefined behaviour if c is empty
        return *std::prev(std::end(c));
}

template <class C>
range<typename std::conditional<std::is_const<C>::value, typename C::const_iterator, typename C::iterator>::type> make_range(C& c) {
        return range<typename std::conditional<std::is_const<C>::value, typename C::const_iterator, typename C::iterator>::type>(std::begin(c), std::end(c));
}

// algorithms for range-like classes

template <class C, class T>
constexpr bool has(const C& c, const T& t) {
        return find(std::begin(c), std::end(c), t) == std::end(c) ? false : true;
}

template <class C, class Function>
Function for_each(const C& c, Function fn) {
        return std::for_each(std::begin(c), std::end(c), fn);
}

// Divide range in <Divisor> equal subranges.
template <class C>
std::vector<C> divide(C& c, const unsigned divisor) {
        assert(divisor > 0);

        std::vector<C> results;
        results.reserve(divisor);

        auto last = std::begin(c);
        auto d = size(c) / divisor;
        auto r = size(c) % divisor;
        while(last != std::end(c)) {
                auto first = last;
                std::advance(last, d);
                if(r > 0) {
                        std::advance(last, 1);
                        --r;
                }
                results.emplace_back(first, last);
        }

        return results;
}

template <class C, class UnaryPredicate>
typename C::iterator find_if(const C& c, UnaryPredicate pred) {
        return find_if(std::begin(c), std::end(c), pred);
}

} // namespace range

#endif // RANGE_H_
