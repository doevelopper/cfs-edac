

#include <cfs/edac/IsErrorActive.hpp>

using namespace cfs::edac;

template< class ParamType >
IsErrorActive< ParamType >::IsErrorActive()
    : m_value(ParamType() )
    , m_isValid(false)
{
}

template< class ParamType >
void IsErrorActive< ParamType >::set (const ParamType & value, std::mutex & mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_value = value;
    m_isValid = true;
}

template< class ParamType >
ParamType IsErrorActive< ParamType >::get () const
{
    return ( m_value );
}

template< class ParamType >
void IsErrorActive< ParamType >::clear (const ParamType & value, std::mutex & mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_value = nullptr /*value*/;
    m_isValid = false;
}

template< class ParamType >
bool IsErrorActive< ParamType >::isActive () const
{
    return ( m_isValid );
}

template< class ParamType >
void IsErrorActive< ParamType >::isActive (bool value)
{
    m_isValid = value;
}

