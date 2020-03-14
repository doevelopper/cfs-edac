

#ifndef CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP
#define CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP

#include <gtest/gtest.h>
#include <cfs/edac/callstack/ABIDemangling.hpp>

namespace cfs::edac::callstack::test

{

    class ABIDemanglingTest : public ::testing::Test
    {
        LOG4CXX_DECLARE_STATIC_LOGGER
        public:

            ABIDemanglingTest();
            ~ABIDemanglingTest();

        protected:

            void SetUp() override;
            void TearDown() override;

            cfs::edac::callstack::ABIDemangling*         testee;
        private:

    };

}
#endif

