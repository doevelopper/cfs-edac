

#ifndef CFS_EDAR_INTERNAL_LOGGERPRIVATE_HPP
#define CFS_EDAR_INTENRAL_LOGGERPRIVATE_HPP

#include <string>
#include <stdexcept>
#include <apr-1/apr.h>
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

namespace cfs::edar::internal
{
    class LoggerPrivate
    {
        public:




            LoggerPrivate( unsigned long delay = 5000UL );
            LoggerPrivate( const std::string & logFileProperties, std::string path = "/etc/cfg" );
            LoggerPrivate(const LoggerPrivate&) = default;
            LoggerPrivate(LoggerPrivate&&) = default;
            LoggerPrivate& operator=(const LoggerPrivate&) = default;
            LoggerPrivate& operator=(LoggerPrivate&&) = default;
            ~LoggerPrivate( );
            /*!
             * @brief Retrieve valy of delay beetween the read of config file
             * @param  s is a char array containing a proper C-string
             * @return value do delay (minus null) as an usigned int
             */
            unsigned long periodicalCheck ( ) const;
            void periodicalCheck ( unsigned long delay);
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
            void setLoggerLevel (const std::string &loggerId, const std::string &level);
            void setRootDefaultLevel (const std::string &level);
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
            /*!
             * @brief Name of the env variable pointing to logging config file
             */
            static const char * configEnv;
    };
}
#endif

