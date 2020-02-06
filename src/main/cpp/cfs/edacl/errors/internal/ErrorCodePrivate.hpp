

/*!
 * @file
 * @brief Common source of API return status codes and erros management.
 */

#ifndef CFS_EDACL_ERRORS_INTERNAL_ERRORCODEPRIVATE_HPP
#define CFS_EDACL_ERRORS_INTERNAL_ERRORCODEPRIVATE_HPP
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

/*! @defgroup CFS_Status_Codes CFS Error Space
 *  @brief Status Codes.
 *         Status Codes are 32 bit values formatted as follows:

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
#include <stdexcept>
#include <string_view>
#include <cfs/edac/Export.hpp>

namespace cfs::edacl::errors::internal
{
    using HRESULT = std::uint32_t;
    using status_t = std::uint32_t;
    using cfs_status_t = std::int8_t;
    HRESULT CFE_SUCCESS = static_cast<std::uint32_t>( 0ULL );
    HRESULT CFE_ERROR = ( !CFE_SUCCESS );
    HRESULT CFE_INVALIDE_ERROR = (0XFFFFFFFF);

    enum class edacErrorPage : std::uint32_t
    {
        OS_ERRORS_PAGE_SIZE = 0x0000EA60,
        OS_START_ERROR = (0x00004E20),
        OS_START_USER_ERROR = (0x0001D4C0),
        OS_START_APPLICATION_ERROR = (0x0001D4C0),
        OS_START_SYSTEM_ERROR = (0x000AFC80),
    };
    /*!
     * @defgroup CFS_Severity_Status CFS Error severity.
     * Severity  Meaning
     *   00   Informational: This level is used to convey information to the user. No error has occurred.
     *            Informational messages are listed only when the FLAG (00) option is specified.
     *   10   Warning: This level indicates that an error was detected but is not serious enough to interfere with the
     *            running of the program.
     *   20   Error: This level indicates that an error was made, but the compiler is taking a recovery that might
     *            yield the desired code.
     *   30   Severe Error: This level indicates that a serious error was detected. Compilation is completed, but the
     *            module object is not created and running of the program cannot be attempted.
     *   40   Unrecoverable: This level usually indicates a user error that forces termination of processing.
     *   50   Unrecoverable: This level usually indicates a compiler error that forces termination of processing.
     *   99   Action: Some manual action is required, such as entering a reply, changing printer forms, or replacing
     *        disk...
     * @{
     */
    enum class edacSeverity : std::uint32_t
    {
        CFE_SEVERITY_BITMASK = (0xc0000000L),
        CFE_SEVERITY_SUCCESS = (0x00000000L),
        CFE_SEVERITY_NOTICE = 5,            /*!< An unusual event has occured, though not an error condition. This
                                               should be investigated for the root cause.*/
        CFE_SEVERITY_DEBUG = 7,             /*!< Useful non-operational messages that can assist in debugging. These
                                               should not occur during normal operation.*/
        CFE_SEVERITY_INFO = (0x40000000L),  /*!< Normal operational messages. Useful for logging. No action is required
                                               for these messages.*/
        CFE_SEVERITY_WARNING = 4,           /*!< Indicates about a possible future error if this is not resolved within
                                               a given timeframe. Example would be a low battery warning.*/
        CFE_SEVERITY_ERROR = (0xc0000000L), /*!< Indicates an error in secondary/redundant systems.*/
        CFE_SEVERITY_ALERT = 1,             /*!< Action should be taken immediately. Indicates error in non-critical
                                               systems.*/
        CFE_SEVERITY_CRITICAL = 2,          /*!< Action must be taken immediately. Indicates failure in a primary
                                               system.*/
        CFS_SEVERITY_EMERGENCY = 0,         /*!< System is unusable. This is a "panic" condition.*/
        CFE_SEVERITY_NONE,                  /*!< No logging will occur*/
        CFE_SEVERITY_ENUM_END = 8
    };
    /*!
     * @}
     */
    enum class edacServiceId : std::uint32_t
    {
        CFE_SERVICE_BITMASK = (0x0e000000L),
        CFE_EVENTS_SERVICE = (0x02000000L),
        CFE_EXECUTIVE_SERVICE = (0x04000000L),
        CFE_FILE_SERVICE = (0x06000000L),
        CFE_OSAPI_SERVICE = (0x08000000L),
        CFE_SOFTWARE_BUS_SERVICE = (0x0a000000L),
        CFE_TABLE_SERVICE = (0x0c000000L),
        CFE_TIME_SERVICE = (0x0e000000L)
    };

    enum class edacErrc : std::uint32_t
    {
        ERROR_TIME_OUT_OF_RANGE = (0xce000002L),
        ERROR_TBL_NOT_IMPLEMENTED = (0xcc00ffffL),
        ERROR_INFO_RECOVERED_TBL = (0x4c000027L),
        ERROR_INVALID_HANDLE,
        ERROR_NOT_ENOUGH_MEMORY,
        ERROR_BAD_FORMAT,
        ERROR_INVALID_ACCESS,
        ERROR_INVALID_DATA,
        ERROR_OUTOFMEMORY,
        ERROR_NOT_SAME_DEVICE,
        ERROR_NOT_READY,
        ERROR_CRC,
        ERROR_WRITE_FAULT,
        ERROR_READ_FAULT,
        ERROR_GEN_FAILURE,
        ERROR_SHARING_VIOLATION,
        ERROR_HANDLE_EOF,
        ERROR_HANDLE_DISK_FULL,
        ERROR_NOT_SUPPORTED,
        ERROR_NETWORK_BUSY,
        ERROR_ADAP_HDW_ERR,
        ERROR_OUT_OF_STRUCTURES,
        ERROR_INVALID_PARAMETER,
        ERROR_CONTINUE,     /**< Iteration has not converged */
        ERROR_FAULT,        /**< Invalid pointer */
        ERROR_SANITY,       /**< Sanity check failed - shouldn't happen */
        ERROR_ZERODIV,      /**< Tried to divide by zero */
        ERROR_SING,         /**< Apparent singularity detected */
        ERROR_DIVERGE,      /**< Integral or series is divergent */
        ERROR_UNIMPL,       /**< Requested feature not (yet) implemented */
        ERROR_COULDNT_RESOLVE_PROXY,
        ERROR_COULDNT_RESOLVE_HOST,
        ERROR_COULDNT_CONNECT,
        ERROR_WEIRD_SERVER_REPLY,
        ERROR_REMOTE_ACCESS_DENIED,
        ERROR_FTP_ACCEPT_TIMEOUT,
        ERROR_FTP_WEIRD_PASV_REPLY,
        ERROR_FTP_WEIRD_227_FORMAT,
        ERROR_FTP_CANT_GET_HOST,
        ERROR_ABORTED_BY_CALLBACK,
        STATUS_OK = 0,                        ///< Operation has completed successfully.
        STATUS_FAILURE = 1,                   ///< Operation has failed for some undefined reason.
        STATUS_UNIMPLEMENTED = 2,             ///< Given operation has not been implemented.
        STATUS_INVALID_ARGUMENT = 3,          ///< An argument to the operation is invalid.
        STATUS_INVALID_STATE = 4,             ///< This operation is invalid for the current device state.
        STATUS_INVALID_COMMAND = 5,           ///< This command is not recognized.
        STATUS_INVALID_INTERFACE = 6,         ///< This interface is not supported.
        STATUS_INTERNAL_ERROR = 7,            ///< An internal runtime error has occured.
        STATUS_SECURITY_ERROR = 8,            ///< A security/authentication error has occured.
        STATUS_PARSE_ERROR = 9,               ///< A error has occured while parsing the command.
        STATUS_IN_PROGRESS = 10,              ///< This operation is in progress.
        STATUS_NOMEM = 11,                    ///< Operation prevented due to memory pressure.
        STATUS_BUSY = 12,                     ///< The device is currently performing a mutually exclusive operation
        STATUS_PROP_NOT_FOUND = 13,           ///< The given property is not recognized.
        STATUS_DROPPED = 14,                  ///< A/The packet was dropped.
        STATUS_EMPTY = 15,                    ///< The result of the operation is empty.
        STATUS_CMD_TOO_BIG = 16,              ///< The command was too large to fit in the internal buffer.
        STATUS_NO_ACK = 17,                   ///< The packet was not acknowledged.
        STATUS_CCA_FAILURE = 18,              ///< The packet was not sent due to a CCA failure.
        STATUS_ALREADY = 19,                  ///< The operation is already in progress.
        STATUS_ITEM_NOT_FOUND = 20,           ///< The given item could not be found.
        STATUS_INVALID_COMMAND_FOR_PROP = 21, ///< The given command cannot be performed on this property.
        Heisenbug,                            //!< Bug that seems to disappear or alter its behavior when one attempts
        //   to study it.
        Hindenbug,                            //!< Bug with catastrophic behavior.
        Schroedinbug,                         //!< Bug that manifests itself in running software.
        Bohrbug,                              //!< Bug that do not change its behavior and are relatively easily
        //   detected.
        Mandelbug                             //!< Bug whose causes are so complex.
    };
    /*!
     * @brief Error Code type enum class used to throw a exception with std::make_error_code in case of generic user
     * error .
     *
     */
    enum class CfeUserError : std::uint32_t
    {
        STATUS_ERR_NULL_POINTER,     ///<  Indicates that a null pointer is detected.
        STATUS_ERR_BAD_PARAMETER,    ///<  Indicates that a wrong parameter has been used in a function call.
        STATUS_ERR_INVALID_INDEX,    ///<  Indicates that an invalid index is detected.
        STATUS_ERR_MEM_ALLOC_FAILED, ///<  Indicates that a memory allocation failed.
        STATUS_ERR_INVALID_HANDLE,   ///<  Indicates that an invalid handle is detected.
        STATUS_ERR_INVALID_THREAD,   ///<  Indicates that an invalid thread is detected.
        STATUS_ERR_INVALID_SEM,      ///<  Indicates that an invalid semaphore is detected.
        STATUS_ERR_INVALID_MSGQ,     ///<  Indicates that an invalid message queue is detected.
        STATUS_ERR_UNKNOWN,          ///<  Indicates that an unknown error is detected.
    };

    enum class CfeBoardDiagStatus : std::uint32_t
    {
        STATUS_NOT_DETECTED,    ///<  The board is not detected.
        STATUS_BAD_CONF,        ///<  There is an error in the configuration.
        STATUS_NOT_CONFIGURED,  ///<  The board is not configured.
        STATUS_BAD_VOLTAGE,     ///<  Voltage issue on the board.
        STATUS_FAILURE_DETECTED ///<  General error on the board.
    };

    enum class edacAppErrc : std::uint32_t
    {
        CFG_ERROR_UPG,
        VOL_LOW_ERROR,
        SERIAL_N_ERROR,
        IMU_ERROR,
        COMPASS_ERROR,
        GPS_NOT_CALIBRATED_ERROR,
        CALIBRATION_ERROR,
        IMU_INITIALIZATION_ERROR
    };

    enum class edacSSLErrc : std::uint32_t
    {
        SSLBACKEND_NONE = 0,
        SSLBACKEND_OPENSSL = 1,
        SSLBACKEND_GNUTLS = 2,
        SSLBACKEND_NSS = 3,
        SSLBACKEND_OBSOLETE4 = 4,     /* Was QSOSSL. */
        SSLBACKEND_GSKIT = 5,
        SSLBACKEND_POLARSSL = 6,
        SSLBACKEND_WOLFSSL = 7,
        SSLBACKEND_SCHANNEL = 8,
        SSLBACKEND_DARWINSSL = 9,
        SSLBACKEND_AXTLS = 10,
        SSLBACKEND_MBEDTLS = 11,
        SSL_CONNECT_ERROR,
    };

    //template<> struct is_error_code_enum<edac::errc::edacErrc> : std::true_type {};
    //std::error_code make_error_code(edac::errc::edacErrc);
    class ErrorCodePrivate
    {
        public:

            struct ErrorDescription
            {
                std::uint32_t errorCode;
                std::string errorText;
                std::string severity;
                std::string recommendedAction;
                std::string rootCause;
                std::string service;
                std::string component;
            };

            ErrorCodePrivate();
            ErrorCodePrivate(const ErrorCodePrivate& orig) = delete;
            ErrorCodePrivate(ErrorCodePrivate&& orig) = delete;
            ErrorCodePrivate & operator=(const ErrorCodePrivate& orig) = delete;
            ErrorCodePrivate & operator=(ErrorCodePrivate && orig) = delete;
            virtual ~ErrorCodePrivate() = default;

        //const error_category & edac_category();

        private:
    };
}

namespace std
{
    // Tell the C++ 11 STL metaprogramming that enum edac::internal::edacErrc
    // is registered with the standard error code system
    template <>
    struct is_error_code_enum<cfs::edacl::errors::internal::edacErrc>
        : std::true_type
    {
    };
    template <>
    struct is_error_code_enum<cfs::edacl::errors::internal::edacAppErrc>
        : std::true_type
    {
    };
    template <>
    struct is_error_code_enum<cfs::edacl::errors::internal::edacSSLErrc>
        : std::true_type
    {
    };
}

#endif

