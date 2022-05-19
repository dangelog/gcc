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

// { dg-do run { target c++17 } }
// { dg-options "-std=gnu++2b" }

#include <string>
#include <type_traits>
#include <utility>

#include <testsuite_hooks.h>

static_assert(std::is_same_v<decltype(std::declval<std::string>() + std::declval<std::string_view>()), std::string>);
static_assert(std::is_same_v<decltype(std::declval<std::string &>() + std::declval<std::string_view>()), std::string>);
static_assert(std::is_same_v<decltype(std::declval<std::string_view>() + std::declval<std::string>()), std::string>);
static_assert(std::is_same_v<decltype(std::declval<std::string_view>() + std::declval<std::string &>()), std::string>);

struct convertible_to_string
{
  operator std::string() const { return "convertible_to_string"; }
};

struct convertible_to_string_view
{
  operator std::string_view() const { return "convertible_to_sv"; }
};

struct convertible_to_string_view_and_char_star
{
  operator std::string_view() const { return "convertible_to_sv_and_charstar1"; }
  operator const char *() const { return "convertible_to_sv_and_charstar2"; }
};

struct convertible_to_lots
{
  operator std::string_view() const { return "convertible_to_lots1"; }
  operator const char *() const { return "convertible_to_lots2"; }
  operator std::string() const { return "convertible_to_lots3"; }
};

void
test01()
{
  std::string str_0("costa ");
  std::string str_1("marbella");

  std::string tmp;

  std::string_view str_0_view = str_0;
  std::string_view str_1_view = str_1;


  // string
  VERIFY( (str_0 + str_1) == "costa marbella" );
  tmp = str_0;
  VERIFY( (std::move(tmp) + str_1) == "costa marbella" );
  tmp = str_1;
  VERIFY( (str_0 + std::move(tmp)) == "costa marbella" );


  // string + string_view
  VERIFY( (str_0 + str_1_view) == "costa marbella" );
  VERIFY( (str_0_view + str_1) == "costa marbella" );

  tmp = str_0;
  VERIFY( (std::move(tmp) + str_1_view) == "costa marbella" );
  tmp = str_1;
  VERIFY( (str_0_view + std::move(tmp)) == "costa marbella" );


  // string + string literal
  VERIFY( (str_0 + "marbella") == "costa marbella" );
  VERIFY( ("costa " + str_1) == "costa marbella" );

  tmp = str_0;
  VERIFY( (std::move(tmp) + "marbella") == "costa marbella" );
  tmp = str_1;
  VERIFY( ("costa " + std::move(tmp)) == "costa marbella" );


  // string + non-const char *
  VERIFY( (str_0 + str_1.data()) == "costa marbella" );
  VERIFY( (str_0.data() + str_1) == "costa marbella" );

  tmp = str_0;
  VERIFY( (std::move(tmp) + str_1.data()) == "costa marbella" );
  tmp = str_1;
  VERIFY( (str_0.data() + std::move(tmp)) == "costa marbella" );


  // string + const char *
  VERIFY( (str_0 + std::as_const(str_1).data()) == "costa marbella" );
  VERIFY( (std::as_const(str_0).data() + str_1) == "costa marbella" );

  tmp = str_0;
  VERIFY( (std::move(tmp) + std::as_const(str_1).data()) == "costa marbella" );
  tmp = str_1;
  VERIFY( (std::as_const(str_0).data() + std::move(tmp)) == "costa marbella" );


  // convertible to string_view
  convertible_to_string_view conv_string_view;
  VERIFY( (str_0 + conv_string_view) == "costa convertible_to_sv" );
  VERIFY( (conv_string_view + str_1) == "convertible_to_svmarbella" );

  convertible_to_string_view_and_char_star conv_sv_cs;
  VERIFY( (str_0 + conv_sv_cs) == "costa convertible_to_sv_and_charstar1" );
  VERIFY( (conv_sv_cs + str_1) == "convertible_to_sv_and_charstar1marbella" );

  convertible_to_lots conv_lots;
  VERIFY( (str_0 + conv_lots) == "costa convertible_to_lots1" );
  VERIFY( (conv_lots + str_1) == "convertible_to_lots1marbella" );

#if defined(STRING_PLUS_STRING_VIEW_AS_HIDDEN_FRIEND)
  // convertible to string
  convertible_to_string conv_string;
  VERIFY( (str_0 + conv_string) == "costa convertible_to_string" );
  // Hidden friend! doesn't work
  // VERIFY( (str_0_view + conv_string) == "costa convertible_to_string" );

  VERIFY( (conv_string + str_1) == "convertible_to_stringmarbella" );
  // Hidden friend! doesn't work
  // VERIFY( (conv_string + str_1_view) == "convertible_to_stringmarbella" );

  // std::reference_wrapper
  std::reference_wrapper<std::string> str_0_ref_wrap(str_0);
  std::reference_wrapper<std::string> str_1_ref_wrap(str_1);
  std::reference_wrapper<std::string_view> str_0_view_ref_wrap(str_0_view);
  std::reference_wrapper<std::string_view> str_1_view_ref_wrap(str_1_view);
  VERIFY( (str_0_ref_wrap + str_1_ref_wrap) == "costa marbella" );

  VERIFY( (str_0_ref_wrap + str_1_view_ref_wrap) == "costa marbella" );
  VERIFY( (str_0_view_ref_wrap + str_1_ref_wrap) == "costa marbella" );
#endif
}

int main()
{
  test01();
}
