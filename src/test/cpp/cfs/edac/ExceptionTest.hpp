

#ifndef CFS_EDAC_EXCEPTIONTEST_HPP
#define CFS_EDAC_EXCEPTIONTEST_HPP

#include <gmock/gmock.h>

#include <cfs/edac/Exception.hpp>

namespace cfs::edac::test
{
    class ExceptionTest : public ::testing::Test
    {
        public:

            ExceptionTest();
            ~ExceptionTest();

            void Setup() override;
            void TearDown() override;

        protected:

            //   Exception * ObjectUnderTest;
            Exception * exception;
    };
}
#endif

