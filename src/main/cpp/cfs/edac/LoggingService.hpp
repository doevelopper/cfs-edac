
#ifndef CPPBDD101_EDAC_LOGGINGSERVICE_HPP
#define CPPBDD101_EDAC_LOGGINGSERVICE_HPP

#include <string>
#include <stdexcept>
//#include <apr-1/apr.h>
#include <apr.h>
#include <log4cxx/logger.h>
#include <log4cxx/appender.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/consoleappender.h>                              // CONSOLE Appender
#include <log4cxx/fileappender.h>                                 // FILE Appender
#include <log4cxx/rolling/rollingfileappender.h>                  // ROLLING FILE Appender
#include <log4cxx/nt/nteventlogappender.h>                        // NT EVENT LOG Appender
#include <log4cxx/nt/outputdebugstringappender.h>                 // NT OUTPUTDEBUGSTRING Appender
#include <log4cxx/net/socketappender.h>                           // SOCKET Appender
#include <log4cxx/simplelayout.h>                                 // needed for simple layout
#include <log4cxx/patternlayout.h>                                // needed for pattern layout
#include <log4cxx/logmanager.h>
#include <log4cxx/logstring.h>                                    // has typedefed string type used in log4cxx
#include <log4cxx/rolling/rollingpolicy.h>
#include <log4cxx/rolling/rollingpolicybase.h>
#include <log4cxx/rolling/triggeringpolicy.h>
#include <log4cxx/rolling/sizebasedtriggeringpolicy.h>
#include <log4cxx/rolling/fixedwindowrollingpolicy.h>
#include <log4cxx/xml/domconfigurator.h>

class LoggingService
{
    public:

        LoggingService();
        /*!
         * @brief
         * @param delay Volue in ms to check if logger config level has changed.
         */
        LoggingService(unsigned long delay = 5000L);
        /*!
         * @brief
         */
        virtual ~LoggingService();
        /*!
         * @brief
         */
        log4cxx::LoggerPtr operator -> (void)
        {
            return this->m_logger;
        }
        /*!
         * @brief
         */
        log4cxx::LoggerPtr operator = (const LoggingService & logger)
        {
            (void)logger;

            return this->m_logger;
        }
        /*!
         * @brief Retrieve valy of delay beetween the read of config file
         * @param  s is a char array containing a proper C-string
         * @return value do delay (minus null) as an usigned int
         */
        unsigned long periodicalCheck () const;
        /*!
         * @brief
         */
        bool loggerReset ();
        /*!
         * @brief
         * @param[in]  loggerName  The Logger name to get reference from.
         */
        log4cxx::LoggerPtr getLoggerByName (const char * loggerName);

    private:

        /*!
         *  @brief
         *  @return logger configuration status
         */
        bool checkLogManagerStatus ();
        /*!
         *  @brief
         *  @param[in,out] s required file extention
         *  @return file extension
         */
        std::string getFileExtension (const std::string & s);

        static const char * configEnv;  ///< 
        log4cxx::LoggerPtr m_logger;    ///< 
        unsigned long m_watchPeriod;    ///< Value for periodical check if configFilename has been created or modified!

    private:
};
#endif
