

#ifndef CFS_EDACL_ERRORS_IOERROR_HPP
#define CFS_EDACL_ERRORS_IOERROR_HPP

#include <ios>
#include <cfs/edacl/errors/ErrorCode.hpp>

namespace cfs::edacl::errors
{
    class IOError : public std::error_category //: std::iostream_category
    {
        public:

            IOError();
            IOError(IOError const&) = delete;
            IOError(IOError&&) = delete;
            IOError& operator=(IOError const&) = delete;
            IOError& operator=(IOError&&) = delete;
            virtual ~IOError();

            virtual const char *name() const noexcept override final;
            std::string message(int ev) const override;

        private:
    };
}
#endif

