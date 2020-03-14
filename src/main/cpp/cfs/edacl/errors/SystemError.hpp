

#ifndef CFS_EDACL_ERRORS_SYSTEMERROR_HPP
#define CFS_EDACL_ERRORS_SYSTEMERROR_HPP

#include <ios>
#include <cstring>
#include <system_error>
#include <cerrno>
#include <cfs/edar/LoggingService.hpp>

namespace cfs::edacl::errors
{
    enum class cfssy_errc : std::uint32_t
    {
        ERROR_PARAMETER_OUT_OF_RANGE,
        ERROR_OPERATING_SYSTEM,
        ERROR_SOFT_FATAL,
        ERROR_SOFT_RECOVERABLE,
        ERROR_SERVICE_CLOSING,
        ERROR_ILLEGAL_PARAMETER,
        ERROR_WRITE_FAILED,
        ERROR_READ_FAILED,
    };
    /*!
     * @brief return std::system_category() for errors originating from the OS,
     *        or a reference to an implementation-defined error_category object
     *        for errors originating elsewhere.
     */
    class SystemError : public std::error_category
    {
        LOG4CXX_DECLARE_STATIC_LOGGER
        public:

            SystemError();
            SystemError(SystemError const&) = delete;
            SystemError(SystemError&&) = delete;
            SystemError& operator=(SystemError const&) = delete;
            SystemError& operator=(SystemError&&) = delete;
            SystemError(const std::error_code code) noexcept;
            SystemError(const std::error_code code, const char * const what) noexcept;
            SystemError(const int code, const std::error_category & category) noexcept;
            SystemError(const int code) noexcept;
            SystemError(const int code, const std::error_category & category, const char * const what) noexcept;
            virtual ~SystemError();

            virtual const char* name() const noexcept override;
            virtual std::string message(int ev) const override;
            virtual bool equivalent(const std::error_code& code, std::uint32_t condition) const noexcept;
            virtual std::error_condition default_error_condition(int ev) const noexcept override;

        private:
    };

    std::error_category const& cfssys_category() noexcept
    {
        static SystemError cat;
        return cat;
    }
}
#endif

