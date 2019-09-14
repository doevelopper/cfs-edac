

#ifndef CFS_EDAC_NAMEDTYPE_INTERNAL_NAMEDTYPEINTERNAL_HPP
#define CFS_EDAC_NAMEDTYPE_INTERNAL_NAMEDTYPEINTERNAL_HPP

#include <utility>
#include <type_traits>

namespace cfs::edac::namedType::internal
{

    template<typename T>
    using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;

    template <typename T, typename Parameter, template<typename> class ... Skills>
    class NamedType : public Skills<NamedType<T, Parameter, Skills...> >...
    {
        public:

            using UnderlyingType = T;
            explicit constexpr NamedType(T const& value)
                : m_value(value)
            {
            }

            template<typename T_ = T, typename = IsNotReference<T_> >
            explicit constexpr NamedType(T&& value)
                : m_value(std::move(value))
            {
            }

            constexpr T & get()
            {
                return m_value;
            }

            constexpr T const& get() const
            {
                return m_value;
            }

            using ref = NamedType<T&, Parameter, Skills...>;

            operator ref ()
            {
                return ref(m_value);
            }

            struct argument
            {
                template<typename U>
                NamedType operator=(U&& value) const
                {
                    return NamedType(std::forward<U>(value));
                }

                argument() = default;
                argument(argument const&) = delete;
                argument(argument &&) = delete;
                argument& operator=(argument const&) = delete;
                argument& operator=(argument &&) = delete;
            };

        private:

            T m_value;
    };

    template<template<typename T> class StrongType, typename T>
    constexpr StrongType<T> make_named(T const& value)
    {
        return StrongType<T>(value);
    }

}

#endif

