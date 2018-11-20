

#include <cfs/edac/ExceptionTest.hpp>

using cfs::edac::test::ExceptionTest;

log4cxx::LoggerPtr ExceptionsTest::logger =
    log4cxx::Logger::getLogger(std::string("cfs.edac.ExceptionsTest"));

ExceptionTest::ExceptionTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

ExceptionTest::~ExceptionTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

ExceptionTest::Setup()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

ExceptionTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

TEST_F(ExceptionTest, testExceptionConstruction)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}


TEST_F(ExceptionTest, testExceptionCopyConstruction)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

TEST_F(ExceptionTest, testExceptionAssignment)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

TEST_F(ExceptionTest, testExceptionClone)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

