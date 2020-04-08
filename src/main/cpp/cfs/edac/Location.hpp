
#ifndef CFS_EDAC_LOCATION_HPP
#define CFS_EDAC_LOCATION_HPP

#include <cfs/edar/LoggingService.hpp>

#define __LOCATION__ cfs::com::Location(__FILE__, __LINE__)

namespace cfs::edac
{
class Location
{
    friend class Exception;
    LOG4CXX_DECLARE_STATIC_LOGGER

 public:
    Location(const Location&) = default;
    Location(Location&&) = default;
    Location& operator=(const Location&) = default;
    Location& operator=(Location&&) = default;
    virtual ~Location() = default;

    explicit Location(const char* filename, int line) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Location& source_location);
    const char* filename() const noexcept;
    int line() const noexcept;

protected:

private:
    Location() noexcept;

    const char* m_filename;
    int m_line;
};
    /*std::ostream& operator<<(std::ostream& os, const Location& source_location)
    {
        if ((source_location.filename() == nullptr) || (source_location.line() == 0))
        {
            return (os);
        }

        return os << source_location.filename() << ':' << source_location.line();
    }
    */
}
#endif


