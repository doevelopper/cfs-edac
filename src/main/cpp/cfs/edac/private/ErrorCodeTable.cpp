
#include <cfs/edac/private/ErrorCodeTable.hpp>

cfs::edac::ErrorCodeTable::ErrorCodeTable()
{

}

cfs::edac::ErrorCodeTable::~ErrorCodeTable()
{

}

void cfs::edac::ErrorCodeTable::addCode(int code, const char *name, const char *description) 
{
    (*this)[code] = std::make_pair(name, description);
}


