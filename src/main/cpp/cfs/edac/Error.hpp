

// class error_code;
// class error_condition;
// class error_category;
// class system_error;
// std::error_condition ec;
// ec = std::errc::not_enough_memory;
// assert(ec.value() == static_cast<int>(std::errc::not_enough_memory));
// assert(ec.category() == std::generic_category());
// const std::error_category& e_cat = std::generic_category();
// std::error_condition e_cond = e_cat.default_error_condition(static_cast<int>(std::errc::not_a_directory));
// assert(e_cond.category() == e_cat);
// assert(e_cond.value() == static_cast<int>(std::errc::not_a_directory));

#ifndef CFS_OSGI_EDAC_ERROR_HPP
#define CFS_OSGI_EDAC_ERROR_HPP

#include <cerrno>
#include <cstdint>
#include <string>
#include <exception>
#include <system_error>
#include <vector>

#define ERRMSG  std::cerr << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "(): "

/*
 *
    https://docs.microsoft.com/en-us/windows-hardware/drivers/kernel/defining-new-ntstatus-values
 *
 |        | Sev   |  Res  |   Serv   | Mission Defined /Facility  |                       Code                      |
 |:------:|:-----:|:-----:|:--------:|:--------------------------:|:-----------------------------------------------:|
 | Class  | 3  3  | 2  2  | 2  2  2  | 2  2  2  2  2  1  1  1  1  | 1  1  1  1  1  1  -  -  -  -  -  -  -  -  -  -  |
 | Index  | 1  0  | 9  8  | 7  6  5  | 4  3  2  1  0  9  8  7  6  | 5  4  3  2  1  0  9  8  7  6  5  4  3  2  1  0  |
 | Bits   | 32 31 | 30 29 | 28 27 26 | 25 24 23 22 21 20 19 18 17 | 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 |

 |     |        ServiceID        |     |    |    Severity   |      |    |    Reserved   |
 |:---:|:-----------------------:|     |----|:-------------:|      |----|:-------------:|
 | 000 |    Not a cFE Service    |     | 00 |    Success    |      | 00 |    -------    |
 | 001 |    Events Services      |     | 01 | Informational |      | 01 |    -------    |
 | 010 |    Executive Services   |     | 10 |     Error     |      | 10 |    -------    |
 | 011 |    File Services        |     | 11 |    Critical   |      | 11 |    -------    |
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


   Severity    Meaning
    00      Informational: This level is used to convey information to the user. No error has occurred. Informational
 |messages are listed only when the FLAG (00) option is specified.
    10      Warning: This level indicates that an error was detected but is not serious enough to interfere with the
 |running of the program.
    20      Error: This level indicates that an error was made, but the compiler is taking a recovery that might yield
 |the desired code.
    30      Severe Error: This level indicates that a serious error was detected. Compilation is completed, but the
 |module object is not created and running of the program cannot be attempted.
    40      Unrecoverable: This level usually indicates a user error that forces termination of processing.
    50      Unrecoverable: This level usually indicates a compiler error that forces termination of processing.
    99      Action: Some manual action is required, such as entering a reply, changing printer forms, or replacing
 |diskettes.

 *
 *
 */

//#define CFS_DECLARE( type )  type
//#define CFS_SUCCESS  ( 0x00000000L )    //! no error.
//#define CFE_ERROR    ~( CFS_SUCCESS )   //! error.

/*!
 * @brief  Macro for generating bit masks using bit index from the spec.
 */
//#define CFS_BIT_MASK( bit_index, field_bit_count ) ( ( 1 << (( field_bit_count ) - 1 )) >> ( bit_index ) )

namespace cfs::edac
{
    /*!
     * @brief Type for specifying an error or status code.
     */
    using cfs_status_t = std::int8_t;
    using HRESULT = std::uint32_t;

    enum CfsError : std::uint32_t
    {
        LARGE_VALUE = 0x0e000000UL,
        VALUE = 0x0e000000UL,
        LARGEVALUE = 0x0e000000UL,
        LARGE = 0x0e000000UL
    };

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

    enum class CfeOperationStatus : std::uint32_t
    {
        STATUS_OK = CFS_SUCCESS,              ///< Operation has completed successfully.
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
    };

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

    class Exception;

    class Error : public std::exception
    {
        public:

            /*!
             * @brief Constructs a new error with null as its detail message.
             */
            Error() noexcept( false );
            /*!
             * @brief Constructs a new error with null as its detail message.
             */
            Error( std::string & message );
            /*!
             * @brief Constructs a new error with the specified detail message and cause.
             */
            Error( std::string & message, int code )  noexcept( false );
            /*!
             * @brief Constructs a new error with the specified detail message, cause,
             *        suppression enabled or disabled, and writable stack trace enabled or disabled.
             * @param[in,out] message - The detail message.
             * @param[in] enableSuppression  - Whether or not suppression is enabled or disabled.
             * @param[in] writableStackTrace   - Whether or not the stack trace should be writable.
             */
            Error( std::string & message, bool enableSuppression,  bool writableStackTrace ) noexcept( false );
            Error( const std::error_code code ) noexcept;
            Error( const std::error_code code, const char * const what ) noexcept;
            Error( const int code, const std::error_category & category ) noexcept;
            Error( const int code ) noexcept;
            Error( const int code, const std::error_category & category, const char * const what) noexcept;
            /*!
             * @brief Destructor.
             */
            virtual ~Error() = default;

            /*!
             * @brief Return a description of the error
             * @return Pointer to a string containing the error message
             */
            virtual const char * what () const throw ( );

            /*!
             * @brief Return the error location (file + line + function)
             * @return String containing the error location
             */
            virtual const char * where () const throw ( );
            /*!
             * @brief Registers the given handler as the current error handler.
             * @return The previously registered handler.
             */
            static Error * set ( Error * handler );
            /*!
             * @brief Returns a pointer to the currently registered.
             */
            static Error * get ();
            static int lastErrno ();
            static const char * lastErrmsg ();
            /*!
             *
             */
            std::system_error systemError ( int e, const char * msg )
            {
                return std::system_error( std::error_code( e, std::system_category()), msg );
            }

            /*!
             *
             */
            std::system_error systemError ( int e, const std::string & msg)
            {
                return systemError( e, msg.c_str());
            }

            /*!
             *
             */
            std::system_error systemError ( const std::string & msg )
            {
                return systemError( errno, msg );
            }

            /*!
             *
             */
            std::system_error systemError ( const char * msg )
            {
                return systemError( errno, msg );
            }

            /*!
             *
             */
            std::error_code systemErrorCode ( int code )
            {
                return ( std::error_code( code, std::system_category()));
            }

            /*!
             *
             */
            std::error_code genericErrorCode ( int code )
            {
                return ( std::error_code( code, std::generic_category()));
            }

            /*!
             *
             */
            std::error_condition systemErrorConditionCode ( int code )
            {
                return ( std::error_condition( code, std::system_category()));
            }

            /*!
             *
             */
            std::error_condition genericErrorConditionCode ( int code )
            {
                return ( std::error_condition( code, std::generic_category()));
            }

            /*!
             *
             */
            auto systemErrorCode ()
            {
                return ( systemErrorCode( errno ).default_error_condition());
            }

            /*!
             *
             */
            auto genericErrorCode ()
            {
                return ( genericErrorCode( errno ).default_error_condition());
            }

            [[noreturn]] void makeErrorCode(std::uint32_t errc)
            {
                std::make_error_code(std::errc::timed_out);
            }

            [[noreturn]] void makeAndThrowErrorCode()
            {
                throw std::system_error(std::make_error_code(std::errc::timed_out));
            }

            void throw_error [[noreturn]]();
            void throw_error [[noreturn]]( const char * origin, const char * format = nullptr, ... );
            void throw_error [[noreturn]]( int code );
            void throw_error [[noreturn]]( int code, const char * origin, const char * format = nullptr, ... );
            void throw_error [[noreturn]]( int code, const char * origin, const char * format, va_list args );

        protected:

            /*!
             * @brief Returns the default Error handler.
             */
            static Error * defaultHandler ();
            /*!
             * @brief Utility function translating numeric error code to string.
             */
            static std::string getErrorDescription ( int errorCode );
            std::pair < std::size_t /* bytes */, CfsErrorSeverity >  severity ();
            std::pair < std::size_t /* bytes */, CfeServiceIdentifiers > serviceId ();
            std::pair < std::size_t /* bytes */, CfeOperationStatus > operationStatus ();

            using ErrorMessageMap = std::map < std::string, CfsErrorSeverity >;

            std::map < std::uint32_t, std::string > const errorsList
            {
                { 0, "No Error" },
                { 1, "Wrong ID" },

                /* ... */
                { 75000, "Unknown" },
            };

            std::string const & getErrorString ( int errorId )
            {
                auto it = errorsList.find( errorId );

                return it != errorsList.end() ? it->second : errorsList.find( 2500 )->second;
            }

        private:

            std::string m_message;  ///< Error message
            std::string m_location; ///< Location of the error (file, line and function)
            std::error_code m_ec;
            std::vector < std::pair < std::string, std::string > > errorProperties;
            std::uint32_t m_codeMask;
            std::uint32_t m_facilityMask;
            std::uint32_t m_ErrorCode;
            std::uint32_t m_ErrorFacility;
    };
}

#endif

