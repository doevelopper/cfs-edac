

#include <iostream>
#include <cstdlib>

#include <cfs/edac/Test.hpp>

int main(int argc, char**argv)
{
    cfs::edac::test::Test edacTest;

    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(),"TEST EDAC unit test");

    edacTest.run(argc,argv);

    return (EXIT_SUCCESS);
}

