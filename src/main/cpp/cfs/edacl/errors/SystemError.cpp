

#include <cfs/edacl/errors/SystemError.hpp>

using namespace cfs::edacl::errors;

log4cxx::LoggerPtr SystemError::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.SystemError"));

SystemError::SystemError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

SystemError::~SystemError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

const char *SystemError::name() const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    return ("CFS System Error ");
}

std::string SystemError::message(int ev) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    switch ( static_cast< cfssy_errc >( ev) )
    {
        case cfssy_errc::ERROR_SOFT_RECOVERABLE:
            return std::string{ "Internal Error: Null Pointer." };
        default:
            break;

    }

    return std::string(strerror(ev));
}

std::error_condition SystemError::default_error_condition( int ev) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );

     switch ( static_cast< cfssy_errc >( ev) )
     {
         case cfssy_errc::ERROR_SOFT_RECOVERABLE:
            return std::error_condition{static_cast< int >(cfssy_errc::ERROR_SOFT_RECOVERABLE),cfssys_category()};
        default:
            break;
     }
    return ( std::error_condition{ ev, * this });
}

bool SystemError::equivalent( std::error_code const& code, std::uint32_t condition) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    return * this == code.category()
        && static_cast<std::uint32_t>( default_error_condition( code.value() ).value() ) == condition;
}

/*
   SystemError::SystemError(const std::error_code code) noexcept
    : std::system_error{code}
   {
   }

   SystemError::SystemError(const std::error_code code,
                         const char * const what) noexcept
    : std::system_error{code, what}
   {
   }

   SystemError::SystemError(const int code) noexcept
    : std::system_error{code, std::generic_category()}
   {
   }

   SystemError::SystemError(const int code,
                         const std::error_category & category) noexcept
    : std::system_error{code, category}
   {
   }

   SystemError::SystemError(const int code,
                         const std::error_category & category,
                         const char * const what) noexcept
    : std::system_error{code, category, what}
   {
   }
 */

