

#include <string>
#include <cfs/edar/Logger.hpp>

using namespace cfs::edar;
using namespace cfs::edar::internal;

Logger::Logger(unsigned long loggerWatchDelay )
    : d_ptr( new LoggerPrivate(loggerWatchDelay))
{
    //Q_D( Logger );

    // d->loggerSvce = log4cxx::Logger::getLogger (name.toStdString().c_str());
}

Logger::~Logger( )
{
    //Q_D( Logger );
}

void Logger::configure( )
{
    //::BasicConfigurator::configure();
}

void Logger::debug( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->debug( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->debug(s);
}

void Logger::info( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->info( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->info(s);
}

void Logger::trace( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->trace( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->trace(s);
}

void Logger::warn( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->warn( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->warn(s);
}

void Logger::error( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->error( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->error(s);
}

void Logger::fatal( const std::string & s )
{
    // Q_D( Logger );
    // d->loggerSvce->fatal( s.toStdString( ) );
    log4cxx::LogManager::getLoggerRepository()->getRootLogger()->fatal(s);
}

