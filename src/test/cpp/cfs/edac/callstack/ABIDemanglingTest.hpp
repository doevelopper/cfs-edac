
#ifndef CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP
#define CFS_EDAC_CALLSTACK_ABIDEMANGLINGTEST_HPP

#include <gtest/gtest.h>

namespace cfs::edac::callstack

{
    class ABIDemanglingTest : public ::testing::Test
    {

    public:

        ABIDemanglingTest();
        ~ABIDemanglingTest();

    protected:

        void SetUp() override ;
        void TearDown() override;

    private:
    };
}
#endif
