

#ifndef EDAC_LOWLEVELAPIERROR_HPP
#define EDAC_LOWLEVELAPIERROR_HPP
#include <edac/errors/ErrorCode.hpp>
class LowLevelApiError : public std::error_category
{
public:

LowLevelApiError();
LowLevelApiError(const LowLevelApiError& orig) = default;
LowLevelApiError(LowLevelApiError&& orig) = default;
LowLevelApiError & operator=(const LowLevelApiError& orig) = default;
LowLevelApiError & operator=(LowLevelApiError && orig) = default;
virtual ~LowLevelApiError() = default;
virtual const char *name() const noexcept override final;
std::string message(int ev) const override;

private:
};

#endif

