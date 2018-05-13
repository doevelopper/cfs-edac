
#include <cfs/edac/IsErrorActive.hpp>

template< class ParamType >
cfs::edac::IsErrorActive< ParamType >::IsErrorActive()
  : m_value(ParamType() )
  , m_isValid(false)
{

}

template< class ParamType >
void cfs::edac::IsErrorActive< ParamType >::set (const ParamType & value)
{
    m_value = value;
    m_isValid = true;
}

template< class ParamType >
ParamType cfs::edac::IsErrorActive< ParamType >::get () const
{
    return ( m_value );
}

template< class ParamType >
void cfs::edac::IsErrorActive< ParamType >::clear (const ParamType & value)
{
    m_value = nullptr/*value*/;
    m_isValid = false;
}

template< class ParamType >
bool cfs::edac::IsErrorActive< ParamType >::isActive () const
{
    return ( m_isValid );
}

template< class ParamType >
void cfs::edac::IsErrorActive< ParamType >::isActive (bool value)
{
    m_isValid = value;
}


