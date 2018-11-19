

#include <cfs/edac/private/ErrorCodeTable.hpp>

cfs::edac::ErrorCodeTable::ErrorCodeTable()
{
}

cfs::edac::ErrorCodeTable::~ErrorCodeTable()
{
}

/*
   ErrorCodeTable::ErrorCodeTable(const std::error_code code) noexcept
    : std::system_error{code}
   {
   }

   ErrorCodeTable::ErrorCodeTable(const std::error_code code,
                             const char * const what) noexcept
   : std::system_error{code, what}
   {
   }

   ErrorCodeTable::ErrorCodeTable(const int code) noexcept
   : std::system_error{code, std::generic_category()}
   {
   }

   ErrorCodeTable::ErrorCodeTable(const int code,
                             const std::error_category & category) noexcept
   : std::system_error{code, category}
   {
   }

   ErrorCodeTable::ErrorCodeTable(const int code,
                             const std::error_category & category,
                                    const char * const what) noexcept
   : std::system_error{code, category, what}
   {
   }

   void cfs::edac::ErrorCodeTable::addCode(int code, const char *name, const char *description)
   {
    (*this)[code] = std::make_pair(name, description);
   }
 */

