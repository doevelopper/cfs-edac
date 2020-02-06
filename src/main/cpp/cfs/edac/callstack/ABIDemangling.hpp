

#ifndef CFS_EDAC_CALLSTACK_ABIDEMANGLING_HPP
#define CFS_EDAC_CALLSTACK_ABIDEMANGLING_HPP

#include <algorithm>
#include <cassert>
#include <cxxabi.h>
#include <execinfo.h>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <typeinfo>

namespace cfs::edac::callstack
{
    class ABIDemangling
    {
        public:

            ABIDemangling();
            virtual ~ABIDemangling();

            bool demangle ( std::string s, std::string & res);
            /* Use __cxa_demangle to demangle a mangled name.
             * Since abi::__cxa_demangle returns a `char *` to a
             * heap-allocated string, we cache based on the `type_index`.
             */
            const char * cxaDemangle(const std::type_info &type_info);
            template <typename T>
            const char * cxaDemangle()
            {
                static const char *result = cxaDemangle(typeid(T));

                return result;
            }

            template < typename T >
            std::string gccDemangle ( T & e );
            std::string demangle ( const char * name /*, std::string & retVal*/ );
            template < class T >
            std::string type ( const T & t );
            std::string demangle ( const std::type_info & type );
            std::size_t demangle ( const std::type_info & type, char * buf, size_t bufSize);
            void printExceptionStack (const std::exception & e, std::ostream & output = std::cerr );

        private:
    };
}
#endif

