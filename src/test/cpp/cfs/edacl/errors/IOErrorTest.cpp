
#include <cfs/edacl/errors/IOErrorTest.hpp>

using namespace cfs::edacl::errors;
using namespace cfs::edacl::errors::test;

log4cxx::LoggerPtr IOErrorTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.test.IOErrorTest"));


IOErrorTest::IOErrorTest()
: testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

IOErrorTest::~IOErrorTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void IOErrorTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new IOError();
}

void IOErrorTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(IOErrorTest, testDummy)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

