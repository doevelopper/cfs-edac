
#include <cfs/edar/EventSystemTest.hpp>

using namespace cfs::edar;
using namespace cfs::edar::test;

log4cxx::LoggerPtr EventSystemTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edar.test.EventSystemTest"));

EventSystemTest::EventSystemTest()
    : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

EventSystemTest::~EventSystemTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void EventSystemTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new EventSystem();
}

void EventSystemTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(EventSystemTest, test_Simple)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

