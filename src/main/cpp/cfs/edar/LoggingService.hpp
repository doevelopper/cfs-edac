

#ifndef CFS_EDAR_LOGGER_HPP
#define CFS_EDAR_LOGGER_HPP

#include <memory>
#include <string>
#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <cfs/utils/PimplPtr.hpp>
#include <log4cxx/logger.h>

#define LOG4CXX_DECLARE_STATIC_LOGGER private: static log4cxx::LoggerPtr logger;
#define LOG4CXX_DECLARE_STATIC_TEST_LOGGER protected : static log4cxx::LoggerPtr logger;
#define LOG4CXX_DECLARE_CLASS_LOGGER(name) private: log4cxx::LoggerPtr name;
#define LOG4CXX_DEFINE_CLASS_LOGGER(name) log4cxx::Logger::getLogger(std::string(boost::core::demangle( name )));
#define LOG std::clog << __DATE__ << " " << __TIME__ << " " << __FUNCTION__ << std::endl;

#define CREATE_LOGGERPTR_LOCAL(loggerVar, loggerName) \
    log4cxx::LoggerPtr loggerVar = log4cxx::LoggerPtr(log4cxx::Logger::getLogger(loggerName));

#define LOG4CXX_DEFINE_NS_LOGGER(loggerVar, loggerName) \
     namespace \
     { \
        CREATE_LOGGERPTR_LOCAL(loggerVar, loggerName); \
     }

#define INIT_LOGGER(fileName) \
    log4cxx::PropertyConfigurator::configure(fileName);

#define LOG_FUNCTION(x) \
    LOG4CXX_TRACE(this->logger, __FUNCTION__ << "(" << x << ")");

 /*!
 * @brief Fallback logging macro to console appender.
 * @param stream Standard stream to log to.
 * @return Given @a stream.
 * @exemple LOG_CA(std::cout) << "streaming to standard output." << std::endl;
 *          LOG_CA(std::cerr) << "streaming to standard error."  << std::endl;
 */
#define LOG_CA(stream) \
    stream << "(" << "processID " << ") " \
           << "[" << logger << "::" << __func__ << "] "


#define LOG_DEBUG(logger,data) { \
    if(logger) std::cout<<logger<<": "<<data<<std::endl; \
    else LOG_CA(std::cout) << data <<std::endl; \
}

#define LOG_INFO(logger,data) { \
    if(logger) std::cout<<logger<<": "<<data<<std::endl; \
    else LOG_CA(std::cout) << data <<std::endl; \
}

#define LOG_WARN(logger,data) { \
    if(logger) std::cout<<logger<<": "<<data<<std::endl; \
    else LOG_CA(std::cout) << data <<std::endl; \
}

#define LOG_ERROR(logger,data) { \
    if(logger) std::cerr<<logger<<": "<<data<<std::endl; \
    else LOG_CA(std::cerr) << data <<std::endl; \
}

#define LOG_FATAL(logger,data) { \
    if(logger) std::cerr<<logger<<": "<<data<<std::endl; \
    else LOG_CA(std::cout) << data <<std::endl; \
}

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
            void flush();

        protected:

            // std::shared_ptr<LoggingServicePrivate> d_ptr;
            cfs::utils::PimplPtr<LoggingServicePrivate> d_ptr;

        private:

            Q_DECLARE_PRIVATE(LoggingService);
    };
}
#endif

