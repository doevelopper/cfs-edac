

#include <typeindex>
#include <cfs/edac/callstack/ABIDemangling.hpp>

using namespace cfs::edac::callstack;
log4cxx::LoggerPtr ABIDemangling::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.callstack.ABIDemangling"));

ABIDemangling::ABIDemangling()
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
}

ABIDemangling::~ABIDemangling()
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
}

template < typename T >
std::string ABIDemangling::gccDemangle ( T & e )
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    int status;
    std::unique_ptr < char > realname;
    const std::type_info & ti = typeid( e );
    realname.reset( abi::__cxa_demangle( ti.name(), nullptr, nullptr, &status ));

    // assert(status == 0);
    return ( std::string( realname.get()));
}

const char* ABIDemangling::cxaDemangle(const std::type_info &typeInfo)
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    if (!typeInfo.name())
    {
        LOG4CXX_ERROR(logger , __LOG4CXX_FUNC__);
        return("NULL");
    }
    static std::map<std::type_index, std::unique_ptr<char, void (*)(void *)> > cache;
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
        LOG4CXX_ERROR(logger,"Demangle failed.");
        //throw std::runtime_error("Demangle failed.");
    }

    std::tie(iter, std::ignore) = cache.emplace(typeIndex, std::move(result));

    return (iter->second.get());
}

template < class T >
std::string ABIDemangling::type ( const T & t )
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    return ( demangle( typeid( t ).name()));
}

std::string ABIDemangling::demangle ( const char * name)
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    int status;
    std::string retVal;

    std::unique_ptr < char, void ( * )(void *) > res  {
        abi::__cxa_demangle( name, nullptr, nullptr, &status ), std::free
    };

    switch ( status )
    {
    case 0:

        return (name);

    case -1:
        retVal = "A memory allocation failure occurred.";
        break;
    case -2:
        retVal = "Invalid name given. Not a valid name under the GCC C++ ABI mangling rules.";
        break;
    case -3:
        retVal = "internal error: __cxa_demangle: invalid argument";
        break;
    default:
        retVal = "unknown error occured";
        break;
    }

    LOG4CXX_DEBUG(logger , "Demangle status: " << status << " Desc: " << retVal);
    return (( status == 0 ) ? res.get() : retVal /*name*/ );
}

std::string ABIDemangling::demangle ( const std::type_info & typeInfo )
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    return ( demangle( typeInfo.name()));
}

size_t ABIDemangling::demangle ( const std::type_info & typeInfo, char * buf, size_t bufSize)
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    // return (demangle(typeInfo.name(), buf, bufSize));
    return 42;  // ;)
}

void ABIDemangling::printExceptionStack ( const std::exception & e, std::ostream & output)
{
    LOG4CXX_TRACE(logger , __LOG4CXX_FUNC__);
    output << "Issue on " << abi::__cxa_demangle( typeid( e ).name(), nullptr, nullptr, nullptr ) << ": " << e.what() <<
        std::endl;
}

