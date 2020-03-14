
#ifndef CFS_EDACL_ERRORS_SYSTEMERRORTEST_HPP
#define CFS_EDACL_ERRORS_SYSTEMERRORTEST_HPP

#include <gmock/gmock.h>
#include <cfs/edacl/errors/SystemError.hpp>

namespace cfs::edacl::errors::test
{
    class SystemErrorTest : public ::testing::Test
    {
        LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            SystemErrorTest();
            SystemErrorTest(const SystemErrorTest&) = default;
            SystemErrorTest(SystemErrorTest&&) = default;
            SystemErrorTest& operator=(const SystemErrorTest&) = default;
            SystemErrorTest& operator=(SystemErrorTest&&) = default;
            virtual ~SystemErrorTest();

            void SetUp() override;
            void TearDown() override;

        protected:

            cfs::edacl::errors::SystemError * testee;

        private:
    };
}
#endif
