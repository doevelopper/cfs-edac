

#include <cfs/edac/Test.hpp>

using namespace cfs::edac;
using namespace cfs::edac::test;

Test::Test()
		: m_testSuites(std::string() )
		, m_numberOfTestIteration(1)
{
}

Test::Test(std::string & suite, unsigned int iteration)
		: m_testSuites(suite)
		, m_numberOfTestIteration(iteration)
{
}

Test::~Test()
{
}

void Test::notYetImplemented()
{
		//GTEST_NONFATAL_FAILURE_("Not YET implemented!!!!!!");
}

int Test::run (int argc, char * argv[])
{
		::testing::GTEST_FLAG(repeat) = m_numberOfTestIteration;
		::testing::GTEST_FLAG(output) = "xml:Report.xml"; // GTEST_FLAG(output) = "xml:" + path;
		//  ::testing::FLAGS_gmock_verbose = "verbose";
		//  ::testing::GTEST_FLAG(print_time) = false;

		try
		{
				::testing::InitGoogleTest(&argc, argv);
				// ::testing::InitGoogleMock(&argc , argv);
		}
		catch (std::exception & e)
		{
				std::cerr << "Issues while innitializing test environment" << typeid (e).name () << ": " << e.what () <<
				        std::endl;
		}
		catch (...)
		{
				std::cerr << "Unhandled exception" << std::endl;
		}

		return RUN_ALL_TESTS();
}

void Test::showUsage(std::string name)
{
		std::cerr << "Usage: " << name << " <option(s)> SOURCES \n"
		          << "Options:\n"
		          << "\t-h,--help \t Show this help message\n"
		          << "\t-i,--iterration \t Number of iteration on test Default 1\n"
		          << "\t-o,--outputpath \t Specify the destination path Default netx to executable\n"
		          << "\t-m,--module \t The name of xml test report to be generated\n"
		          << "\t-l,--list \t Specify the list of tests to be executed Default netx to executable\n"
		          << std::endl;
}

