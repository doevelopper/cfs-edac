

#ifndef CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURE_HPP
#define CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURE_HPP

#include <string>
#include <cfs/edar/LoggingService.hpp>
namespace cfs::edac::callstack
{
    class CallStackDataStructure
    {
        LOG4CXX_DECLARE_STATIC_LOGGER

        //! Stack trace frame
        struct Frame
        {
            void* address;          //!< Frame address
            std::string module;     //!< Frame module
            std::string function;   //!< Frame function
            std::string filename;   //!< Frame file name
            int line;               //!< Frame line number

            //! Get string from the current stack trace frame
            std::string surrentStackFrame() const
            {
                std::stringstream ss;
                ss << *this;
                return ss.str();
            }

            //! Output stack trace frame into the given output stream
            friend std::ostream& operator<<(std::ostream& os, const Frame& frame);
        };

        public:

            CallStackDataStructure();
            CallStackDataStructure(const CallStackDataStructure&) = default;
            CallStackDataStructure(CallStackDataStructure&&) = default;
            CallStackDataStructure& operator=(const CallStackDataStructure&) = default;
            CallStackDataStructure& operator=(CallStackDataStructure&&) = default;
            virtual ~CallStackDataStructure();

            std::string data () const;

        private:

            std::string m_file;         // filename
            size_t      m_line;         // line number
            std::string m_lineContent;  // line number string (not always set)
            std::string m_function;     // name of function or method
            void *      m_address;      // memory address of stack pointer (raw)
            void *      m_address2;     // memory address of stack pointer (from dladdr; data segment offset subtracted)
    };
}

std::ostream & operator << ( std::ostream & out, const cfs::edac::callstack::CallStackDataStructure & ent );

#endif

