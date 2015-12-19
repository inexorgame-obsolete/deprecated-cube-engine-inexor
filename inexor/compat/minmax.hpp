
#ifndef INEXOR_COMPAT_MINMAX_HPP
#define INEXOR_COMPAT_MINMAX_HPP

#include <algorithm>

#ifdef _MSC_VER
namespace inexor {
namespace compat {

template <class T>
constexpr const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template <class T, class Compare>
constexpr const T& max(const T& a, const T& b, Compare comp)
{
    return (comp(a, b)) ? b : a;
}

template <class T>
constexpr T max(std::initializer_list<T> ilist)
{
    return *std::max_element(ilist.begin(), ilist.end());
}

template <class T, class Compare>
constexpr T max(std::initializer_list<T> ilist, Compare comp)
{
    return *std::max_element(ilist.begin(), ilist.end(), comp);
}

template <class T> constexpr const T& min(const T& a, const T& b)
{
    return (b < a) ? b : a;
}

template <class T, class Compare>
constexpr const T& min(const T& a, const T& b, Compare comp)
{
    return (comp(b, a)) ? b : a;
}

template <class T>
constexpr T min(std::initializer_list<T> ilist)
{
    return *std::min_element(ilist.begin(), ilist.end());
}

template <class T, class Compare>
constexpr T min(std::initializer_list<T> ilist, Compare comp)
{
    return *std::min_element(ilist.begin(), ilist.end(), comp);
}

} // namespace compat
} // namespace inexor
#else

namespace inexor {
namespace compat {

using std::min;
using std::max;

} // namespace compat
} // namespace inexor

#endif


#endif // INEXOR_COMPAT_MINMAX_HPP
