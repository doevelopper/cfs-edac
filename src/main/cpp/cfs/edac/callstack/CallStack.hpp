

#ifndef CFS_EDAC_CALLSTACK_CALLSTACK_HPP
#define CFS_EDAC_CALLSTACK_CALLSTACK_HPP

#include <string>
#include <vector>
#include <sstream>
#include <inttypes.h>

namespace cfs::edac::callstack
{
    class CallStackDataStructure;

    class CallStack
    {
        public:

            CallStack();

            /*!
             * @brief Stack-trace consructor.
             * @param num_discard - number of stack entries to discard at the top.
             */
            CallStack( const size_t num_discard = 0 );

            /*!
             *  @brief Serializes the entire call-stack into a text string.
             */
            virtual ~CallStack() = default;

        private:

            //std::vector < CallStackDataStructure > m_stackData;
    };
}
#endif

