

#ifndef CFS_EDAR_LOGGER_HPP
#define CFS_EDAR_LOGGER_HPP

#include <memory>
#include <string>
#include <cfs/utils/PimplPtr.hpp>
#include <log4cxx/logger.h>
// EMERG    0       /* system is unusable. A panic condition was reported to all processes. */
// ALERT    1       /* action must be taken immediately. A condition that should be corrected immediately.
// CRIT     2       /* critical conditions */
// ERR      3       /* error conditions */
// WARNING  4       /* warning conditions */
// NOTICE   5       /* normal but significant condition. A condition requiring special handling.  */
// INFO     6       /* informational */
// DEBUG    7       /* debug-level messages. A message useful for debugging programs.  */

/*
 #define LOG_TRACE(message)          LOG4CXX_TRACE(logger, message)
 #define LOG_DEBUG(message)          LOG4CXX_DEBUG(logger, message)
 #define LOG_INFO(message)           LOG4CXX_INFO(logger, message)
 #define LOG_WARNING(message)        LOG4CXX_WARN(logger, message)
 #define LOG_ERROR(message)          LOG4CXX_ERROR(logger, message)
 #define LOG_FATAL(message)          LOG4CXX_FATAL(logger, message)
 #define LOG_ASSERT(cond, message)   LOG4CXX_ASSERT(logger, condition, message)
 #define LOG_GLOBAL_CATEGORY(category) private: static const log4cxx::LoggerPtr LOGGER; */

namespace cfs::edar
{
    class LoggingServicePrivate;

    class LoggingService
    {
        public:

            explicit LoggingService (unsigned long delay);
            LoggingService(const LoggingService&) = delete;
            LoggingService(LoggingService&&) = delete;
            LoggingService& operator=(const LoggingService&) = delete;
            LoggingService& operator=(LoggingService&&) = delete;
            virtual ~LoggingService ( );

            void configure ( );

            [[deprecated("Replaced by LOG4CXX_TRACE macro, which has an improved interface")]]
            void trace ( const std::string & s );
            [[deprecated("Replaced by LOG4CXX_BEBUG, which has an improved interface")]]
            void debug ( const std::string & s );
            [[deprecated("Replaced by LOG4CXX_INFO, which has an improved interface")]]
            void info ( const std::string & s );
            [[deprecated("Replaced by LOG4CXX_WARN, which has an improved interface")]]
            void warn ( const std::string & s );
            [[deprecated("Replaced by LOG4CXX_ERROR, which has an improved interface")]]
            void error ( const std::string & s );
            [[deprecated("Replaced by LOG4CXX_FATAL, which has an improved interface")]]
            void fatal ( const std::string & s );

        protected:

            // std::shared_ptr<LoggingServicePrivate> d_ptr;
            cfs::utils::PimplPtr<LoggingServicePrivate> d_ptr;

        private:

            Q_DECLARE_PRIVATE(LoggingService);
    };
}
#endif

