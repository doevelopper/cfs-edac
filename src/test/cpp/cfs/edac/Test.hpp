

#ifndef CPPBDD101_TEST_HPP
#define CPPBDD101_TEST_HPP

#include <vector>
#include <gmock/gmock.h>
//#include <cfs/edar/Logger.hpp>

namespace cfs::edac::test
{
    class Test
    {
public:

        Test();
        Test(std::string & suite, unsigned int iteration = 1);
        Test(const Test & orig) = default;
        virtual ~Test();

        int run (int argc = 0, char * argv[] = NULL);
        static void showUsage(std::string name);
        void notYetImplemented();

private:

        std::string m_testSuites;
        unsigned int m_numberOfTestIteration;
    };
}

#endif

