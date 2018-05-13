
//#include <posix/unistd.h>
#include <unistd.h>
#include <iostream>
#include <typeinfo>
#include <cfs/edac/LoggingService.hpp>

LoggingService::LoggingService()
{
}

LoggingService::LoggingService(unsigned long delay)
    : m_watchPeriod(delay)
{
    std::string configurationPath("");

    if( log4cxx::LogManager::getLoggerRepository()->isConfigured() )
    {
        throw std::logic_error("log4cxx configuration detected");
    }
    else
    {
        char * filePath;
        try
        {
            if( ( filePath = getenv("LOG4CXX_CONFIGURATION") ) == NULL )
            {
                std::cerr << "Failed to get loggger configuratin file" << std::endl;
            }
            else
            {
                configurationPath.assign(filePath);
            }
        }
        catch ( std::exception & e )
        {
            std::cout << typeid ( e ).name () << ": " << e.what () << std::endl;
        }
        catch ( ... )
        {
            std::cerr << " ??? " << std::endl;
        }
    }

    if( configurationPath.empty() /*&& getenv(log4cxx.properties)*/ )
    {
        log4cxx::PatternLayoutPtr layout   (new log4cxx::PatternLayout  (
                                                "%d{yyyy-MM-dd HH:mm:ss.SSS} (%-6c) [%-6p] [%15.15t] (%-10.20l) -- %m%n"
                                                ) );

        log4cxx::ConsoleAppenderPtr consoleAppender (new log4cxx::ConsoleAppender (layout) );

        log4cxx::helpers::Pool pool;
        consoleAppender->activateOptions(pool);
        log4cxx::BasicConfigurator::configure( consoleAppender );
        log4cxx::Logger::getRootLogger()->setLevel (log4cxx::Level::getTrace () );

        log4cxx::LogManager::getLoggerRepository()->setConfigured(true);
        log4cxx::LogManager::getLoggerRepository()->getRootLogger()->info("Starting the logging system - BASIC");
    }
    else
    {
        if( ::access(configurationPath.c_str(), R_OK) == 0 )
        {
            if( configurationPath.substr(configurationPath.find_last_of(".") + 1).compare("xml") == 0 )
            {
#if APR_HAS_THREADS
                log4cxx::xml::DOMConfigurator::configureAndWatch(configurationPath,
                                                                 static_cast< long >( this->periodicalCheck() ) );
#else

                // configurationPath.append(logFileProperties);
                log4cxx::xml::DOMConfigurator::configure(log4cxx::File(configurationPath).getPath() );
#endif
            }
            else
            {
#if APR_HAS_THREADS
                log4cxx::PropertyConfigurator::configureAndWatch(configurationPath,
                                                                 static_cast< long >( this->periodicalCheck() ) );
#else
                log4cxx::PropertyConfigurator::configure(configurationPath);
#endif
            }
        }

        log4cxx::Logger::getRootLogger()->setLevel(log4cxx::Level::getAll() );
        log4cxx::LogManager::getLoggerRepository()->setConfigured(true);

        // log4cxx::LogManager::getLoggerRepository()->getRootLogger()->trace("Starting the logging system" + configurationPath );
        // LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(),"Logger initialized. Appenders sise:" << log4cxx::Logger::getRootLogger()->getAllAppenders().size() );
    }

    LOG4CXX_INFO(log4cxx::Logger::getRootLogger(), "----START LOGGING-----" );
    LOG4CXX_TRACE( log4cxx::Logger::getRootLogger(),
        "Logger initialized. Appenders sise:" << log4cxx::Logger::getRootLogger()->getAllAppenders().size() );
}

LoggingService::~LoggingService()
{
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), __LOG4CXX_FUNC__);

    if( log4cxx::LogManager::getLoggerRepository()->isConfigured() )
    {
        LOG4CXX_INFO(log4cxx::Logger::getRootLogger(), "---- END LOGGING -----");
    }

    log4cxx::LogManager::shutdown();
}

unsigned long
LoggingService::periodicalCheck () const
{
    return ( this->m_watchPeriod );
}

bool
LoggingService::loggerReset ()
{
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), __LOG4CXX_FUNC__);
    log4cxx::LogManager::resetConfiguration();
    log4cxx::BasicConfigurator::resetConfiguration();

    return ( true );
}

std::string LoggingService::getFileExtension (const std::string & s)
{
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), __LOG4CXX_FUNC__);
    size_t i = s.rfind('.', s.length() );

    if( i != std::string::npos )
    {
        return ( s.substr(i + 1, s.length() - i) );
    }

    return ( "" );
}

log4cxx::LoggerPtr
LoggingService::getLoggerByName (const char * loggerName)
{
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), __LOG4CXX_FUNC__);

    return ( log4cxx::LogManager::getLoggerRepository()->getLogger(std::string(loggerName) ) );
}
