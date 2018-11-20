

#ifndef CFS_EDAC_EXCEPTIONTEST_HPP
#define CFS_EDAC_EXCEPTIONTEST_HPP

#include <gmock/gmock.h>

#include <cfs/edac/Exception.hpp>

namespace cfs::edac::test: public ::testing::Test
{
    class ExceptionTest
    {
        public:

            ExceptionTest();
            ~ExceptionTest();

            void Setup() override;
            void TearDown() override;

        protected:

            //   Exception * ObjectUnderTest;
            static log4cxx::LoggerPtr logger;
            Exception * exception;
    };
}
#endif

