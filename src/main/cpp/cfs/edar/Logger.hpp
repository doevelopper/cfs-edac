

#ifndef CFS_EDAC_LOGGER_LOGGER_HPP
#define CFS_EDAC_LOGGER_LOGGER_HPP

#include <memory>
#include <string>
#include <cfs/edac/internal/LoggerPrivate.hpp>

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
 #define LOG_GLOBAL_CATEGORY(category) \
    private: \
        static const log4cxx::LoggerPtr LOGGER;
*/

namespace cfs::edac
{
    class cfs::edac::internal::LoggerPrivate;

    class Logger
    {
        public:

            explicit Logger (unsigned long delay);
            virtual ~Logger ( );

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

            std::shared_ptr<cfs::edac::internal::LoggerPrivate> d_ptr;

        private:

            // DECLARE_PRIVATE( Logger )
            // DISABLE_COPY( Logger )
    };
}
#endif

