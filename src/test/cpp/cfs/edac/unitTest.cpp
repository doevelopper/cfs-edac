

#include <iostream>
#include <cstdlib>

#include <cfs/edac/Test.hpp>

int main(int argc, char**argv)
{
    cfs::edac::test::Test edacTest;

    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(),"TEST EDAC unit test");
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->info("Running UnitTest");

    int status = edacTest.run(argc,argv);

    if (status != EXIT_SUCCESS)
    {
        log4cxx::LogManager::getLoggerRepository()->getRootLogger()->error("Unit Test failed");
    }

    return (EXIT_SUCCESS);
}

