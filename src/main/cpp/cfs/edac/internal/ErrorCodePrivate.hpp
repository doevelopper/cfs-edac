

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
   ___________________________________________________________________________________________________________________
 |        | Sev   |  Res  |   Serv   |      Mission  Defined      |                       Code                      |
 |:------:|:-----:|:-----:|:--------:|:--------------------------:|:-----------------------------------------------:|
 | Class  | 3  3  | 2  2  | 2  2  2  | 2  2  2  2  2  1  1  1  1  | 1  1  1  1  1  1  -  -  -  -  -  -  -  -  -  -  |
 | Index  | 1  0  | 9  8  | 7  6  5  | 4  3  2  1  0  9  8  7  6  | 5  4  3  2  1  0  9  8  7  6  5  4  3  2  1  0  |
 | 32Bits | 32 31 | 30 29 | 28 27 26 | 25 24 23 22 21 20 19 18 17 | 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 |

   _______________________________________________________________________________________
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

   _______________________________________________________________________________________________________
 |           |                                      Mission,Defined                                     |
 |:---------:|:----------------------------------------------------------------------------------------:|
 | 000000000 | Used to classify error codes   related  to mission specific library function calls, etc. |

   ______________________________________________________________________________________________________________
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
#include <cfs/edac/Export.hpp>

namespace cfs::edac::internal
{
    using HRESULT = std::uint32_t;
    using status_t = std::uint32_t;
    HRESULT EDAC_SUCCESS = static_cast<std::uint32_t>( 0ULL );
    HRESULT EDAC_ERROR = ( !EDAC_SUCCESS );
    HRESULT EDAC_INVALIDE_ERROR = (0XFFFFFFFF);
    /*!
     * @defgroup CFS_Status_Codes CFS Error Space
     * @{
     */
    enum class edacErrorPage : std::uint32_t
    {
        CFS_ERRORS_PAGE_SIZE = 0x0000EA60,
        CFS_START_ERROR = ( 0x00004E20 ),
        CFS_START_USER_ERROR = ( 0x0001D4C0 ),
        CFS_START_APPLICATION_ERROR = ( 0x0001D4C0 ),
        CFS_START_SYSTEM_ERROR = ( 0x000AFC80 ),
    };
    /*!
     * @}
     */

    /*!
     * @defgroup CFS_Severity_Status CFS Error severity.
       Severity  Meaning
        00      Informational: This level is used to convey information to the user. No error has occurred.
     * Informational messages are listed only when the FLAG (00) option is specified.
        10      Warning: This level indicates that an error was detected but is not serious enough to interfere with the
     * running of the program.
        20      Error: This level indicates that an error was made, but the compiler is taking a recovery that might
     * yield the desired code.
        30      Severe Error: This level indicates that a serious error was detected. Compilation is completed, but the
     * module object is not created and running of the program cannot be attempted.
        40      Unrecoverable: This level usually indicates a user error that forces termination of processing.
        50      Unrecoverable: This level usually indicates a compiler error that forces termination of processing.
        99      Action: Some manual action is required, such as entering a reply, changing printer forms, or replacing
     * diskettes.
     * @{
     */
    enum class edacSeverity : std::uint32_t
    {
        CFS_SEVERITY_BITMASK = ( 0xC0000000L ),
        CFS_SEVERITY_SUCCESS = ( 0x00000000L ),
        CFS_SEVERITY_NOTICE = ( 0x40000000L ),   /*!< An unusual event has occured, though not an error condition. This
                                                    should be investigated for the root cause. | */
        CFS_SEVERITY_DEBUG = ( 0x40000000L ),    /*!< Useful non-operational messages that can assist in debugging.
                                                    These should not occur during normal operation. | */
        CFS_SEVERITY_INFO = ( 0x40000000L ),     /*!< Normal operational messages. Useful for logging. No action is
                                                    required for these messages. | */
        CFS_SEVERITY_ERROR = ( 0x80000000L ),    /*!< Indicates an error in secondary/redundant systems. | */
        CFS_SEVERITY_WARNING,                    /*!< Indicates about a possible future error if this is not resolved
                                                    within a given timeframe. Example would be a low battery warning. |
                                                  */
        CFS_SEVERITY_ALERT,                      /*!< Action should be taken immediately. Indicates error in
                                                    non-critical systems. | */
        CFS_SEVERITY_CRITICAL = ( 0xC0000000L ), /*!< Action must be taken immediately. Indicates failure in a primary
                                                    system. | */
        CFS_SEVERITY_EMERGENCY,                  /*!< System is unusable. This is a "panic" condition. | */
        CFS_SEVERITY_NONE                        /**< No logging will occur */
    };
    /*!
     * @}
     */
    /*!
     * @defgroup CFS_service_id CFS Services identifications.
     * @{
     */
    enum class edacServiceId : std::uint32_t
    {
        CFS_SERVICE_BITMASK = ( 0x0e000000L ),
        CFS_EVENTS_SERVICE = ( 0x02000000L ),
        CFS_EXECUTIVE_SERVICE = ( 0x04000000L ),
        CFS_FILE_SERVICE = ( 0x06000000L ),
        CFS_OSAPI_SERVICE = ( 0x08000000L ),
        CFS_SOFTWARE_BUS_SERVICE = ( 0x0a000000L ),
        CFS_TABLE_SERVICE = ( 0x0c000000L ),
        CFS_TIME_SERVICE = ( 0x0e000000L )
                           /*!
                            * @}
                            */
    };

    enum class errc : std::int32_t
    {
        argument_list_too_long = std::int32_t(std::errc::argument_list_too_long),
        argument_out_of_domain = std::int32_t(std::errc::argument_out_of_domain),
        bad_address = std::int32_t(std::errc::bad_address),
        bad_file_descriptor = std::int32_t(std::errc::bad_file_descriptor),
        broken_pipe = std::int32_t(std::errc::broken_pipe),
        device_or_resource_busy = std::int32_t(std::errc::device_or_resource_busy),
        directory_not_empty = std::int32_t(std::errc::directory_not_empty),
        executable_format_error = std::int32_t(std::errc::executable_format_error),
        file_exists = std::int32_t(std::errc::file_exists),
        file_too_large = std::int32_t(std::errc::file_too_large),
        filename_too_long = std::int32_t(std::errc::filename_too_long),
        function_not_supported = std::int32_t(std::errc::function_not_supported),
        illegal_byte_sequence = std::int32_t(std::errc::illegal_byte_sequence),
        inappropriate_io_control_operation = std::int32_t(std::errc::inappropriate_io_control_operation),
        interrupted = std::int32_t(std::errc::interrupted),
        invalid_argument = std::int32_t(std::errc::invalid_argument),
        invalid_seek = std::int32_t(std::errc::invalid_seek),
        io_error = std::int32_t(std::errc::io_error),
        is_a_directory = std::int32_t(std::errc::is_a_directory),
        no_child_process = std::int32_t(std::errc::no_child_process),
        no_lock_available = std::int32_t(std::errc::no_lock_available),
        no_space_on_device = std::int32_t(std::errc::no_space_on_device),
        no_such_device_or_address = std::int32_t(std::errc::no_such_device_or_address),
        no_such_device = std::int32_t(std::errc::no_such_device),
        no_such_file_or_directory = std::int32_t(std::errc::no_such_file_or_directory),
        no_such_process = std::int32_t(std::errc::no_such_process),
        not_a_directory = std::int32_t(std::errc::not_a_directory),
        not_enough_memory = std::int32_t(std::errc::not_enough_memory),
        operation_not_permitted = std::int32_t(std::errc::operation_not_permitted),
        permission_denied = std::int32_t(std::errc::permission_denied),
        read_only_file_system = std::int32_t(std::errc::read_only_file_system),
        resource_deadlock_would_occur = std::int32_t(std::errc::resource_deadlock_would_occur),
        resource_unavailable_try_again = std::int32_t(std::errc::resource_unavailable_try_again),
        result_out_of_range = std::int32_t(std::errc::result_out_of_range),
        too_many_files_open_in_system = std::int32_t(std::errc::too_many_files_open_in_system),
        too_many_files_open = std::int32_t(std::errc::too_many_files_open),
        too_many_links = std::int32_t(std::errc::too_many_links)
    };

    inline std::error_code make_error_code(errc E)
    {
        return std::error_code(static_cast<int>(E), std::generic_category());
    }

    class EDAC_MAIN_EXPORT ErrorCodePrivate
    {
        public:

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
namespace std
{
    // Tell the C++ 11 STL metaprogramming that enum edac::errc::edacErrc
    // is registered with the standard error code system
    template <>
    struct is_error_code_enum<cfs::edac::errc>
        : std::true_type
    {
    };
    /*
        template< >
        struct is_error_code_enum< edac::errc::edacErrc >
            : std::true_type
        {
        };

        template< >
        struct is_error_code_enum< edac::errc::edacAppErrc >
            : std::true_type
        {
        };

        template< >
        struct is_error_code_enum< edac::errc::edacSSLErrc >
            : std::true_type
        {
        };
     */
}
#endif

