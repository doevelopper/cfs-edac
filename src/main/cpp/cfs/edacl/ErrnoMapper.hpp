

#ifndef ERRNOMAPPER_HPP
#define ERRNOMAPPER_HPP
#include <system_error>
class ErrnoMapper : public std::system_error
{
public:

ErrnoMapper();
ErrnoMapper(const ErrnoMapper& orig) = delete;
ErrnoMapper(ErrnoMapper&& orig) = delete;
ErrnoMapper & operator=(const ErrnoMapper& orig) = delete;
ErrnoMapper & operator=(ErrnoMapper && orig) = delete;
virtual ~ErrnoMapper();

ErrnoMapper(const std::error_code code) noexcept;
ErrnoMapper(const std::error_code code, const char * const what) noexcept;
ErrnoMapper(const int code, const std::error_category & category) noexcept;
ErrnoMapper(const int code) noexcept;
ErrnoMapper(const int code, const std::error_category & category, const char * const what) noexcept;

private:
};

#endif

