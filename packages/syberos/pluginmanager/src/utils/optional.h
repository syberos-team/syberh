#ifndef OPTIONAL_H
#define OPTIONAL_H

/*
    optional<T>
    make_optional(t)

    See std(::experimental)::optional.
*/

// TODO: replace by #include <(experimental/)optional> depending on compiler and C++ version
#include "optional.hpp"

namespace Utils {

// --> Utils::optional
using std::experimental::optional;
// --> Utils::nullopt
using std::experimental::nullopt;
using std::experimental::nullopt_t;
// --> Utils::in_place
using std::experimental::in_place;

// TODO: make_optional is a copy, since there is no sensible way to import functions in C++
template <class T>
constexpr optional<typename std::decay<T>::type> make_optional(T&& v)
{
  return optional<typename std::decay<T>::type>(std::experimental::constexpr_forward<T>(v));
}

template <class X>
constexpr optional<X&> make_optional(std::reference_wrapper<X> v)
{
  return optional<X&>(v.get());
}

} // Utils

#endif // OPTIONAL_H
