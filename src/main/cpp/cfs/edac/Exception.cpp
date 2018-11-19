

#include <cfs/edac/Exception.hpp>


cfs::edac::Exception::Exception( int code )
    : m_who(std::string())
    , m_where(std::string())
    , m_reason(std::string())
    , m_oldHandler(nullptr)
    , m_stackTrace(std::string("Stack Trace"))
    , m_message(std::string("StackTrace"))
    , m_location(ERROR_LOCATION)
    , m_code( code )
{
}

cfs::edac::Exception::Exception(std::terminate_handler handler)
    : m_who(std::string())
    , m_where(std::string())
    , m_reason(std::string())
    , m_oldHandler(std::set_terminate(handler))
    , m_stackTrace(std::string("Stack Trace"))
    , m_message(std::string("StackTrace"))
    , m_location(ERROR_LOCATION)
    , m_code(0)
{
    m_oldHandler = std::set_terminate(handler);
}

cfs::edac::Exception::~Exception()
{
    std::set_terminate(m_oldHandler);
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

