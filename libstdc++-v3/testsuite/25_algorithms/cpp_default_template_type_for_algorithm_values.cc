// Copyright (C) 2019-2020 Free Software Foundation, Inc.
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

// { dg-options "-std=gnu++2b" }

#include <algorithm>
#include <ranges>
#include <numeric>
#include <iterator>

#include <vector>

#include <testsuite_hooks.h>

#ifndef __cpp_lib_default_template_type_for_algorithm_values
# error "Feature-test macro missing"
#endif

#if __cplusplus <= 202002L
# error "Wrong C++ version"
#endif

struct point
{
  int x; int y;
  bool operator==(const point&) const noexcept = default;
};

void
test_find()
{
  const std::vector<point> v{ {0, 0}, {1, 1}, {2, 2}, {3, 3} };

  VERIFY(std::find(v.begin(), v.end(), {0, 0}) == v.begin());
  VERIFY(std::find(v.begin(), v.end(), {1, 1}) == v.begin() + 1);
  VERIFY(std::find(v.begin(), v.end(), {2, 2}) == v.begin() + 2);
  VERIFY(std::find(v.begin(), v.end(), {9, 9}) == v.end());

  VERIFY(std::ranges::find(v, {0, 0}) == v.begin());
  VERIFY(std::ranges::find(v, {1, 1}) == v.begin() + 1);
  VERIFY(std::ranges::find(v, {2, 2}) == v.begin() + 2);
  VERIFY(std::ranges::find(v, {9, 9}) == v.end());
}

void
test_count()
{
  const std::vector<point> v{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };

  VERIFY(std::count(v.begin(), v.end(), {0, 0}) == 1);
  VERIFY(std::count(v.begin(), v.end(), {1, 1}) == 2);
  VERIFY(std::count(v.begin(), v.end(), {2, 2}) == 3);
  VERIFY(std::count(v.begin(), v.end(), {9, 9}) == 0);

  VERIFY(std::ranges::count(v, {0, 0}) == 1);
  VERIFY(std::ranges::count(v, {1, 1}) == 2);
  VERIFY(std::ranges::count(v, {2, 2}) == 3);
  VERIFY(std::ranges::count(v, {9, 9}) == 0);
}

void
test_search_n()
{
  const std::vector<point> v{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  VERIFY(std::search_n(v.begin(), v.end(), 2, {1, 1}) == v.begin() + 3);

  const auto& sub = std::ranges::search_n(v, 2, {1, 1});
  VERIFY(sub.begin() == v.begin() + 3);
  VERIFY(sub.end() == v.begin() + 5);
}

void
test_replace()
{
  const std::vector<point> orig{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };

  std::vector<point> v = orig;
  std::replace(v.begin(), v.end(), {1, 1}, {9, 9});
  VERIFY(v[0] == point(0, 0));
  VERIFY(v[1] == point(9, 9));
  VERIFY(v[2] == point(2, 2));
  VERIFY(v[3] == point(9, 9));
  VERIFY(v[4] == point(2, 2));
  VERIFY(v[5] == point(3, 3));
  VERIFY(v[6] == point(2, 2));

  v = orig;
  std::ranges::replace(v, {1, 1}, {9, 9});
  VERIFY(v[0] == point(0, 0));
  VERIFY(v[1] == point(9, 9));
  VERIFY(v[2] == point(2, 2));
  VERIFY(v[3] == point(9, 9));
  VERIFY(v[4] == point(2, 2));
  VERIFY(v[5] == point(3, 3));
  VERIFY(v[6] == point(2, 2));
}

void
test_replace_if()
{
  const std::vector<point> orig{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  const auto predicate = [](point p) -> bool
  {
    return (p.x % 2) == 0;
  };

  std::vector<point> v = orig;
  std::replace_if(v.begin(), v.end(), predicate, {9, 9});
  VERIFY(v[0] == point(9, 9));
  VERIFY(v[1] == point(1, 1));
  VERIFY(v[2] == point(9, 9));
  VERIFY(v[3] == point(1, 1));
  VERIFY(v[4] == point(9, 9));
  VERIFY(v[5] == point(3, 3));
  VERIFY(v[6] == point(9, 9));

  v = orig;
  std::ranges::replace_if(v, predicate, {9, 9});
  VERIFY(v[0] == point(9, 9));
  VERIFY(v[1] == point(1, 1));
  VERIFY(v[2] == point(9, 9));
  VERIFY(v[3] == point(1, 1));
  VERIFY(v[4] == point(9, 9));
  VERIFY(v[5] == point(3, 3));
  VERIFY(v[6] == point(9, 9));
}

void
test_replace_copy()
{
  const std::vector<point> orig{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  std::vector<point> dest(orig.size());
  std::replace_copy(orig.begin(), orig.end(), dest.begin(), {1, 1}, {9, 9});
  VERIFY(dest[0] == point(0, 0));
  VERIFY(dest[1] == point(9, 9));
  VERIFY(dest[2] == point(2, 2));
  VERIFY(dest[3] == point(9, 9));
  VERIFY(dest[4] == point(2, 2));
  VERIFY(dest[5] == point(3, 3));
  VERIFY(dest[6] == point(2, 2));

  dest = orig;
  std::ranges::replace_copy(orig, dest.begin(), {1, 1}, {9, 9});
  VERIFY(dest[0] == point(0, 0));
  VERIFY(dest[1] == point(9, 9));
  VERIFY(dest[2] == point(2, 2));
  VERIFY(dest[3] == point(9, 9));
  VERIFY(dest[4] == point(2, 2));
  VERIFY(dest[5] == point(3, 3));
  VERIFY(dest[6] == point(2, 2));
}

void
test_replace_copy_if()
{
  const std::vector<point> orig{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  const auto predicate = [](point p) -> bool
  {
    return (p.x % 2) == 0;
  };

  std::vector<point> dest(orig.size());
  std::replace_copy_if(orig.begin(), orig.end(), dest.begin(), predicate, {9, 9});
  VERIFY(dest[0] == point(9, 9));
  VERIFY(dest[1] == point(1, 1));
  VERIFY(dest[2] == point(9, 9));
  VERIFY(dest[3] == point(1, 1));
  VERIFY(dest[4] == point(9, 9));
  VERIFY(dest[5] == point(3, 3));
  VERIFY(dest[6] == point(9, 9));

  dest = orig;
  std::ranges::replace_copy_if(orig, dest.begin(), predicate, {9, 9});
  VERIFY(dest[0] == point(9, 9));
  VERIFY(dest[1] == point(1, 1));
  VERIFY(dest[2] == point(9, 9));
  VERIFY(dest[3] == point(1, 1));
  VERIFY(dest[4] == point(9, 9));
  VERIFY(dest[5] == point(3, 3));
  VERIFY(dest[6] == point(9, 9));
}

void
test_fill()
{
  std::vector<point> v(10);
  std::fill(v.begin(), v.end(), {1, 1});
  for (const auto& p : v)
    VERIFY(p == point(1, 1));

  std::ranges::fill(v, {9, 9});
  for (const auto& p : v)
    VERIFY(p == point(9, 9));
}

void
test_fill_n()
{
  std::vector<point> v(10, {0, 0});
  std::fill_n(v.begin(), 5, {1, 1});
  for (auto i = v.begin(); i != v.begin() + 5; ++i)
    VERIFY(*i == point(1, 1));
  for (auto i = v.begin() + 5; i != v.end(); ++i)
    VERIFY(*i == point(0, 0));

  std::ranges::fill_n(v.begin() + 5, 5, {9, 9});
  for (auto i = v.begin(); i != v.begin() + 5; ++i)
    VERIFY(*i == point(1, 1));
  for (auto i = v.begin() + 5; i != v.end(); ++i)
    VERIFY(*i == point(9, 9));
}

void
test_remove()
{
  const std::vector<point> orig{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };

  std::vector<point> v = orig;
  v.erase(std::remove(v.begin(), v.end(), {1, 1}), v.end());
  VERIFY(v.size() == 5);
  VERIFY(v[0] == point(0, 0));
  VERIFY(v[1] == point(2, 2));
  VERIFY(v[2] == point(2, 2));
  VERIFY(v[3] == point(3, 3));
  VERIFY(v[4] == point(2, 2));

  v = orig;
  const auto& removed = std::ranges::remove(v, {1, 1});
  v.erase(removed.begin(), removed.end());
  VERIFY(v.size() == 5);
  VERIFY(v[0] == point(0, 0));
  VERIFY(v[1] == point(2, 2));
  VERIFY(v[2] == point(2, 2));
  VERIFY(v[3] == point(3, 3));
  VERIFY(v[4] == point(2, 2));
}

void
test_remove_copy()
{
  const std::vector<point> v{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  std::vector<point> dest;
  std::remove_copy(v.begin(), v.end(), std::back_inserter(dest), {1, 1});
  VERIFY(dest.size() == 5);

  dest.clear();
  std::ranges::remove_copy(v, std::back_inserter(dest), {1, 1});
  VERIFY(dest.size() == 5);
}

void
test_lower_bound()
{
}

void
test_upper_bound()
{
}

void
test_equal_range()
{
}

void
test_binary_search()
{
}

void
test_vector_erase()
{
  std::vector<point> v{ {0, 0}, {1, 1}, {2, 2}, {1, 1}, {2, 2}, {3, 3}, {2, 2} };
  erase(v, {2, 2});
  VERIFY(v.size() == 4);
  VERIFY(v[0] == point(0, 0));
  VERIFY(v[1] == point(1, 1));
  VERIFY(v[2] == point(1, 1));
  VERIFY(v[3] == point(3, 3));
}

void
test_proxy_iterators()
{
  std::vector<bool> v;
  std::find(v.begin(), v.end(), {});
  std::ranges::find(v.begin(), v.end(), {});
  std::ranges::find(v.begin(), v.end(), {true});
  std::ranges::find(v.begin(), v.end(), {false});
  std::ranges::find(v, {});
  std::ranges::find(v, {true});
  std::ranges::find(v, {false});
}

void
test_projection()
{
  std::vector<point> v{ {0, 10}, {1, 11}, {2, 12}, {1, 11}, {2, 12}, {3, 13}, {2, 12} };
  auto i = std::ranges::find(v, 2, &point::x);
  VERIFY(i == v.begin() + 2);
  i = std::ranges::find(v, 13, &point::y);
  VERIFY(i == v.begin() + 5);
  i = std::ranges::find(v, -1, &point::x);
  VERIFY(i == v.end());
}

int
main()
{
  test_find();
  test_count();
  test_search_n();
  test_replace();
  test_replace_if();
  test_replace_copy();
  test_replace_copy_if();
  test_fill();
  test_fill_n();
  test_remove();
  test_remove_copy();

  test_lower_bound();
  test_upper_bound();
  test_equal_range();
  test_binary_search();

  test_vector_erase();

  test_proxy_iterators();
  test_projection();
}
