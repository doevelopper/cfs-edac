

#include <edac/exceptions/ErrnoMapper.hpp>

ErrnoMapper::ErrnoMapper()
{
}

ErrnoMapper::~ErrnoMapper()
{
}

ErrnoMapper::ErrnoMapper(const std::error_code code) noexcept
	: std::system_error{code}
{
}

ErrnoMapper::ErrnoMapper(const std::error_code code,
                         const char * const what) noexcept
	: std::system_error{code, what}
{
}

ErrnoMapper::ErrnoMapper(const int code) noexcept
	: std::system_error{code, std::generic_category()}
{
}

ErrnoMapper::ErrnoMapper(const int code,
                         const std::error_category & category) noexcept
	: std::system_error{code, category}
{
}

ErrnoMapper::ErrnoMapper(const int code,
                         const std::error_category & category,
                         const char * const what) noexcept
	: std::system_error{code, category, what}
{
}

