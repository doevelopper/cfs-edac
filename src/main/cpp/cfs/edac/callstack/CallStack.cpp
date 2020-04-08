

#include <cfs/edac/callstack/CallStack.hpp>
#include <cfs/edac/callstack/CallStackDataStructure.hpp>

using namespace cfs::edac::callstack;

log4cxx::LoggerPtr CallStack::logger = log4cxx::Logger::getLogger(std::string("cfs.edac.callStack.CallStack"));

CallStack::CallStack()
  : m_stackFrames()
{
}

CallStack::~CallStack()
{
}

const std::vector<CallStackDataStructure>& CallStack::frames() const noexcept
{
    return (m_stackFrames);
}


