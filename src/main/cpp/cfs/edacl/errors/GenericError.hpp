

#ifndef CFS_EDACL_ERRORS_GENERICERROR_HPP
#define CFS_EDACL_ERRORS_GENERICERROR_HPP

#include <cfs/edacl/errors/ErrorCode.hpp>
#include <cerrno>
#include <cstdint>

namespace cfs::edacl::errors
{
    class GenericError : public std::error_category
    {
        enum class GenericErrorErrorCodes : std::uint32_t
        {
            NOT_INITIALIZED = 1,
            ALREADY_INITIALIZED,
            INTERNAL_ERROR,
            REQUEST_ERROR
        };

        public:

            GenericError();
            GenericError(GenericError const&) = delete;
            GenericError(GenericError&&) = delete;
            GenericError& operator=(GenericError const&) = delete;
            GenericError& operator=(GenericError&&) = delete;
            virtual ~GenericError();

            virtual const char *name() const noexcept override final
            {
                return "EDAC Generic Error";
            }

            /*
               virtual const char* name() const throw() override
               {
                return "EDAC Generic Error";
               }*/

            virtual std::error_condition default_error_condition(int ev) const throw() override
            {
                return std::error_condition(ev, *this);
            }

            bool equivalent(int code, const std::error_condition &condition) const noexcept override final
            {
                return default_error_condition(code) == condition;
            }

            /*
               bool equivalent(const std::error_code &code, int condition) const noexcept override final
               {
                return *this == code.category() && code.value() == condition;
               }*/
            bool equivalent() const noexcept
            {
                return true;//category().default_error_condition(value());
            }

            virtual bool equivalent(const std::error_code& errorCode, int condition) const throw() override
            {
                GenericErrorErrorCodes code = static_cast<GenericErrorErrorCodes>(condition);
                switch(code)
                {
                default:
                    break;
                }

                return true;// ???
            }

            int value() const noexcept
            {
                return (evalue);
            }

            const std::error_category& category() const noexcept
            {
                return (*ecat);
            }

            std::string message() const
            {
                return category().message(value());
            }

            virtual std::string message(int ev) const noexcept override
            {
                GenericErrorErrorCodes code = static_cast<GenericErrorErrorCodes>(ev);
                switch (code /*ev*/)
                {
                //case static_cast<int>(GenericErrorErrorCodes::NOT_INITIALIZED)
                case GenericErrorErrorCodes::NOT_INITIALIZED
                    : return "Object was not initialized";

                    break;
                default:

                    return "Unknown error";

                    break;
                }
            }

        private:

            std::error_code make_error_code( GenericErrorErrorCodes e);
            std::error_condition make_error_condition(GenericErrorErrorCodes e);
            std::error_condition        econd;
            const std::error_category * ecat;
            int                         evalue;
    };
}
#endif

