// Copyright (C) 2020 Free Software Foundation, Inc.
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

// { dg-options "-std=gnu++2a" }
// { dg-do run { target c++2a } }

#include <memory>
#include <testsuite_hooks.h>

void
test01()
{
  std::shared_ptr<int> p0;
  int* raw_ptr = nullptr;
  VERIFY( p0 == raw_ptr );
  VERIFY( !(p0 != raw_ptr) );
  VERIFY( !(p0 < raw_ptr) );
  VERIFY( !(p0 > raw_ptr) );
  VERIFY( p0 <= raw_ptr );
  VERIFY( p0 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p0) );
  VERIFY( !(raw_ptr > p0) );
  VERIFY( raw_ptr <= p0 );
  VERIFY( raw_ptr >= p0 );
  VERIFY( std::is_eq(raw_ptr <=> p0) );

  std::shared_ptr<int> p1(new int(1));
  VERIFY( !(p1 == raw_ptr) );
  VERIFY( p1 != raw_ptr );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( p1 > raw_ptr );
  VERIFY( !(p1 <= raw_ptr) );
  VERIFY( p1 >= raw_ptr );
  VERIFY( std::is_gt(p1 <=> raw_ptr) );
  VERIFY( raw_ptr != p1 );
  VERIFY( raw_ptr < p1 );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( !(raw_ptr >= p1) );
  VERIFY( std::is_lt(raw_ptr <=> p1) );

  raw_ptr = p1.get();
  VERIFY( p1 == raw_ptr );
  VERIFY( !(p1 != raw_ptr) );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( !(p1 > raw_ptr) );
  VERIFY( p1 <= raw_ptr );
  VERIFY( p1 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p1) );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( raw_ptr >= p1 );
  VERIFY( std::is_eq(raw_ptr <=> p1) );
}

void
test02()
{
  std::shared_ptr<const int> p0;
  const int* raw_ptr = nullptr;
  VERIFY( p0 == raw_ptr );
  VERIFY( !(p0 != raw_ptr) );
  VERIFY( !(p0 < raw_ptr) );
  VERIFY( !(p0 > raw_ptr) );
  VERIFY( p0 <= raw_ptr );
  VERIFY( p0 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p0) );
  VERIFY( !(raw_ptr > p0) );
  VERIFY( raw_ptr <= p0 );
  VERIFY( raw_ptr >= p0 );
  VERIFY( std::is_eq(raw_ptr <=> p0) );

  std::shared_ptr<const int> p1(new int(1));
  VERIFY( !(p1 == raw_ptr) );
  VERIFY( p1 != raw_ptr );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( p1 > raw_ptr );
  VERIFY( !(p1 <= raw_ptr) );
  VERIFY( p1 >= raw_ptr );
  VERIFY( std::is_gt(p1 <=> raw_ptr) );
  VERIFY( raw_ptr != p1 );
  VERIFY( raw_ptr < p1 );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( !(raw_ptr >= p1) );
  VERIFY( std::is_lt(raw_ptr <=> p1) );

  raw_ptr = p1.get();
  VERIFY( p1 == raw_ptr );
  VERIFY( !(p1 != raw_ptr) );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( !(p1 > raw_ptr) );
  VERIFY( p1 <= raw_ptr );
  VERIFY( p1 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p1) );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( raw_ptr >= p1 );
  VERIFY( std::is_eq(raw_ptr <=> p1) );
}

void
test03()
{
  std::shared_ptr<int[]> p_array(new int[2]{1, 2});
  int* raw_ptr = nullptr;
  VERIFY( !(p_array == raw_ptr) );
  VERIFY( p_array != raw_ptr );
  VERIFY( !(p_array < raw_ptr) );
  VERIFY( p_array > raw_ptr );
  VERIFY( !(p_array <= raw_ptr) );
  VERIFY( p_array >= raw_ptr );
  VERIFY( std::is_gt(p_array <=> raw_ptr) );
  VERIFY( raw_ptr != p_array );
  VERIFY( raw_ptr < p_array );
  VERIFY( !(raw_ptr > p_array) );
  VERIFY( raw_ptr <= p_array );
  VERIFY( !(raw_ptr >= p_array) );
  VERIFY( std::is_lt(raw_ptr <=> p_array) );

  raw_ptr = p_array.get();
  VERIFY( p_array == raw_ptr );
  VERIFY( !(p_array != raw_ptr) );
  VERIFY( !(p_array < raw_ptr) );
  VERIFY( !(p_array > raw_ptr) );
  VERIFY( p_array <= raw_ptr );
  VERIFY( p_array >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p_array) );
  VERIFY( !(raw_ptr > p_array) );
  VERIFY( raw_ptr <= p_array );
  VERIFY( raw_ptr >= p_array );
  VERIFY( std::is_eq(raw_ptr <=> p_array) );

  ++raw_ptr;
  VERIFY( !(p_array == raw_ptr) );
  VERIFY( p_array != raw_ptr );
  VERIFY( p_array < raw_ptr );
  VERIFY( !(p_array > raw_ptr) );
  VERIFY( p_array <= raw_ptr );
  VERIFY( !(p_array >= raw_ptr) );
  VERIFY( std::is_lt(p_array <=> raw_ptr) );
  VERIFY( raw_ptr != p_array );
  VERIFY( !(raw_ptr < p_array) );
  VERIFY( raw_ptr > p_array );
  VERIFY( !(raw_ptr <= p_array) );
  VERIFY( raw_ptr >= p_array );
  VERIFY( std::is_gt(raw_ptr <=> p_array) );
}

template<typename T>
class shared_ptr_derived : public std::shared_ptr<T>
{
public:
  using std::shared_ptr<T>::shared_ptr;
};

void
test04()
{
  shared_ptr_derived<int> p0;
  int* raw_ptr = nullptr;
  VERIFY( p0 == raw_ptr );
  VERIFY( !(p0 != raw_ptr) );
  VERIFY( !(p0 < raw_ptr) );
  VERIFY( !(p0 > raw_ptr) );
  VERIFY( p0 <= raw_ptr );
  VERIFY( p0 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p0) );
  VERIFY( !(raw_ptr > p0) );
  VERIFY( raw_ptr <= p0 );
  VERIFY( raw_ptr >= p0 );
  VERIFY( std::is_eq(raw_ptr <=> p0) );

  shared_ptr_derived<int> p1(new int(1));
  VERIFY( !(p1 == raw_ptr) );
  VERIFY( p1 != raw_ptr );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( p1 > raw_ptr );
  VERIFY( !(p1 <= raw_ptr) );
  VERIFY( p1 >= raw_ptr );
  VERIFY( std::is_gt(p1 <=> raw_ptr) );
  VERIFY( raw_ptr != p1 );
  VERIFY( raw_ptr < p1 );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( !(raw_ptr >= p1) );
  VERIFY( std::is_lt(raw_ptr <=> p1) );

  raw_ptr = p1.get();
  VERIFY( p1 == raw_ptr );
  VERIFY( !(p1 != raw_ptr) );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( !(p1 > raw_ptr) );
  VERIFY( p1 <= raw_ptr );
  VERIFY( p1 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p1) );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( raw_ptr >= p1 );
  VERIFY( std::is_eq(raw_ptr <=> p1) );
}

void
test05()
{
  shared_ptr_derived<const int> p0;
  const int* raw_ptr = nullptr;
  VERIFY( p0 == raw_ptr );
  VERIFY( !(p0 != raw_ptr) );
  VERIFY( !(p0 < raw_ptr) );
  VERIFY( !(p0 > raw_ptr) );
  VERIFY( p0 <= raw_ptr );
  VERIFY( p0 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p0) );
  VERIFY( !(raw_ptr > p0) );
  VERIFY( raw_ptr <= p0 );
  VERIFY( raw_ptr >= p0 );
  VERIFY( std::is_eq(raw_ptr <=> p0) );

  shared_ptr_derived<const int> p1(new int(1));
  VERIFY( !(p1 == raw_ptr) );
  VERIFY( p1 != raw_ptr );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( p1 > raw_ptr );
  VERIFY( !(p1 <= raw_ptr) );
  VERIFY( p1 >= raw_ptr );
  VERIFY( std::is_gt(p1 <=> raw_ptr) );
  VERIFY( raw_ptr != p1 );
  VERIFY( raw_ptr < p1 );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( !(raw_ptr >= p1) );
  VERIFY( std::is_lt(raw_ptr <=> p1) );

  raw_ptr = p1.get();
  VERIFY( p1 == raw_ptr );
  VERIFY( !(p1 != raw_ptr) );
  VERIFY( !(p1 < raw_ptr) );
  VERIFY( !(p1 > raw_ptr) );
  VERIFY( p1 <= raw_ptr );
  VERIFY( p1 >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p1) );
  VERIFY( !(raw_ptr > p1) );
  VERIFY( raw_ptr <= p1 );
  VERIFY( raw_ptr >= p1 );
  VERIFY( std::is_eq(raw_ptr <=> p1) );
}

void
test06()
{
  shared_ptr_derived<int> p_array(new int[2]{1, 2});
  int* raw_ptr = nullptr;
  VERIFY( !(p_array == raw_ptr) );
  VERIFY( p_array != raw_ptr );
  VERIFY( !(p_array < raw_ptr) );
  VERIFY( p_array > raw_ptr );
  VERIFY( !(p_array <= raw_ptr) );
  VERIFY( p_array >= raw_ptr );
  VERIFY( std::is_gt(p_array <=> raw_ptr) );
  VERIFY( raw_ptr != p_array );
  VERIFY( raw_ptr < p_array );
  VERIFY( !(raw_ptr > p_array) );
  VERIFY( raw_ptr <= p_array );
  VERIFY( !(raw_ptr >= p_array) );
  VERIFY( std::is_lt(raw_ptr <=> p_array) );

  raw_ptr = p_array.get();
  VERIFY( p_array == raw_ptr );
  VERIFY( !(p_array != raw_ptr) );
  VERIFY( !(p_array < raw_ptr) );
  VERIFY( !(p_array > raw_ptr) );
  VERIFY( p_array <= raw_ptr );
  VERIFY( p_array >= raw_ptr );
  VERIFY( raw_ptr == raw_ptr );
  VERIFY( !(raw_ptr < p_array) );
  VERIFY( !(raw_ptr > p_array) );
  VERIFY( raw_ptr <= p_array );
  VERIFY( raw_ptr >= p_array );
  VERIFY( std::is_eq(raw_ptr <=> p_array) );

  ++raw_ptr;
  VERIFY( !(p_array == raw_ptr) );
  VERIFY( p_array != raw_ptr );
  VERIFY( p_array < raw_ptr );
  VERIFY( !(p_array > raw_ptr) );
  VERIFY( p_array <= raw_ptr );
  VERIFY( !(p_array >= raw_ptr) );
  VERIFY( std::is_lt(p_array <=> raw_ptr) );
  VERIFY( raw_ptr != p_array );
  VERIFY( !(raw_ptr < p_array) );
  VERIFY( raw_ptr > p_array );
  VERIFY( !(raw_ptr <= p_array) );
  VERIFY( raw_ptr >= p_array );
  VERIFY( std::is_gt(raw_ptr <=> p_array) );
}

void
test07()
{
  shared_ptr_derived<int> p0;
  shared_ptr_derived<int> p1;
  VERIFY( p0 == p1 );
  VERIFY( !(p0 != p1) );
  VERIFY( !(p0 < p1) );
  VERIFY( !(p0 > p1) );
  VERIFY( p0 <= p1 );
  VERIFY( p0 >= p1 );
  VERIFY( p1 == p1 );
  VERIFY( !(p1 < p0) );
  VERIFY( !(p1 > p0) );
  VERIFY( p1 <= p0 );
  VERIFY( p1 >= p0 );
  VERIFY( std::is_eq(p1 <=> p0) );
}

int
main()
{
  test01();
  test02();
  test03();
  test04();
  test05();
  test06();
  test07();
}
