
#include <cfs/edac/callstack/CallStackDataStructureTest.hpp>

using namespace cfs::edac::callstack;
using namespace cfs::edac::callstack::test;

log4cxx::LoggerPtr CallStackDataStructureTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.callstack.test.CallStackDataStructureTest"));

CallStackDataStructureTest::CallStackDataStructureTest()
  : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

CallStackDataStructureTest::~CallStackDataStructureTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void CallStackDataStructureTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new CallStackDataStructure();
}

void CallStackDataStructureTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(CallStackDataStructureTest, test_Simple)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}


