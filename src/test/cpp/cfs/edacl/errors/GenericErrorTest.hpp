
#ifndef CFS_EDACL_ERRORS_GENERICERRORTEST_HPP
#define CFS_EDACL_ERRORS_GENERICERRORTEST_HPP

#include <gmock/gmock.h>
#include <cfs/edacl/errors/GenericError.hpp>

namespace cfs::edacl::errors::test
{
    class GenericErrorTest : public ::testing::Test
    {
        LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            GenericErrorTest();
            GenericErrorTest(const GenericErrorTest&) = default;
            GenericErrorTest(GenericErrorTest&&) = default;
            GenericErrorTest& operator=(const GenericErrorTest&) = default;
            GenericErrorTest& operator=(GenericErrorTest&&) = default;
            virtual ~GenericErrorTest();

            void SetUp() override;
            void TearDown() override;

        protected:

            cfs::edacl::errors::GenericError *         testee;

        private:
    };
}

#endif
