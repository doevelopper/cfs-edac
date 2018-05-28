#ifndef CFS_EDAC_PRIVATE_ERRORCODETABLE_HPP
#define CFS_EDAC_PRIVATE_ERRORCODETABLE_HPP

#include <exception>
#include <map>

namespace cfs::edac
{
    class ErrorCodeTable : public std::map<int, std::pair<const char*, const char*> >
    {

    public:

        ErrorCodeTable();
        ErrorCodeTable(const ErrorCodeTable & orig) = delete;
        ErrorCodeTable(ErrorCodeTable && orig) = delete;
        ErrorCodeTable & operator=(const ErrorCodeTable & orig) = delete;
        ErrorCodeTable & operator=(ErrorCodeTable && orig) = delete;
        virtual ~ErrorCodeTable();

        void addCode(int code, const char *name, const char *description);
        void addCode(std::uint32_t ode, std::string & name, std::string & description);

    private:

    };
}
#endif
