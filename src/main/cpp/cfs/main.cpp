

/*!
 *      Copyright {{ year }} {{ organization }}

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
    or implied. See the License for the specific language governing
    permissions and limitations under the License.
 */


#include <iostream>
#include <cstdlib>
#include <cfs/edar/LoggingService.hpp>

int main(int argc, char**argv)
{
    cfs::edar::LoggingService * loggingService = new cfs::edar::LoggingService(5000UL);

    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), "CFS Error handling !");
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), "Error Detection and Classification");
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), "Error Detection and Correction.");
    LOG4CXX_TRACE(log4cxx::Logger::getRootLogger(), "Error Detection and Reporting.");

    if(loggingService)
    {
        delete loggingService;
        loggingService = nullptr;
    }

    return (EXIT_SUCCESS);
}

