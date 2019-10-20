

/*!
 * @file
 * @brief Common source of API return status codes and erros management.
 */

#ifndef EDAC_PRIVATE_ERRORCODEPRIVATE_HPP
#define EDAC_PRIVATE_ERRORCODEPRIVATE_HPP
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

 |        | Sev | Res | Serv  |  Mission  Defined |       Code status               |
 |:------:|:---:|:---:|-------|:-----------------:|:-------------------------------:|
 | Class  | 3 3 | 2 2 | 2 2 2 | 2 2 2 2 2 1 1 1 1 | 1 1 1 1 1 1 - - - - - - - - - - |
 | Index  | 1 0 | 9 8 | 7 6 5 | 4 3 2 1 0 9 8 7 6 | 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 |


 |        | Sev   |  Res  |   Serv   |      Mission  Defined      |                       Code                      |
 |:------:|:-----:|:-----:|:--------:|:--------------------------:|:-----------------------------------------------:|
 | Class  | 3  3  | 2  2  | 2  2  2  | 2  2  2  2  2  1  1  1  1  | 1  1  1  1  1  1  -  -  -  -  -  -  -  -  -  -  |
 | Index  | 1  0  | 9  8  | 7  6  5  | 4  3  2  1  0  9  8  7  6  | 5  4  3  2  1  0  9  8  7  6  5  4  3  2  1  0  |
 | 32Bits | 32 31 | 30 29 | 28 27 26 | 25 24 23 22 21 20 19 18 17 | 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 |


 |    |    Severity   |    |    |    Reserved   |    |     |        ServiceID        |
 |----|:-------------:|    |----|:-------------:|    |:---:|:-----------------------:|
 | 00 |    Success    |    | 00 |    -------    |    | 000 |    Not a cFE Service    |
 | 01 | Informational |    | 01 |    -------    |    | 001 |    Events Services      |
 | 10 |     Error     |    | 10 |    -------    |    | 010 |    Executive Services   |
 | 11 |    Critical   |    | 11 |    -------    |    | 011 |    File Services        |
 | 100 |    OS API Services      |
 | 101 |    Software Bus Services|
 | 110 |    Tables Services      |
 | 111 |    Time Services        |

 |           |                                      Mission,Defined                                     |
 |:---------:|:----------------------------------------------------------------------------------------:|
 | 000000000 | Used to classify error codes   related  to mission specific library function calls, etc. |


 |                  |                                      Error codes                                         |
 |:----------------:|:----------------------------------------------------------------------------------------:|
 | 0000000000000000 | Used to classify error codes   related  to mission specific library function calls, etc. |
 */

#include <clocale>
#include <cstdint>
#include <system_error>
#include <type_traits>
namespace edac
{
namespace errc
{
using HRESULT = std::uint32_t;
HRESULT EDAC_SUCCESS = (std::uint32_t)(0ULL);
HRESULT EDAC_ERROR = (!EDAC_SUCCESS);

enum class edacErrorPage : std::uint32_t
{
	OS_ERRORS_PAGE_SIZE = 0x0000EA60,
	OS_START_ERROR = (0x00004E20),
	OS_START_USER_ERROR = (0x0001D4C0),
	OS_START_APPLICATION_ERROR = (0x0001D4C0),
	OS_START_SYSTEM_ERROR = (0x000AFC80),
};

enum class edacSeverity : std::uint32_t
{
	CFE_SEVERITY_BITMASK = (0xc0000000L),
	CFE_SEVERITY_SUCCESS = (0x00000000L),
	CFE_SEVERITY_INFO = (0x40000000L),
	CFE_SEVERITY_ERROR = (0xc0000000L),
	MAV_SEVERITY_EMERGENCY = 0,       /* System is unusable. This is a "panic" condition. | */
	MAV_SEVERITY_ALERT = 1,           /* Action should be taken immediately. Indicates error in non-critical
			                     systems. | */
	MAV_SEVERITY_CRITICAL = 2,        /* Action must be taken immediately. Indicates failure in a primary system. |
			                   */
	MAV_SEVERITY_ERROR = 3,           /* Indicates an error in secondary/redundant systems. | */
	MAV_SEVERITY_WARNING = 4,         /* Indicates about a possible future error if this is not resolved within a
			                     given timeframe. Example would be a low battery warning. | */
	MAV_SEVERITY_NOTICE = 5,          /* An unusual event has occured, though not an error condition. This should be
			                     investigated for the root cause. | */
	MAV_SEVERITY_INFO = 6,            /* Normal operational messages. Useful for logging. No action is required for
			                     these messages. | */
	MAV_SEVERITY_DEBUG = 7,           /* Useful non-operational messages that can assist in debugging. These should
			                     not occur during normal operation. | */
	MAV_SEVERITY_ENUM_END = 8
};

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
	TIME_OUT_OF_RANGE = (0xce000002L),
	TBL_NOT_IMPLEMENTED = (0xcc00ffffL),
	INFO_RECOVERED_TBL = (0x4c000027L),
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
	ERROR_ABORTED_BY_CALLBACK
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
	SSLBACKEND_OBSOLETE4 = 4,      /* Was QSOSSL. */
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
}

namespace std
{
// Tell the C++ 11 STL metaprogramming that enum edac::errc::edacErrc
// is registered with the standard error code system
template <>
struct is_error_code_enum<edac::errc::edacErrc>
	: std::true_type
{
};
template <>
struct is_error_code_enum<edac::errc::edacAppErrc>
	: std::true_type
{
};
template <>
struct is_error_code_enum<edac::errc::edacSSLErrc>
	: std::true_type
{
};
}

#endif

