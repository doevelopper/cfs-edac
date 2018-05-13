
#include <cfs/edac/Exception.hpp>

using namespace cfs::edac;

Exception::Exception( int code )
    : m_code( code )
{
}

const char * Exception::what () const throw ( )
{
    return ( m_message.c_str());
}

const char * Exception::where () const throw ( )
{
    return ( m_location.c_str());
}

std::string Exception::stackTrace () const
{

}
