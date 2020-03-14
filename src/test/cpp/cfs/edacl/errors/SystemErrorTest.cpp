
#include <cfs/edacl/errors/SystemErrorTest.hpp>

using namespace cfs::edacl::errors;
using namespace cfs::edacl::errors::test;

log4cxx::LoggerPtr SystemErrorTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.test.SystemErrorTest"));


SystemErrorTest::SystemErrorTest()
   : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

SystemErrorTest::~SystemErrorTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void SystemErrorTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
   testee = new SystemError();
}

void SystemErrorTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
   delete testee;
}

TEST_F(SystemErrorTest, testDummy)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

