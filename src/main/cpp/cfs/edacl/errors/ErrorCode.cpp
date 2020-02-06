

#include <cfs/edacl/errors/ErrorCode.hpp>
#include <cfs/edacl/errors/FutureError.hpp>
#include <cfs/edacl/errors/GenericError.hpp>
#include <cfs/edacl/errors/IOError.hpp>
#include <cfs/edacl/errors/LowLevelApiError.hpp>
#include <cfs/edacl/errors/SystemError.hpp>

using namespace cfs::edacl::errors;

ErrorCode::ErrorCode()
{
}

ErrorCode::~ErrorCode()
{
}

void ErrorCode::check(std::error_code ec)
{
    /*
       ec = std::error_code(errno, std::system_category());
       if(ec == std::errc::no_such_file_or_directory)
       {
        std::error_condition ec2(ec.default_error_condition());
       }
     */
}

const std::error_category & ErrorCode::future_category() noexcept
{
    static const FutureError impl{};

    return impl;
}

const std::error_category & ErrorCode::generic_category() noexcept
{
    static const GenericError impl{};

    return impl;
}

const std::error_category & ErrorCode::io_category() noexcept
{
    static const IOError impl{};

    return impl;
}

const std::error_category & ErrorCode::api_category() noexcept
{
    static const LowLevelApiError impl{};

    return impl;
}

const std::error_category & ErrorCode::sys_category() noexcept
{
    static const SystemError impl{};

    return impl;
}

