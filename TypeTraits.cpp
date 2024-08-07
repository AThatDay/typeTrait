#include <iostream>
#include <type_traits> // For std::remove_cv

// integral_constant_t definition
template<typename _Tp, _Tp __v>
struct integral_constant_t {
    static constexpr _Tp value = __v;
    typedef _Tp value_type;
    typedef integral_constant_t<_Tp, __v> type;

    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

// false_type_t and true_type_t definitions
typedef integral_constant_t<bool, false> false_type_t;
typedef integral_constant_t<bool, true> true_type_t;

// __is_integral_helper_t definition
template<typename>
struct __is_integral_helper_t : public false_type_t { };

template<>
struct __is_integral_helper_t<bool> : public true_type_t { };

template<>
struct __is_integral_helper_t<int> : public true_type_t { };

// remove_cv definition
template <typename T>
struct remove_cv { typedef typename std::remove_cv<T>::type type; };

// is_integral_t definition
template<typename _Tp>
struct is_integral_t : public __is_integral_helper_t<typename remove_cv<_Tp>::type>::type { };

// Example usage
int main() {
    // Check if various types are integral
    std::cout << "is_integral_t<int>::value: " << is_integral_t<int>::value << std::endl;
    std::cout << "is_integral_t<const int>::value: " << is_integral_t<const int>::value << std::endl;
    std::cout << "is_integral_t<volatile int>::value: " << is_integral_t<volatile int>::value << std::endl;
    std::cout << "is_integral_t<bool>::value: " << is_integral_t<bool>::value << std::endl;
    std::cout << "is_integral_t<float>::value: " << is_integral_t<float>::value << std::endl;
    std::cout << "is_integral_t<double>::value: " << is_integral_t<double>::value << std::endl;

    return 0;
}
