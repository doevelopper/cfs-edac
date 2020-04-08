

#ifndef CFS_EDAC_CALLSTACK_CALLSTACK_HPP
#define CFS_EDAC_CALLSTACK_CALLSTACK_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <inttypes.h>

#include <cfs/edar/LoggingService.hpp>

namespace cfs::edac::callstack
{
    class CallStackDataStructure;

    class CallStack
    {

        LOG4CXX_DECLARE_STATIC_LOGGER

        public:

            CallStack();
            CallStack(const CallStack&) = default;
            CallStack(CallStack&&) noexcept = default;
            CallStack& operator=(const CallStack&) = default;
            CallStack& operator=(CallStack&&) noexcept = default;

            /*!
             * @brief Stack-trace consructor.
             * @param num_discard - number of stack entries to discard at the top.
             */
            CallStack( const size_t num_discard);

            /*!
             *  @brief Serializes the entire call-stack into a text string.
             */
            virtual ~CallStack();

            const std::vector<CallStackDataStructure>& frames() const noexcept;
            friend std::ostream& operator<<(std::ostream& os, const CallStack & callStack);
        private:

            std::vector < CallStackDataStructure > m_stackFrames;
    };

    std::ostream& operator<<(std::ostream& os, const CallStackDataStructure & stackFrame)
    {
        // Format stack trace frame address
        std::ios_base::fmtflags flags = os.flags();
        //os << "0x" << std::hex << std::uppercase << std::setfill('0')
        //   << std::setw(2 * sizeof(std::uintptr_t)) << (std::uintptr_t)stackFrame.address << ": ";

        return (os);
    }
}
#endif

