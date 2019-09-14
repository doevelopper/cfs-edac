

#ifndef CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURE_HPP
#define CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURE_HPP

#include <string>

namespace cfs::edac::callstack
{

    class CallStackDataStructure
    {
        public:

            CallStackDataStructure();
            virtual ~CallStackDataStructure() = default;

            std::string
            data () const;

        private:

            std::string m_file;         // filename
            size_t m_line;              // line number
            std::string m_lineContent;  // line number string (not always set)
            std::string m_function;     // name of function or method
            void * m_address;           // memory address of stack pointer (raw)
            void * m_address2;          // memory address of stack pointer (from dladdr; data segment offset subtracted)
    };

}

std::ostream & operator << ( std::ostream & out, const CallStackDataStructure & ent );

#endif

