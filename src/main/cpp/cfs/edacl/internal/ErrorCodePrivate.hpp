

/*!
 * @file filename
 * @brief Common source of API return status codes and erros management.
 * @author N/A
 *
 * Detailed description of the file here if needed.
 *
 * -----------------------------------------------------------------------
 *
 * Copyright (C) 2010-2018  (see AUTHORS file for a list of contributors)
 *
 * CFS-EDAC error management for cfs system applications.
 *
 * This file is part of CFS-EDAC.
 *
 * CFS-EDAC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFS-EDAC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CFS-EDAC. If not, see <http://www.gnu.org/licenses/>.
 *
 * -----------------------------------------------------------------------
 */

#ifndef CFS_EDAC_PRIVATE_ERRORCODEPRIVATE_HPP
#define CFS_EDAC_PRIVATE_ERRORCODEPRIVATE_HPP

/*!
 *  @brief CLF Error and Misc Linux kernel error system interface :
 *         Exception class(for recoverable errors)
 *         Error class (for unrecoverable errors)
           https://stackoverflow.com/questions/14196820/why-do-we-need-error-class
 *  <ul>
 *      <li> External
 *     <ol> <li>a href="https://docstore.mik.ua/orelly/java/langref/ch09_04.htm" target="_blank"><b>Java Exception &
 * Error class</b></a>
 *     </ol>
 *     <ol>
 *          <li>a href="https://docs.python.org/3.7/library/errno.html" target="_blank"><b>Python errore</b></a>
 *          <li>a href="https://docs.python.org/3.7/library/exceptions.html" target="_blank"><b>Exception
 * hierarchy</b></a>
 *          <li>a href="https://docs.python.org/3.7/library/errno.html" target="_blank"><b>Python errore</b></a>
 *     </ol>
 *      <li> OS based Error
 *          <ol>
 *              <li><a href="https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno.h"
 * target="_blank"><b>Python errore</b></a>
 *              <li><a href="https://github.com/torvalds/linux/blob/master/include/uapi/asm-generic/errno-base.h"
 * target="_blank"><b>Python errore</b></a>
 *              <li><a href="http://elixir.free-electrons.com/linux/latest/source/include/uapi/asm-generic/errno.h"
 * target="_blank"><b>Linux errno.h</b></a>
 *              <li><a href="http://elixir.free-electrons.com/linux/latest/source/include/uapi/asm-generic/errno-base.h"
 * target="_blank"><b>Linux errno-base.h</b></a>
 *          </ol>
 *  </ul>
 *
 */

/*!
 *  @brief Status Codes.
 *         Status Codes are 32 bit values formatted as follows:
 *
 ____________________________________________________________________________________________________________________
 |        | Sev   |  Res  |   Serv   |      Mission  Defined      |                       Code                      |
 |:------:|:-----:|:-----:|:--------:|:--------------------------:|:-----------------------------------------------:|
 | Class  | 3  3  | 2  2  | 2  2  2  | 2  2  2  2  2  1  1  1  1  | 1  1  1  1  1  1  -  -  -  -  -  -  -  -  -  -  |
 | Index  | 1  0  | 9  8  | 7  6  5  | 4  3  2  1  0  9  8  7  6  | 5  4  3  2  1  0  9  8  7  6  5  4  3  2  1  0  |
 | 32Bits | 32 31 | 30 29 | 28 27 26 | 25 24 23 22 21 20 19 18 17 | 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 |

 ________________________________________________________________________________________
 |     |        ServiceID        |     |    |    Severity   |      |    |    Reserved   |
 |:---:|:-----------------------:|     |----|:-------------:|      |----|:-------------:|
 | 000 |    Not a CFE Service    |     | 00 |    Success    |      | 00 |    -------    |
 | 001 |    Events Services      |     | 01 | Informational |      | 01 |    -------    |
 | 010 |    Executive Services   |     | 10 |     Error     |      | 10 |    -------    |
 | 011 |    File Services        |     | 11 |    Critical   |      | 11 |    -------    |
 | 100 |    OS API Services      |
 | 101 |    Software Bus Services|
 | 110 |    Tables Services      |
 | 111 |    Time Services        |

 ________________________________________________________________________________________________________
 |           |                                      Mission,Defined                                     |
 |:---------:|:----------------------------------------------------------------------------------------:|
 | 000000000 | Used to classify error codes   related  to mission specific library function calls, etc. |

 _______________________________________________________________________________________________________________
 |                  |                                      Error codes                                         |
 |:----------------:|:----------------------------------------------------------------------------------------:|
 | 0000000000000000 | Used to classify error codes   related  to mission specific library function calls, etc. |


 * @attention
 *    0xyyyy1bbb Normal failure (plausibly these should not even be "errors", but they are failures of the way
 *               operations are currently defined)
 *    0xyyyy15bb 15xx Platform errors
 *    2xxx user Attempt to do something illegal.
 *    2200 - errors from bindings and official APIs
 *    2300 - backup and restore errors
 *    4xxx - Internal errors (those that should be generated only by bugs) are decimal 4xxx
 */

#include <clocale>
#include <cstdint>
#include <system_error>
#include <type_traits>
//#include <cfs/edac/Export.hpp>

namespace cfs::edacl::internal
{
    /*!
     * @brief Type for specifying an error or status code.
     */
    using HRESULT = std::uint32_t;
    using status_t = std::uint32_t;
    using cfs_status_t = std::int8_t;

    HRESULT EDAC_SUCCESS = static_cast<std::uint32_t>( 0ULL );
    HRESULT EDAC_ERROR = ( !EDAC_SUCCESS );
    HRESULT EDAC_INVALIDE_ERROR = (0XFFFFFFFF);

			// https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
		enum class CfsErrorSeverity : std::uint32_t
		{
				CFE_SEVERITY_BITMASK = ( 0xC0000000L ),
				CFE_SEVERITY_SUCCESS = ( 0x00000000L ),
				CFE_SEVERITY_INFO = ( 0x40000000L ),
				CFE_SEVERITY_ERROR = ( 0x80000000L ),
				CFE_SEVERITY_CRITICAL = ( 0xC0000000L )
		};

		enum class CfeServiceIdentifiers : std::uint32_t
		{
				CFE_SERVICE_BITMASK = ( 0x0C000000L ),
				CFE_EVENTS_SERVICE = ( 0x02000000L ),
				CFE_EXECUTIVE_SERVICE = ( 0x04000000L ),
				CFE_FILE_SERVICE = ( 0x06000000L ),
				CFE_OSAPI_SERVICE = ( 0x08000000L ),
				CFE_SOFTWARE_BUS_SERVICE = ( 0x0A000000L ),
				CFE_TABLE_SERVICE = ( 0x0C000000L ),
				CFE_TIME_SERVICE = ( 0x0E000000L )
		};

		enum class edacErrorPage : std::uint32_t
		{
				CFS_ERRORS_PAGE_SIZE = 0x0000EA60,
				CFS_START_ERROR = ( 0x00004E20 ),
				CFS_START_USER_ERROR = ( 0x0001D4C0 ),
				CFS_START_APPLICATION_ERROR = ( 0x0001D4C0 ),
				CFS_START_SYSTEM_ERROR = ( 0x000AFC80 ),
		};

    class EDAC_MAIN_EXPORT ErrorCodePrivate
    {
        public:
			/*
			 * A container for the error details.
			 */
			struct ErrorFields
			{
				struct err
				{
					std::string domain;
					std::string location;
					std::string locationType;
				};
				std::uint32_t errorCode;
				std::string errorText;
				std::string severity;
				std::string recommendedAction;
				std::string rootCause;
				std::string service;
				std::string component;

			};

			ErrorCodePrivate();
			ErrorCodePrivate(const ErrorCodePrivate & orig) = delete;
			ErrorCodePrivate(ErrorCodePrivate && orig) = delete;
			ErrorCodePrivate & operator=(const ErrorCodePrivate & orig) = delete;
			ErrorCodePrivate & operator=(ErrorCodePrivate && orig) = delete;
			virtual ~ErrorCodePrivate();

      // const error_category & edac_category();

        private:
    };
}

#endif

