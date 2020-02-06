

#include <cstddef>
#include <sstream>

#include <cfs/edac/callstack/CallStackDataStructure.hpp>

using namespace cfs::edac::callstack;

CallStackDataStructure::CallStackDataStructure()
    : m_line( 0 )
    , m_address( nullptr )
{
}

std::string CallStackDataStructure::data () const
{
    std::ostringstream os;
    os << this->m_file;

    if ( this->m_line > 0 )
    {
        os << " (" << this->m_line << ")";
    }
    else
    {
        if ( !this->m_lineContent.empty())
        {
            os << " (" << this->m_lineContent << ")";
        }
    }

    os << ": " << this->m_function;

    return os.str();
}

