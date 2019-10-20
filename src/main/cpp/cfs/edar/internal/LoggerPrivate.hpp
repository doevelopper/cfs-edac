

#ifndef CFS_EDAC_INTERNAL_LOGGERPRIVATE_HPP
#define CFS_EDAC_INTENRAL_LOGGERPRIVATE_HPP

#include <string>
#include <stdexcept>
// #include <apr-1/apr.h>
#include <apr.h>
//#include <apr-1.0/apr.h>
#include <log4cxx/logger.h>
#include <log4cxx/appender.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/consoleappender.h>                                // CONSOLE Appender
#include <log4cxx/fileappender.h>                                   // FILE Appender
#include <log4cxx/rolling/rollingfileappender.h>                    // ROLLING FILE Appender
#include <log4cxx/nt/nteventlogappender.h>                          // NT EVENT LOG Appender
#include <log4cxx/nt/outputdebugstringappender.h>                   // NT OUTPUTDEBUGSTRING Appender
#include <log4cxx/net/socketappender.h>                             // SOCKET Appender
#include <log4cxx/simplelayout.h>                                   // needed for simple layout
#include <log4cxx/patternlayout.h>                                  // needed for pattern layout
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>                                      // has typedefed string type used in log4cxx
#include <log4cxx/rolling/rollingpolicy.h>
#include <log4cxx/rolling/rollingpolicybase.h>
#include <log4cxx/rolling/triggeringpolicy.h>
#include <log4cxx/rolling/sizebasedtriggeringpolicy.h>
#include <log4cxx/rolling/fixedwindowrollingpolicy.h>
#include <log4cxx/xml/domconfigurator.h>

// extern log4cxx::LoggerPtr logger;

// #define LOG_TRACE(x) LOG4CXX_TRACE(logger , x)
// #define LOG_DEBUG(x) LOG4CXX_DEBUG(logger , x)
// #define LOG_INFO(x)  LOG4CXX_INFO(logger , x)
// #define LOG_WARN(x)  LOG4CXX_WARN(logger , x)
// #define LOG_ERROR(x) LOG4CXX_ERROR(logger , x)

namespace cfs::edac::internal
{
class LoggerPrivate
{
enum class Level : std::uint32_t
{
	EMERGENCY = (1 << 0),         /* system is unusable. A panic condition was reported to all processes. */
	CRITICAL = (1 << 1),
	FATAL = (1 << 2),             /* critical conditions */
	ALERT = (1 << 3),
	ERROR = (1 << 4),             /* action must be taken immediately. A condition that should be corrected
			                 immediately.  */
	WARNING = (1 << 5),           /* error conditions */
	INFO = (1 << 6),              /* warning conditions */
	TRACE = (1 << 7),             /* informational */
	DEBUG = (1 << 8),             /* debug-level messages. A message useful for debugging programs.  */
	ADVISORY = (1 << 9),
	INHIBIT = (1 << 10),
	HINDENBUG = (1 << 11),        /* "... bug with catastrophic behavior" */
	MANDELBUG = (1 << 12),        /* "... bug whose causes are so complex it defies repair" */
	BOHRBUG = (1 << 13),          /* "... relatively easily detected" */
	HEISENBUG = (1 << 14),        /* "... software bug that seems to disappear or alter its behavior when one
			                 attempts to study it."*/
	SCHROEDINBUG = (1 << 15)      /* "... bug that manifests itself in running software" */
};

public:

LoggerPrivate( unsigned long delay = 5000UL );
~LoggerPrivate( );
/*!
 * @brief Retrieve valy of delay beetween the read of config file
 * @param  s is a char array containing a proper C-string
 * @return value do delay (minus null) as an usigned int
 */
unsigned long periodicalCheck ( ) const;
/*!
 * @brief
 */
void loggerReset ( );
/*!
 * @brief
 * @param[in]  loggerName  The Logger name to get reference from.
 */
log4cxx::LoggerPtr getLoggerByName ( const char * loggerName );
void loadConfig ( const std::string & configFilename );
void loadConfigAndWatch ( const std::string & configFilename );
void loggerNames ( std::vector<std::string> & names );

//log4cxx::LoggerPtr operator ->( )
//{
//    return this->m_logger;
//}

// log4cxx::LoggerPtr operator = (const LoggerPrivate &logger)
// {
// return this->m_logger;
// }

//log4cxx::Logger * loggerSvce;

//DISABLE_COPY( LoggerPrivate );

private:

/*!
 *  @brief
 *  @return logger configuration status
 */
bool checkLogManagerStatus ( );
/*!
 *  @brief
 *  @param[in,out] s required file extention
 *  @return file extension
 */
std::string getFileExtension ( const std::string & s );
/*!
 *  @brief Value for periodical check if configFilename has been created or modified!
 */
unsigned long m_watchPeriod;
/*!
 *  @brief
 */
//static const char * configEnv;
/*!
 *  @brief
 */
//log4cxx::LoggerPtr m_logger;
static std::string m_loggerConfigLocation;
};
}
#endif

