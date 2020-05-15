

#ifndef CFS_UTILS_HELPERS_HPP
#define CFS_UTILS_HELPERS_HPP

#include <system_error>
#include <type_traits>
#include <memory>

namespace cfs::utils
{
    template<class T>
    using has_value_impl = decltype( std::declval<T>().value );

    template <class T>
    struct is_error_type_default
    {
        static constexpr bool value = has_value<T>::value || std::is_base_of<std::exception,T>::value;
    };

    template <class T>
    struct is_type : cfs::utils::is_error_type_default<T> { };

    template <class T>
    struct is_type<T const>: is_type<T> { };

    template <class T>
    struct is_type<T const &>: is_type<T> { };

    template <class T>
    struct is_type<T &>: is_type<T> { };

    template <>
    struct is_type<std::error_code>: std::false_type { };
    /*
     * Count of elements in static array
     */
    template <typename T, size_t N>
    constexpr size_t countof(const T (&)[N]) noexcept { return N; }
    /*
     * Count of elements in any other STL container
     */
    template <typename T>
    size_t countof(const T& container) noexcept { return container.size(); }
}
#endif

