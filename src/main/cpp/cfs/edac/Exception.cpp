
#include <cfs/edac/Exception.hpp>


cfs::edac::Exception::Exception( int code )
  : m_stackTrace(std::string("Stack Trace"))
  , m_message(std::string("StackTrace"))
  , m_location(ERROR_LOCATION)
  , m_code( code )
{
}

const char * cfs::edac::Exception::what () const throw ( )
{
    return ( m_message.c_str());
}

const char * cfs::edac::Exception::where () const throw ( )
{
    return ( m_location.c_str());
}

std::string cfs::edac::Exception::stackTrace () const
{
   return (std::string("Stack Trace"));
}
