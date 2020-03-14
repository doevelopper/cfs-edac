
#include <cfs/edacl/errors/GenericErrorTest.hpp>

using namespace cfs::edacl::errors;
using namespace cfs::edacl::errors::test;

log4cxx::LoggerPtr GenericErrorTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edacl.errors.test.GenericErrorTest"));


GenericErrorTest::GenericErrorTest()
    : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

GenericErrorTest::~GenericErrorTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void GenericErrorTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new GenericError();
}

void GenericErrorTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(GenericErrorTest, testDummy)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

