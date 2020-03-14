
#include <cfs/edar/internal/CFSLevels.hpp>
#include <log4cxx/helpers/stringhelper.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

IMPLEMENT_LOG4CXX_LEVEL(CFSLevels)

CFSLevels::CFSLevels(int level1, const LogString& name1, int syslogEquivalent1)
	: Level(level1, name1, syslogEquivalent1)
{
}

LevelPtr CFSLevels::getTrace()
{
	static const LevelPtr trace(new CFSLevels(CFSLevels::TRACE_INT, LOG4CXX_STR("TRACE"), 7));
	return trace;
}

LevelPtr CFSLevels::getLethal()
{
	static const LevelPtr lethal(new CFSLevels(CFSLevels::LETHAL_INT, LOG4CXX_STR("LETHAL"), 0));
	return lethal;
}

LevelPtr CFSLevels::toLevelLS(const LogString& sArg)
{
	return toLevelLS(sArg, getTrace());
}


LevelPtr CFSLevels::toLevel(int val)
{
	return toLevel(val, getTrace());
}

LevelPtr CFSLevels::toLevel(int val, const LevelPtr& defaultLevel)
{
	switch (val)
	{
		case TRACE_INT:
			return getTrace();

		case LETHAL_INT:
			return getLethal();

		default:
			return defaultLevel;
	}
}

LevelPtr CFSLevels::toLevelLS(const LogString& sArg, const LevelPtr& defaultLevel)
{
	if (sArg.empty())
	{
		return defaultLevel;
	}

	if (StringHelper::equalsIgnoreCase(sArg,
			LOG4CXX_STR("TRACE"), LOG4CXX_STR("trace")))
	{
		return getTrace();
	}

	if (StringHelper::equalsIgnoreCase(sArg,
			LOG4CXX_STR("LETHAL"), LOG4CXX_STR("lethal")))
	{
		return getLethal();
	}

	return Level::toLevel(sArg, defaultLevel);
}

