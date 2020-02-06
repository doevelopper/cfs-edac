

#include <cfs/edacl/errors/SystemError.hpp>

using namespace cfs::edacl::errors;

SystemError::SystemError()
{
}

SystemError::~SystemError()
{
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

