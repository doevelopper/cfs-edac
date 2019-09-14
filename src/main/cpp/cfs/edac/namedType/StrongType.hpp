

#include <utility>


namespace cfs::edac::namedType
{
/*
 *      @exemple
 *          using SeatId = StrongType<int, struct SeatIdTag>;
 *      using FilmId = StrongType<int, struct FilmIdTag>;
 */
template <typename T, typename Parameter>
class StrongType
{
public:

explicit StrongType(T const& value)
		: m_value(value)
{
}

explicit StrongType(T&& value)
		: m_value(std::move(value))
{
}

T & get()
{
		return m_value;
}

T const& get() const
{
		return m_value;
}

operator T&() const
{
		return m_value;
}

operator T&()
{
		return m_value;
}

private:

T m_value;
};
}

