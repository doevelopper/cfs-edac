

#include <cfs/edacl/errors/GenericError.hpp>

using namespace cfs::edacl::errors;

log4cxx::LoggerPtr GenericError::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.GenericError"));

GenericError::GenericError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

GenericError::~GenericError()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

const char *GenericError::name() const noexcept
{
   return "CFS Generic Error";
}

std::string GenericError::message(int ev) const
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    switch ( static_cast< cfsgen_errc >( ev) )
    {
        case cfsgen_errc::NOT_INITIALIZED:
            return std::string{ "Internal Error: Null Pointer." };
        default:
            break;

    }

    return std::string(strerror(ev));
}

std::error_condition GenericError::default_error_condition( int ev) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );

     switch ( static_cast< cfsgen_errc >( ev) )
     {
         case cfsgen_errc::NOT_INITIALIZED:
            return std::error_condition{static_cast< int >(cfsgen_errc::NOT_INITIALIZED),cfs_generic_category()};
        default:
            break;
     }
    return ( std::error_condition{ ev, * this });
}

bool GenericError::equivalent( std::error_code const& code, std::uint32_t condition) const noexcept
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    return * this == code.category()
        && static_cast<std::uint32_t>( default_error_condition( code.value() ).value() ) == condition;
}

/*
std::error_condition GenericError::make_error_condition(cfsgen_errc e)
{
    return std::error_condition(static_cast<std::uint32_t>(e), cfs_generic_category());
}


std::error_code GenericError::make_error_code(cfsgen_errc e)
{
    //return std::error_code(static_cast<int>(e), GenericError);
    // return {static_cast<int>(e) , const GenericError genericErrorErrCategory {}; };
}

std::error_condition GenericError::make_error_condition(cfsgen_errc e)
{
    // std::error_condition(static_cast<int>(e), cfsgen_errc);
}
*/

