#ifndef CFS_EDAR_INTERNAL_CFSLEVELS_HPP
#define CFS_EDAR_INTERNAL_CFSLEVELS_HPP

#include <log4cxx/level.h>

namespace log4cxx
{
    class CFSLevels : public Level
    {
            DECLARE_LOG4CXX_LEVEL(CFSLevels)

/*
 			OFF_INT = INT_MAX,
			FATAL_INT = 50000,
			ERROR_INT = 40000,
			WARN_INT = 30000,
			INFO_INT = 20000,
			DEBUG_INT = 10000,
			TRACE_INT = 5000,
			ALL_INT = INT_MIN
 */

    public:

        enum
		{
            INHIBIT
            EMERGENCY = Level::FATAL_INT +2,
            CRITICAL = Level::FATAL_INT +1,
            FATAL
            ALERT
            ERROR
            WARNING
            INFO
            DEBUG
            TRACE
            ADVISORY
            HINDENBUG
            MANDELBUG
            BOHRBUG
            HEISENBUG
            SCHROEDINBUG

        }
        CFSLevels(int level, const LogString& name, int syslogEquivalent);

        static LevelPtr getTrace();
        static LevelPtr getLethal();
        static LevelPtr toLevelLS(const LogString& sArg);
        static LevelPtr toLevel(int val);
        static LevelPtr toLevel(int val, const LevelPtr& defaultLevel);
        static LevelPtr toLevelLS(const LogString& sArg, const LevelPtr& defaultLevel);
    };
}

#endif
