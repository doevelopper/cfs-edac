

#include <cfs/edacl/errors/GenericError.hpp>

using namespace cfs::edacl::errors;

GenericError::GenericError()
{
}

GenericError::~GenericError()
{
}

/*
   std::error_code GenericError::make_error_code(GenericError::GenericErrorErrorCodes e)
   {
    //return std::error_code(static_cast<int>(e), GenericError);
    // return {static_cast<int>(e) , const GenericError genericErrorErrCategory {}; };
   }

   std::error_condition GenericError::make_error_condition(GenericErrorErrorCodes e)
   {
    // std::error_condition(static_cast<int>(e),
    //GenericErrorErrorCodes);
   }
 */

