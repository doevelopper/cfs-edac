

#ifndef CFS_EDACL_ERRORS_FUTUREERROR_HPP
#define CFS_EDACL_ERRORS_FUTUREERROR_HPP

#include <future>
#include <cfs/edacl/errors/ErrorCode.hpp>

namespace cfs::edacl::errors
{
    class FutureError : public std::error_category //public std::future_category //
    {
        public:

            FutureError();
            FutureError(FutureError const&) = delete;
            FutureError(FutureError&&) = delete;
            FutureError& operator=(FutureError const&) = delete;
            FutureError& operator=(FutureError&&) = delete;
            virtual ~FutureError();
            virtual const char *name() const noexcept override final;
            virtual std::string message(int ev) const override;
            // Map where possible to std::errc (generic_category)
            virtual std::error_condition default_error_condition(int code) const noexcept override final;
        //std::string reason(int code);
        //std::string reason(edac::errc::edacErrc code);
        // virtual std::error_condition default_error_condition(int ev) const override;

        private:
    };
}
#endif

