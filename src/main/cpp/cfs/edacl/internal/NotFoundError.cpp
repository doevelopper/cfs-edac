

#include <cfs/edac/NotFoundError.hpp>
template< class T >
inline NotFoundError< T >::NotFoundError(const std::string& message,
                                         const T& value) throw()
	: std::runtime_error(message)
	, m_value(value)
{
}

template< class T >
inline const T& NotFoundError< T >::get_value(void) const throw()
{
	return m_value;
}

template< class T >
inline NotFoundError< T >::~NotFoundError(void) throw()
{
}

