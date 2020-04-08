

#include <cfs/edac/ExceptionTest.hpp>

using namespace cfs::edac;
using namespace cfs::edac::test;

log4cxx::LoggerPtr ExceptionTest::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.ExceptionTest"));

ExceptionTest::ExceptionTest()
    : testee()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

ExceptionTest::~ExceptionTest()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

void ExceptionTest::SetUp()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    testee = new Exception(0);
}

void ExceptionTest::TearDown()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
    delete testee;
}

TEST_F(ExceptionTest, test_Simple)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
    EXPECT_EQ("UNK", testee->what());
    EXPECT_EQ(0, testee->errorCode());
}

TEST_F(ExceptionTest, testExceptionConstruction)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

TEST_F(ExceptionTest, testExceptionCopyConstruction)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

TEST_F(ExceptionTest, testExceptionAssignment)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}

TEST_F(ExceptionTest, testExceptionClone)
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__ );
}


