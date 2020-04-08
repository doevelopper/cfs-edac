
#include <cerrno>
#include <cstring>
#include <cfs/edac/Exception.hpp>

using namespace cfs::edac;
log4cxx::LoggerPtr Exception::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.Exception"));

Exception::Exception( std::int32_t t_code )
   : std::exception()
    , m_who(std::string())
    , m_where(std::string())
    , m_reason(std::string())
    , m_oldHandler(nullptr)
    , m_stackTrace(std::string("Stack Trace"))
    , m_message(std::string("UNK"))
    , m_location() //ERROR_LOCATION
    , m_code( t_code )
{

}

Exception::Exception( const std::string & msg, const std::string & what , std::int32_t code)
   : std::exception()
   , m_who(std::string())
   , m_where(std::string())
   , m_reason(std::string())
   , m_oldHandler(nullptr)
   , m_stackTrace(std::string("Stack Trace"))
   , m_message(msg)
   , m_location() //ERROR_LOCATION
   , m_code( code )
{
	
}

Exception::Exception(std::terminate_handler handler)
    : std::exception()
    , m_who(std::string())
    , m_where(std::string())
    , m_reason(std::string())
    , m_oldHandler(std::set_terminate(handler))
    , m_stackTrace(std::string("Stack Trace"))
    , m_message(std::string(ERROR_LOCATION))
    , m_location()
    , m_code(0)
{
    m_oldHandler = std::set_terminate(handler);
}

Exception::~Exception()
{
    std::set_terminate(m_oldHandler);
}

const char* Exception::what() const noexcept 
{
	return ( m_message.c_str());
}

const Location& Exception::location() const noexcept 
{ 
	return (m_location); 
}

const std::string& Exception::message() const noexcept
{
	return (m_message);
}

std::int32_t Exception::errorCode () const
{
	return ( m_code);
}

void Exception::errorCode (const std::int32_t & ec)
{
	m_code = ec;
}

const std::string & Exception::errorDescription ()
{
	std::stringstream stream;
	// stream << "Exception: " << m_message << std::endl;
	stream << "Error: " << std::strerror(errno /*error*/) << std::endl;
	// stream << "Message: " << _system_message << std::endl;
	std::string location = m_location.filename() + m_location.line();
	
	return(stream.str());
}

const char * Exception::where () const throw ( )
{
    return ( m_location.filename() + m_location.line() );
}

std::string cfs::edac::Exception::stackTrace () const
{
    return (std::string("Stack Trace"));
}

