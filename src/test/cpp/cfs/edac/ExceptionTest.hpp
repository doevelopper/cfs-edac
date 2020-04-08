

#ifndef CFS_EDAC_EXCEPTIONTEST_HPP
#define CFS_EDAC_EXCEPTIONTEST_HPP

#include <gtest/gtest.h>
#include <cfs/edac/Exception.hpp>

namespace cfs::edac::test
{

    class ExceptionTest : public ::testing::Test
    {

        LOG4CXX_DECLARE_STATIC_TEST_LOGGER

        public:
            ExceptionTest();
            ExceptionTest(const ExceptionTest&) = default;
            ExceptionTest(ExceptionTest&&) = default;
            ExceptionTest& operator=(const ExceptionTest&) = default;
            ExceptionTest& operator=(ExceptionTest&&) = default;
            virtual ~ExceptionTest();

            void SetUp() override;
            void TearDown() override;

        protected:

            cfs::edac::Exception * testee;
    };

}
#endif

