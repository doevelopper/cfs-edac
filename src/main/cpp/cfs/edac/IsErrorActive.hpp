

#ifndef CPPBDD101_EDAC_ISERRORACTIVE_HPP
#define CPPBDD101_EDAC_ISERRORACTIVE_HPP

// IsErrorActive<insigned int> vUint;
#include <thread>
#include <mutex>
#include <functional>

namespace cfs::edac
{
    template< class ParamType >
    class IsErrorActive
    {
public:

        IsErrorActive();
        IsErrorActive(const IsErrorActive & orig) = delete;
        IsErrorActive(IsErrorActive && orig) = delete;
        IsErrorActive & operator=(const IsErrorActive & orig) = delete;
        IsErrorActive & operator=(IsErrorActive && orig) = delete;
        virtual ~IsErrorActive() = default;

        ParamType get () const;
        bool isActive () const;
        [[noreturn]] void set(const ParamType & value, std::mutex & mutex);
        [[noreturn]] void clear ( const ParamType & value, std::mutex & mutex);
        [[noreturn]] void isActive (bool value);

private:

        ParamType m_value;
        bool m_isValid;
    };
}

#endif

