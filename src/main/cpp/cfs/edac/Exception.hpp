
#ifndef CFS_EDAC_EXCEPTION_HPP
#define CFS_EDAC_EXCEPTION_HPP

#include <exception>
#include <string>
#include <iostream>

#define ERROR_LOCATION  std::string ( "(" ) + std::string( __FILE__ ) + std::string ( ":" ) + std::to_string( __LINE__ ) + std::string ( ")" )
#define RAISE_ERROR( error )  throw Exceptions::prepare( error, __FILE__, __LINE__, __func__ std::strerror(error))

namespace cfs::edac
{

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

      Exception( int code = 0 );
      Exception( const Exception & orig );
      Exception & operator = ( const Exception & exc );
      virtual ~Exception();
      /*!
       * @brief Constructs an exeption with message and error code.
       */
      Exception( const std::string & msg, int code = 0 );
      /*!
       * @brief Constructor.
       * @param _method Mothodd s name raising the exception.
       * @param _message Excetion explanation.
       * @param _code Error code.
       * @throw std::runtime_error When socket could not be created.
       */
      Exception( const std::string & msg, const std::string & arg, int code = 0 );
      /*!
       * @brief Constructor.
       * @param _method Mothodd s name raising the exception.
       * @param _message Excetion explanation.
       * @param _code Error code.
       * @throw std::runtime_error When socket could not be created.
       */
      Exception( const std::string & msg, const Exception & nested, int code = 0 );
      /*!
       * @brief methodName Method raising the exception.
       */
      const std::string & methodName ();
      /*!
       * @brief message Message explaining the reason of exception.
       */
      const std::string & errorDescription ();
      /*!
       * @brief errorCode Error code corresponding to errno.h values.
       * @return
       */
      int errorCode () const;
      /*!
       * @brief Gets the nested exception which caused this exception.
       * @return The nested exception, or <code>NULL</code> if there is none.
       */
      const Exception * cause () const throw ( );
      /*!
       * @brief Return a description of the error
       * @return Pointer to a string containing the error message
       */
      const char * what () const throw ( );
      /*!
       * @brief Return the error location (file + line + function)
       * @return String containing the error location
       */
      virtual const char * where () const throw ( );
      /*!
       * @brief Return the error summary description
       * @return String containing the error location
       */
      virtual std::string summary () const;
      virtual std::string stackTrace () const;

    protected:

      //explicit Exception(const std::string & message);
      explicit Exception(std::terminate_handler handler);
 
    private:

      void create( std::size_t nSize);

      //std::shared_ptr< std::string > m_message; ///< Error message
      const std::string m_who;             ///< name of function throwing exception
      const std::string m_where;           ///< source:line info
      const std::string m_reason;          ///< optional, provides context-specific reason
      std::terminate_handler m_oldHandler; ///< old terminate handler. We need it in the destructor.
      std::string m_stackTrace;
      std::string m_message;        ///< Error message.
      std::string m_location;       ///< Location of the error : file, line and procedure)
      std::int32_t m_code;                   ///< Error code
    };

    std::ostream & operator << ( std::ostream & out, const Exception & ex)
    {
        out << "CFS Exception: " << ex.what();
        return out;
    }

    /*!
     * @biref Signals an error condition in a program by throwing an
     *        <code>Exception</code> with the specified message.
     */
    [[noreturn]] void error ( const std::string & msg )
    {
        throw Exception( msg );
    }
}

#endif


