

#include <cfs/edacl/errors/IOError.hpp>

using namespace cfs::edacl::errors;

log4cxx::LoggerPtr IOError::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.IOError"));

IOError::IOError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

IOError::~IOError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

const char *IOError::name() const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    return ("IO ");
}

std::string IOError::message(int ev) const
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    switch ( static_cast< cfsio_errc >( ev) )
    {
        case cfsio_errc::ERROR_NULL_POINTER:
            return std::string{ "Internal Error: Null Pointer." };
        default:
            break;

    }

    return std::string(strerror(ev));
}

std::error_condition IOError::default_error_condition( int ev) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );

     switch ( static_cast< cfsio_errc >( ev) )
     {
         case cfsio_errc::ERROR_NULL_POINTER:
            return std::error_condition{static_cast< int >(cfsio_errc::ERROR_NULL_POINTER),io_category()};
        default:
            break;
     }
    return ( std::error_condition{ ev, * this });
}

bool IOError::equivalent( std::error_code const& code, std::uint32_t condition) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    return * this == code.category()
        && static_cast<std::uint32_t>( default_error_condition( code.value() ).value() ) == condition;
}

std::error_condition IOError::make_error_condition(cfsio_errc e)
{
    return std::error_condition(static_cast<std::uint32_t>(e), io_category());
}

