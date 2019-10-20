

#ifndef CFS_EDAC_NAMEDTYPE_CRTP_HPP
#define CFS_EDAC_NAMEDTYPE_CRTP_HPP

namespace cfs::edac::namedType
{
template <typename T, template<typename> class crtpType>
struct Crtp
{
	T& underlying()
	{
		return static_cast<T&>(*this);
	}

	T const& underlying() const
	{
		return static_cast<T const&>(*this);
	}
};
}

#endif

