
#include <cfs/edac/LocationTest.hpp>

using namespace cfs::edac;
using namespace cfs::edac::test;

log4cxx::LoggerPtr LocationTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.LocationTest"));


LocationTest::LocationTest()
    : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

LocationTest::~LocationTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void LocationTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new Location(nullptr, 0);
}

void LocationTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(LocationTest, test_Simple)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}
