

#include <edac/errors/FutureError.hpp>

FutureError::FutureError()
{
}

FutureError::~FutureError()
{
}

const char * FutureError::name() const noexcept
{
	return "Future Error Category";
}

std::error_condition FutureError::default_error_condition(int code) const noexcept
{
	//const detail::field *f = detail::find_ntstatus(code);
	//if(f == nullptr || f->posix == 0)
	//return std::error_condition(code, *this);
	//return std::error_condition(f->posix, std::generic_category());
}

/*
   const char * FutureError::name() const noexcept
   {
    return "asynchronous operations error";
   }

   std::string FutureError::reason(int code)
   {
    switch (code)
    {
        case 429:
            return "Too Many Requests";
        default:
            return std::string();
    }
   }

   std::string FutureError::reason(edac::errc::edacErrc code)
   {
    return reason(static_cast<std::uint32_t>(code));
   }

   std::string FutureError::message(int ev) const
   {
    static const std::string unknownErr("Unknown error");
    const char *c_str = "";
    return c_str ? std::string(c_str) : unknownErr;
    //return "future_category(static_cast<ErrorCode>(code))";
   }
 */
/*
   std::error_condition FutureError::default_error_condition(int ev) const
   {
   // if(ev < ::edac::errc::edacErrc::TBL_NOT_IMPLEMENTED)
    //{
      //  ; //return make_error_condition(static_cast<errc_t>(ev));
    //}
    //return system_category().default_error_condition(ev);
   }
 */

