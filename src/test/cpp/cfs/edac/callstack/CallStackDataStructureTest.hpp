
#ifndef CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURETEST_HPP
#define CFS_EDAC_CALLSTACK_CALLSTACKDATASTRUCTURETEST_HPP

#include <gtest/gtest.h>
#include <cfs/edac/callstack/CallStackDataStructure.hpp>

namespace cfs::edac::callstack::test
{
    class CallStackDataStructureTest : public ::testing::Test
    {
	   LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            CallStackDataStructureTest();
            CallStackDataStructureTest(const CallStackDataStructureTest&) = default;
            CallStackDataStructureTest(CallStackDataStructureTest&&) = default;
            CallStackDataStructureTest& operator=(const CallStackDataStructureTest&) = default;
            CallStackDataStructureTest& operator=(CallStackDataStructureTest&&) = default;
            virtual ~CallStackDataStructureTest();

            void SetUp() override;
            void TearDown() override;

        protected:
        private:
		    CallStackDataStructure * testee;
    };

}

#endif

