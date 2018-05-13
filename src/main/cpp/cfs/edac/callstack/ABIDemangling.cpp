
#include <cfs/edac/callstack/ABIDemangling.hpp>

cfs::edac::ABIDemangling::ABIDemangling()
{

}

cfs::edac::ABIDemangling::~ABIDemangling()
{
}

template < typename T >
std::string cfs::edac::ABIDemangling::gccDemangle ( T & e )
{
    int status;
    std::unique_ptr < char > realname;
    const std::type_info & ti = typeid( e );
    realname.reset( abi::__cxa_demangle( ti.name(), 0, 0, &status ));
    // assert(status == 0);
    return ( std::string( realname.get()));
}

const char*  cfs::edac::ABIDemangling::cxaDemangle(const std::type_info &typeInfo)
{
    //LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    static std::map<std::type_index, std::unique_ptr<char, void (*)(void *)>> cache;
    auto typeIndex = std::type_index(typeInfo);
    auto iter = cache.find(typeIndex);

    if (iter != std::end(cache)) 
    {
        return iter->second.get();
    }
    
    int status;

    std::unique_ptr<char, void (*)(void *)> result(
        abi::__cxa_demangle(typeInfo.name(), nullptr, nullptr, &status),
        std::free
    );

    if (status != 0) 
    {
        //LOG4CXX_ERROR(logger,"Demangle failed.");
        //throw std::runtime_error("Demangle failed.");
    }

    std::tie(iter, std::ignore) = cache.emplace(typeIndex, std::move(result));

    return (iter->second.get());
}

template < class T >
std::string cfs::edac::ABIDemangling::type ( const T & t )
{
    return ( demangle( typeid( t ).name()));
}

std::string cfs::edac::ABIDemangling::demangle ( const char * name /*, std::string& retVal*/ )
{
    int status;
    std::string retVal;

    std::unique_ptr < char, void ( * )(void *) > res  {
        abi::__cxa_demangle( name, nullptr, nullptr, &status ), std::free
    };

    switch ( status )
    {
        case -1:
            retVal = "memory allocation error";
            break;
        case -2:
            retVal = "invalid name given";
            break;
        case -3:
            retVal = "internal error: __cxa_demangle: invalid argument";
            break;
        default:
            retVal = "unknown error occured";
            break;
    }

    return (( status == 0 ) ? res.get() : retVal /*name*/ );
}

std::string
cfs::edac::ABIDemangling::demangle ( const std::type_info & type )
{
    return ( demangle( type.name()));
}

size_t
cfs::edac::ABIDemangling::demangle ( const std::type_info & type, char * buf, size_t bufSize)
{
    // return (demangle(type.name(), buf, bufSize));
}

void
cfs::edac::ABIDemangling::printExceptionStack ( const std::exception & e, std::ostream & output)
{
    output << "Issue on " << abi::__cxa_demangle( typeid( e ).name(), nullptr, nullptr, nullptr ) << ": " << e.what() << std::endl;
}
