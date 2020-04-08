
#ifndef CFS_EDAC_LOCATIONTEST_HPP
#define CFS_EDAC_LOCATIONTEST_HPP
#include <gtest/gtest.h>
#include <cfs/edac/Location.hpp>

namespace cfs::edac::test
{
    class LocationTest : public ::testing::Test
    {
	   LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            LocationTest();
            LocationTest(const LocationTest&) = default;
            LocationTest(LocationTest&&) = default;
            LocationTest& operator=(const LocationTest&) = default;
            LocationTest& operator=(LocationTest&&) = default;
            virtual ~LocationTest();

            void SetUp() override;
            void TearDown() override;

        protected:

        private:

           cfs::edac::Location * testee;

    };
}

#endif
