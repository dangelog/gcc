// Copyright (C) 2020-2023 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <string>
#include <type_traits>
#include <utility>

#include <testsuite_hooks.h>

// "legacy" string view and operators
template <typename CharT>
struct basic_my_string_view
{
  std::basic_string_view<CharT> view;
};

using my_string_view = basic_my_string_view<char>;

template <class T>
struct my_type_identity { using type = T; };
template <class T>
using my_type_identity_t = typename my_type_identity<T>::type;

template <typename CharT, typename T, typename A>
std::string operator+(const std::basic_string<CharT, T, A> &s, basic_my_string_view<CharT> msv)
{
  std::string result = s;
  result += msv.view;
  result += " using my_string_view";
  return result;
}

template <typename CharT, typename T, typename A>
std::string operator+(const std::basic_string<CharT, T, A> &s, my_type_identity_t<basic_my_string_view<CharT>> msv)
{
  std::string result = s;
  result += msv.view;
  result += " using my_string_view";
  return result;
}


struct buffer
{
  std::string buf;

  // "legacy"
  operator my_string_view() const { return my_string_view{buf}; }
  // "modern"
  operator std::string_view() const { return std::string_view{buf}; }
};

int
main()
{
  std::string s = "costa ";
  buffer b{"marbella"};

  std::string result = s + b;
  VERIFY( result == "costa marbella using my_string_view" );
}
