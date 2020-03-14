

#ifndef CFS_EDACL_ERRORS_IOERROR_HPP
#define CFS_EDACL_ERRORS_IOERROR_HPP

#include <ios>
#include <cstring>
#include <system_error>
#include <errno.h>
#include <cfs/edar/LoggingService.hpp>

//#include <cfs/edacl/errors/ErrorCode.hpp>

namespace cfs::edacl::errors
{
    enum class cfsio_errc : std::uint32_t
    {
        ERROR_NULL_POINTER,
        ERROR_ABORTED,
        ERROR_OUT_OF_MEMORY,
        ERROR_OUT_OF_RESOURCES,
        ERROR_OPEN_FAILED,
        ERROR_TIMEOUT,
        ERROR_INVALID_FILE,
        ERROR_FILE_NOT_FOUND,
        ERROR_FILE_OPENING_FAILED,
        ERROR_FILE_READING_FAILED,
        ERROR_END_OF_FILE,
    };


    class IOError : public std::error_category //: std::iostream_category
    {
        LOG4CXX_DECLARE_STATIC_LOGGER
        public:

            IOError();
            IOError(IOError const&) = delete;
            IOError(IOError&&) = delete;
            IOError& operator=(IOError const&) = delete;
            IOError& operator=(IOError&&) = delete;
            virtual ~IOError();

            virtual const char *name() const noexcept override;
            virtual std::string message(int ev) const override;
            virtual std::error_condition default_error_condition( int ev) const noexcept;
            virtual bool equivalent( std::error_code const& code, std::uint32_t condition) const noexcept;
            virtual std::error_condition make_error_condition(cfsio_errc e) noexcept;

        private:
    };

    std::error_category const& io_category() noexcept
    {
        static IOError instanceCategory;
        return instanceCategory;
    }
}
#endif

