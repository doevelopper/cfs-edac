

#ifndef EDAC_ISERRORACTIVE_HPP
#define EDAC_ISERRORACTIVE_HPP
//IsErrorActive<insigned int> vUint;

template <class ParamType>
class IsErrorActive
{
public:

IsErrorActive();
IsErrorActive(const IsErrorActive& orig) = default;
IsErrorActive(IsErrorActive&& orig) = default;
IsErrorActive & operator=(const IsErrorActive& orig) = default;
IsErrorActive & operator=(IsErrorActive && orig) = default;
virtual ~IsErrorActive() = default;

void value (const ParamType &value);
ParamType value () const;
bool isActive () const;
void isActive (bool value);

private:

ParamType m_value;
bool m_isValid;
};

#endif

