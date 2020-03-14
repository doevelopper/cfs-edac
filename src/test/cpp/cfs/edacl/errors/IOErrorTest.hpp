#ifndef CFS_EDACL_ERRORS_IOERRORTEST_HPP
#define CFS_EDACL_ERRORS_IOERRORTEST_HPP

#include <gmock/gmock.h>
#include <cfs/edacl/errors/IOError.hpp>

namespace cfs::edacl::errors::test
{
    class IOErrorTest : public ::testing::Test
    {
        LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            IOErrorTest();
            IOErrorTest(const IOErrorTest&) = default;
            IOErrorTest(IOErrorTest&&) = default;
            IOErrorTest& operator=(const IOErrorTest&) = default;
            IOErrorTest& operator=(IOErrorTest&&) = default;
            virtual ~IOErrorTest();

            void SetUp() override;
            void TearDown() override;

        protected:

            cfs::edacl::errors::IOError *         testee;

        private:
    };
}
#endif
