

#ifndef EDAC_ERRORCODE_HPP
#define EDAC_ERRORCODE_HPP
#include <edac/errors/private/ErrorCodePrivate.hpp>

/*!
 * @brief Holds a platform dependent error code

 */
class ErrorCode
{
public:

ErrorCode();
ErrorCode(const ErrorCode& orig) = delete;
ErrorCode(ErrorCode&& orig) = delete;
ErrorCode & operator=(const ErrorCode& orig) = delete;
ErrorCode & operator=(ErrorCode && orig) = delete;
virtual ~ErrorCode();
void check(std::error_code ec);

protected:

const std::error_category &future_category() noexcept;
const std::error_category &generic_category() noexcept;
const std::error_category &io_category() noexcept;
const std::error_category &api_category() noexcept;
const std::error_category &sys_category() noexcept;

private:
};

#endif

