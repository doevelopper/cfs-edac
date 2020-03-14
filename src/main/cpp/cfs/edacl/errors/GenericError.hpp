

#ifndef CFS_EDACL_ERRORS_GENERICERROR_HPP
#define CFS_EDACL_ERRORS_GENERICERROR_HPP

//#include <cfs/edacl/errors/ErrorCode.hpp>
#include <cerrno>
#include <cstdint>
#include <ios>
#include <cstring>
#include <system_error>
#include <cfs/edar/LoggingService.hpp>
namespace cfs::edacl::errors
{
	enum class cfsgen_errc : std::uint32_t
	{
		NOT_INITIALIZED = 1,
		ALREADY_INITIALIZED,
		INTERNAL_ERROR,
		REQUEST_ERROR
	};

    class GenericError : public std::error_category
    {
		LOG4CXX_DECLARE_STATIC_LOGGER

        public:

            GenericError();
            GenericError(GenericError const&) = delete;
            GenericError(GenericError&&) = delete;
            GenericError& operator=(GenericError const&) = delete;
            GenericError& operator=(GenericError&&) = delete;
            virtual ~GenericError();

            virtual const char *name() const noexcept override;
            virtual std::string message(int ev) const override;
            virtual std::error_condition default_error_condition( int ev) const noexcept;
            virtual bool equivalent( std::error_code const& code, std::uint32_t condition) const noexcept;
        private:

    };
    std::error_category const& cfs_generic_category() noexcept
    {
        static GenericError instanceCategory;
        return instanceCategory;
    }
}
#endif

