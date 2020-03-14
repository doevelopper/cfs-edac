

#ifndef CFS_EDAR_LOGGER_HPP
#define CFS_EDAR_LOGGER_HPP

#include <memory>
#include <string>
#include <cfs/utils/PimplPtr.hpp>
#include <log4cxx/logger.h>

#define LOG4CXX_DECLARE_STATIC_LOGGER private: static log4cxx::LoggerPtr logger;
#define LOG4CXX_DECLARE_STATIC_TEST_LOGGER protected : static log4cxx::LoggerPtr logger;
#define LOG4CXX_DECLARE_CLASS_LOGGER(name) private: log4cxx::LoggerPtr name;

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

