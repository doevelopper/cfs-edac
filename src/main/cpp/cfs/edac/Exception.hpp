

#ifndef CFS_EDAC_EXCEPTION_HPP
#define CFS_EDAC_EXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

#include <cfs/edar/LoggingService.hpp>
#include <cfs/edac/Location.hpp>
//#include <cfs/edac/Export.hpp>


#define RAISE_ERROR( error )  throw Exceptions::prepare( error, __FILE__, __LINE__, __func__ std::strerror(error))
#define ERROR_LOCATION std::string ( "(" ) + std::string( __FILE__ ) + std::string ( ":" ) + std::to_string( \
        __LINE__ ) + std::string ( ")" )

namespace cfs::edac
{

    /*!
     * @brief Base class for every exception thrown in <>.
     *        C - Computational problem
     *        H - Hardware problem
     *        I - I/O and file problem
     *        L - Library function problem
     *        D - Data input problem
     *        R - Return value problem: function or procedure call
     *        E - External user/client problem  (in embedded systems this may include control network exceptions)
     *        N - Null pointer or memory problems
     */

	class Exception : public std::exception
	{

		LOG4CXX_DECLARE_STATIC_LOGGER

        struct Mode
        {
            enum _v
            {
                Ignore,
                Throw,
                Trace
            };
        };
        /*!
         *  @brief  Wrapper class to define a different terminate handler. The terminate
         *          handler is the function that will be called by the runtime system when
         *          exception handling must be abandoned.
         */
        class TerminateHandler
        {
            /*!
             * @brief Options that set the behavior of this class:
             */
            enum TerminateAction
            {
                NOTHING = 0x0,           /*! Do nothing. Don't even install termination handlers. */
                BACKTRACE = 0x1,         /*! Load gdb and get a stack dump using gdb bt command.  */
                WEAK_BACKTRACE = 0x2,    /*! Get backtrace using glibc::backtrace. */
                TRAP_MANY_SIGNALS = 0x4, /*! Trap a lot of signals not normally trapped. */
                USE_CURRENT = 0x8,       /*! Inherit values already existing in previous handlers. */
                LOCAL_VARIABLES = 0x10   /*! Attempt to additionaly display local variables. */
            };

            public:

                /*!
                 * @brief  Constructor. Register @a handler as the current terminate handler.
                 */
                explicit TerminateHandler( std::terminate_handler handler )
                    : m_oldHandler(std::set_terminate( handler ))
                {
                    //oldHandler = std::set_terminate( handler );
                }

                /*!
                 * @brief Destructor. Unregister the current terminate handler; reset to
                 *        previous handler.
                 */
                virtual ~TerminateHandler()
                {
                    std::set_terminate( m_oldHandler );
                }

            private:

                /*!
                 * @brief  This is the old terminate handler. We need it in the destructor.
                 */
                std::terminate_handler m_oldHandler;
        };

	 public:
		Exception() = delete;
		Exception(const Exception&) noexcept = default;
		Exception(Exception&&) noexcept = default;
		Exception& operator=(const Exception&) noexcept = default;
		Exception& operator=(Exception&&) noexcept = default;
		virtual ~Exception();

		explicit Exception(std::int32_t code );

		/*!
		 * @brief Constructs an exeption with message and error code.
		 */
		explicit Exception( const std::string & msg, std::int32_t code );
		// explicit Exception(const std::string & who, const std::string & what = std::string(""));
            /*!
             * @brief Constructor.
             * @param _method Mothodd s name raising the exception.
             * @param _message Excetion explanation.
             * @param _code Error code.
             * @throw std::runtime_error When socket could not be created.
             */
        explicit Exception( const std::string & msg, const std::string & what = std::string(""), std::int32_t code = 0 );
            /*!
             * @brief Constructor.
             * @param _method Mothodd s name raising the exception.
             * @param _message Excetion explanation.
             * @param _code Error code.
             * @throw std::runtime_error When socket could not be created.
             */

        Exception( const std::string & msg, const Exception & nested, int code = 0 );

		/*!
		 * @brief Return a description of the error
		 * @return Pointer to a string containing the error message
		 */
		const char* what() const noexcept override;
		/*!
		 * @brief Return the error location (file + line + function)
		 * @return String containing the error location
		 */
		virtual const char * where () const noexcept ;
		const cfs::edac::Location& location() const noexcept;
		const std::string& message() const noexcept ;
		/*!
		 * @brief Retrieve the stack trace trace of process
		 *
		 * @return String containing the procces
		 */
		virtual std::string stackTrace () const;
		/*!
		 * @brief message Message explaining the reason of exception.
		 */
		const std::string & errorDescription ();
		/*!
		 * @brief errorCode Error code corresponding to errno.h values.
		 * @return
		 */
		[[nodiscard]]
		std::int32_t errorCode () const;
		void errorCode (const std::int32_t & error);
		//! Link exception with source location
		template<class T>
		friend T&& operator+(const Location & location, T&& instance)
		{ instance.m_location = location; return std::forward<T>(instance); }
		/*!
		 * @brief methodName Method raising the exception.
		 */
		const std::string & methodName ();
/*
		std::string const& operator()() const {}
		void operator()(std::string const& newName) {}
*/
	 protected:
        explicit Exception(std::terminate_handler handler);
	 private:

		//std::shared_ptr< std::string > m_message; ///< Error message
		const std::string      m_who;        ///< name of function throwing exception
		const std::string      m_where;      ///< source:line info
		const std::string      m_reason;     ///< optional, provides context-specific reason
		std::terminate_handler m_oldHandler; ///< old terminate handler. We need it in the destructor.
		std::string            m_stackTrace;
		std::string            m_message;    ///< Error message.
		cfs::edac::Location    m_location;   ///< Location of the error : file, line and procedure)
		std::int32_t           m_code;       ///< Error code

	};
    /*!
     * @biref Signals an error condition in a program by throwing an
     *        <code>Exception</code> with the specified message.
     */
    [[noreturn]] void reportError ( const std::string & msg )
    {
        throw cfs::edac::Exception( msg );
    }

    std::ostream & operator << ( std::ostream & out, const Exception & ex)
    {
        auto c = ex.errorCode();
        out << "CFS Exception:  " << ex.what();

        /*
           out << "- category:     " << c.category().name();
           out << "- value:        " << c.value();
           out << "- msg:          " << c.message();
           out << "- def category: " << c.default_error_condition().category().name();
           out << "- def value:    " << c.default_error_condition().value();
           out << "- def msg:      " << c.default_error_condition().message()
         */
        return (out);
    }

    class NotImplemented : public std::logic_error
    {
        public:

            explicit NotImplemented(const std::string &message)
                : std::logic_error(message)
            {
            }
    };

    class NumericalProblem : public std::runtime_error
    {
        public:

            explicit NumericalProblem(const std::string &message)
                : std::runtime_error(message)
            {
            }
    };

    class MaterialLawProblem : public NumericalProblem
    {
        public:

            explicit MaterialLawProblem(const std::string &message)
                : NumericalProblem(message)
            {
            }
    };

    class LinearSolverProblem : public NumericalProblem
    {
        public:

            explicit LinearSolverProblem(const std::string &message)
                : NumericalProblem(message)
            {
            }
    };

    class BadDependency : public ::std::logic_error
    {
        public:

            BadDependency(const ::std::string &arg)
                : std::logic_error(arg)
            {
            }
    };

    class InvalidResult : public ::std::runtime_error
    {
        public:

            InvalidResult(const ::std::string &arg)
                : std::runtime_error(arg)
            {
            }
    };

    class TooManyIterations : public NumericalProblem
    {
        public:

            explicit TooManyIterations(const std::string &message)
                : NumericalProblem(message)
            {
            }
    };

    class IOError : public std::runtime_error
    {
        /// Error can be specified more precisely in constructor if desired
        explicit IOError(const char *s = "I/O error")
            : std::runtime_error(s)
        {
        }
    };

    class notImplementedException : public std::exception
    {
        public:

            notImplementedException(const char * message)
                : m_message(message)
            {
            }

            notImplementedException()
                : m_message("not implemented")
            {
            }

            virtual const char* what() const noexcept override
            {
                return m_message;
            }

            virtual ~notImplementedException()  noexcept
            {
            }

        private:

            const char * m_message;
    };

	class ArgumentException : public Exception
	{
	public:
		using Exception::Exception;
	};

	//! Runtime exception
	class RuntimeException : public Exception
	{
	public:
		using Exception::Exception;
	};

	//! Security exception
	class SecurityException : public Exception
	{
	public:
		using Exception::Exception;
	};

}

#endif
