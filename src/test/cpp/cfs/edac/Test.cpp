
#include <cfs/edac/Test.hpp>

log4cxx::LoggerPtr cfs::edac::test::Test::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.test.Test") );
const unsigned long cfs::edac::test::Test::LOGGER_WATCH_DELAY = 5000UL;


cfs::edac::test::Test::Test()
    : m_testSuites(std::string() )
    , m_numberOfTestIteration(1)
    , m_loggerService(new LoggingService(LOGGER_WATCH_DELAY))
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

cfs::edac::test::Test::Test(std::string & suite, unsigned int iteration)
    : m_testSuites(suite)
    , m_numberOfTestIteration(iteration)
    , m_loggerService(new LoggingService(LOGGER_WATCH_DELAY))
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
}

cfs::edac::test::Test::~Test()
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
    delete this->m_loggerService;
}


int cfs::edac::test::Test::run (int argc, char * argv[])
{
    LOG4CXX_TRACE(logger, __LOG4CXX_FUNC__);
    ::testing::InitGoogleTest(&argc , argv);
    return RUN_ALL_TESTS();
}

void cfs::edac::test::Test::showUsage(std::string name)
{
    LOG4CXX_TRACE(logger ,"Usage called");

    std::cerr << "Usage: " << name << " <option(s)> SOURCES \n"
              << "Options:\n"
              << "\t-h,--help \t Show this help message\n"
              << "\t-i,--iterration \t Number of iteration on test Default 1\n"
              << "\t-o,--outputpath \t Specify the destination path Default netx to executable\n"
	      << "\t-m,--module \t The name of xml test report to be generated\n"
              << "\t-l,--list \t Specify the list of tests to be executed Default netx to executable\n"
              << std::endl;
}

