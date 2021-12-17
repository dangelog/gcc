// { dg-do compile }
// { dg-options "-std=gnu++2b" }

#include <type_traits>
#include <testsuite_tr1.h>

#ifndef __cpp_lib_is_value_preserving_convertible
# error "Feature-test macro missing"
#endif

#if __cplusplus <= 202002L
# error "Wrong C++ version"
#endif

class float16 // 16 bit, 1 sign, 5 exponent (bias 15), 10 mantissa (1 bit implicit)
{
public:
  float16(float);
  operator float() const;
};

class unbounded_int;
class unbounded_uint;
class unbounded_fp;

class unbounded_int
{
public:
  template <typename T,
            std::enable_if_t<std::is_integral_v<T>, bool> = false>
  unbounded_int(T);
  unbounded_int(unbounded_uint);
};

class unbounded_uint
{
public:
  template <typename T,
            std::enable_if_t<std::is_integral_v<T> && !std::is_signed_v<T>, bool> = false>
  unbounded_uint(T);
};

class unbounded_fp
{
public:
  unbounded_fp(unbounded_int);
  unbounded_fp(unbounded_uint);
  unbounded_fp(long double);
};

namespace std {
template<>
class numeric_limits<float16> : public numeric_limits<float>
{
public:
  static constexpr int digits = 11;
  static constexpr int min_exponent = -13;
  static constexpr int max_exponent = 16;
  static constexpr int digits10 = 3;
  static constexpr int max_digits10 = 5;
  static constexpr int min_exponent10 = -4;
  static constexpr int max_exponent10 = 4;
};

template<>
class numeric_limits<unbounded_int> : public numeric_limits<int>
{
public:
  static constexpr bool is_bounded = false;
};

template<>
class numeric_limits<unbounded_uint> : public numeric_limits<unsigned int>
{
public:
  static constexpr bool is_bounded = false;
};

template<>
class numeric_limits<unbounded_fp> : public numeric_limits<long double>
{
public:
  static constexpr bool is_bounded = false;
};

} // namespace std


void test01()
{
  using std::is_value_preserving_convertible;
  using namespace __gnu_test;

  // Positive tests.

  // Fundamental types into themselves
  static_assert(test_relationship<is_value_preserving_convertible, bool, bool>(true));

  static_assert(test_relationship<is_value_preserving_convertible, char, char>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned char, unsigned char>(true));
  static_assert(test_relationship<is_value_preserving_convertible, signed char, signed char>(true));

  static_assert(test_relationship<is_value_preserving_convertible, short, short>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned short, unsigned short>(true));
  static_assert(test_relationship<is_value_preserving_convertible, int, int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, unsigned int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, long, long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned long, unsigned long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, long long, long long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned long long, unsigned long long>(true));

  // Into wider types
  static_assert(test_relationship<is_value_preserving_convertible, float, float>(true));
  static_assert(test_relationship<is_value_preserving_convertible, double, double>(true));
  static_assert(test_relationship<is_value_preserving_convertible, long double, long double>(true));

  static_assert(test_relationship<is_value_preserving_convertible, bool, unsigned char>(true));
  static_assert(test_relationship<is_value_preserving_convertible, bool, unsigned short>(true));
  static_assert(test_relationship<is_value_preserving_convertible, bool, unsigned int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, bool, unsigned long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, bool, unsigned long long>(true));

  static_assert(test_relationship<is_value_preserving_convertible, signed char, short>(true));
  static_assert(test_relationship<is_value_preserving_convertible, signed char, int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, signed char, long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, signed char, long long>(true));

  static_assert(test_relationship<is_value_preserving_convertible, short, int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, short, long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, short, long long>(true));

  static_assert(test_relationship<is_value_preserving_convertible, int, long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, int, long long>(true));

  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, unsigned long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, unsigned long long>(true));

  static_assert(test_relationship<is_value_preserving_convertible, long, long long>(true));

  // Misc, non portable
  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, long long>(true));
  static_assert(test_relationship<is_value_preserving_convertible, int, double>(true));

  // Negative tests
  static_assert(test_relationship<is_value_preserving_convertible, int, unsigned int>(false));
  static_assert(test_relationship<is_value_preserving_convertible, int, unsigned long>(false));
  static_assert(test_relationship<is_value_preserving_convertible, int, unsigned long long>(false));

  static_assert(test_relationship<is_value_preserving_convertible, unsigned long long, int>(false));

  static_assert(test_relationship<is_value_preserving_convertible, float, int>(false));
  static_assert(test_relationship<is_value_preserving_convertible, double, int>(false));
  static_assert(test_relationship<is_value_preserving_convertible, float, unsigned long long>(false));
  static_assert(test_relationship<is_value_preserving_convertible, double, unsigned long long>(false));

  // User-defined types
  static_assert(test_relationship<is_value_preserving_convertible, float16, float16>(true));
  static_assert(test_relationship<is_value_preserving_convertible, bool, float16>(true));
  static_assert(test_relationship<is_value_preserving_convertible, char, float16>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned char, float16>(true));
  static_assert(test_relationship<is_value_preserving_convertible, signed char, float16>(true));
  static_assert(test_relationship<is_value_preserving_convertible, float16, float>(true));
  static_assert(test_relationship<is_value_preserving_convertible, float16, double>(true));
  static_assert(test_relationship<is_value_preserving_convertible, float16, long double>(true));

  static_assert(test_relationship<is_value_preserving_convertible, float, float16>(false));
  static_assert(test_relationship<is_value_preserving_convertible, double, float16>(false));

  static_assert(test_relationship<is_value_preserving_convertible, int, float16>(false));
  static_assert(test_relationship<is_value_preserving_convertible, long, float16>(false));

  // Unbounded
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_int, unbounded_int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_uint, unbounded_uint>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_fp, unbounded_fp>(true));

  static_assert(test_relationship<is_value_preserving_convertible, int, unbounded_int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, long, unbounded_int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, unbounded_int>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_uint, unbounded_int>(true));

  static_assert(test_relationship<is_value_preserving_convertible, double, unbounded_int>(false));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_fp, unbounded_int>(false));

  static_assert(test_relationship<is_value_preserving_convertible, unsigned int, unbounded_uint>(true));
  static_assert(test_relationship<is_value_preserving_convertible, int, unbounded_uint>(false));
  static_assert(test_relationship<is_value_preserving_convertible, unsigned long long, unbounded_uint>(true));
  static_assert(test_relationship<is_value_preserving_convertible, double, unbounded_uint>(false));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_fp, unbounded_uint>(false));

  static_assert(test_relationship<is_value_preserving_convertible, int, unbounded_fp>(true));
  static_assert(test_relationship<is_value_preserving_convertible, double, unbounded_fp>(true));
  static_assert(test_relationship<is_value_preserving_convertible, long double, unbounded_fp>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_int, unbounded_fp>(true));
  static_assert(test_relationship<is_value_preserving_convertible, unbounded_uint, unbounded_fp>(true));
}

