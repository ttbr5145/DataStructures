
#pragma once

#ifndef __GENERAL_HPP__
#define __GENERAL_HPP__

#include <iostream>

using uint = unsigned int;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using uintptr = std::uintptr_t;
using float64 = double;

#define for_range(i, _first, _last) for (int i=_first; i<(_last); ++i)

template <class T=int>
T rd() {
    using std::cin;
    char c=cin.get();
    while (c<'0'||'9'<c) c = cin.get();
    T n = c^'0';
    while (c=cin.get(), '0'<=c&&c<='9')
        n = n*10 + (c^'0');
    return n;
}
template <class T=int>
T rd_s() {
    using std::cin;
    T s=1,n; char c;
    while (c=cin.get(), c<'0'||'9'<c)
        if (c=='-') s=-1;
    n = c^'0';
    while (c=cin.get(), '0'<=c&&c<='9')
        n = n*10 + (c^'0');
    return s*n;
}
template <class T>
T& rd(T& n) { return n = rd<T>(); }


template<class T>
constexpr void _max(T& a, const T& b)
    { if (a<b) a=b; }
template<class T>
constexpr void _min(T& a, const T& b)
    { if (b<a) a=b; }

#endif