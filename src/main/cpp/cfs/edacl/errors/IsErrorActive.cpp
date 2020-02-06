

#include <edac/errors/IsErrorActive.hpp>
template <class ParamType>
IsErrorActive<ParamType>::IsErrorActive()
    : m_value(ParamType())
    ,m_isValid(false)
{
}

template <class ParamType>
void IsErrorActive<ParamType>::value (const ParamType &value)
{
    m_value = value;
    m_isValid = true;
}

template <class ParamType>
ParamType IsErrorActive<ParamType>::value () const
{
    return (m_value);
}

template <class ParamType>
bool IsErrorActive<ParamType>::isActive () const
{
    return (m_isValid);
}

template <class ParamType>
void IsErrorActive<ParamType>::isActive (bool value)
{
    m_isValid = value;
}

