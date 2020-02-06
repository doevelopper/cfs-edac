

#ifndef CFS_EDACL_ERRORS_SYSTEMERROR_HPP
#define CFS_EDACL_ERRORS_SYSTEMERROR_HPP


#include <system_error>

namespace cfs::edacl::errors
{
    /*!
     * @brief return std::system_category() for errors originating from the OS,
     *        or a reference to an implementation-defined error_category object
     *        for errors originating elsewhere.
     */
    class SystemError : public std::error_category
    {
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

            const char* name() const noexcept override;
            std::string message(int ev) const override;
            bool equivalent(const std::error_code& code, int condition) const noexcept override;
            std::error_condition default_error_condition(int ev) const noexcept override;

        private:
    };
}
#endif

