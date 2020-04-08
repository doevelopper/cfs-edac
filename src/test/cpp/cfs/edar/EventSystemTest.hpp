
#ifndef CFS_EDAR_EVETSYSTEMTEST_HPP
#define CFS_EDAR_EVETSYSTEMTEST_HPP

#include <gtest/gtest.h>
#include <cfs/edar/EventSystem.hpp>

namespace cfs::edar::test
{
    class EventSystemTest : public ::testing::Test
    {
	   LOG4CXX_DECLARE_STATIC_TEST_LOGGER
        public:

            EventSystemTest();
            EventSystemTest(const EventSystemTest&) = default;
            EventSystemTest(EventSystemTest&&) = default;
            EventSystemTest& operator=(const EventSystemTest&) = default;
            EventSystemTest& operator=(EventSystemTest&&) = default;
            virtual ~EventSystemTest();

            void SetUp() override;
            void TearDown() override;

        protected:
        private:

            cfs::edar::EventSystem * testee;
    };
}

#endif
