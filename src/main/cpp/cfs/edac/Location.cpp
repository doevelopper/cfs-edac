
#include <cfs/edac/Location.hpp>

using namespace cfs::edac;

log4cxx::LoggerPtr Location::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.Location"));


Location::Location(const char* file, int line) noexcept
: m_filename(file)
, m_line(line)
{

}

Location::Location() noexcept
 : Location(nullptr, 0)
{

}

const char* Location::filename() const noexcept
{
    return (m_filename);
}

int Location::line() const noexcept
{
    return (m_line);
}

