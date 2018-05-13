
#ifndef CFS_EDAC_ERRORHANDLER_HPP
#define CFS_EDAC_ERRORHANDLER_HPP

namespace cfs::edac
	class ErrorHandler
	{
    public:

        ErrorHandler();
		/*!
		 * @brief Move constructor
		 */
        ErrorHandler( const ErrorHandler & ) = default;
		/*!
		 * @brief Move constructor
		 */
        ErrorHandler( ErrorHandler && ) = default;
		/*!
		 * @brief Copy assignment operator
		 */
        ErrorHandler & operator= ( const ErrorHandler & ) & = default;
		/*!
		 * @brief Move assignment operator
		 */
        ErrorHandler & operator= ( ErrorHandler && ) & = default;
		/*!
		 * @brief Receive notification of a warning.
		 */
        virtual void onWarning ( /*const Exception& exc*/ ) = 0;
		/*!
		 * @brief Receive notification of a recoverable error(system is in error conditions).
		 */
        virtual void error ( /*const Exception& exc*/ ) = 0;
		/*!
		 * @brief Receive notification of a non-recoverable error.
		 */
        virtual void fatalError ( /*const Exception& exc*/ ) = 0;
		/*!
		 * @brief Receive notification of a critical conditions.
		 */
        virtual void criticalError ( /*const Exception& exc*/ ) = 0;
		/*!
		 * @brief Receive notification that an action must be taken immediately.
		 */
        virtual void alertError ( /*const Exception& exc*/ ) = 0;
		/*!
		 * @brief Receive notification that system is unusable.
		 */
        virtual void emergencyError ( /*const Exception& exc*/ ) = 0;

        virtual void dispatchCleanup () = 0;
		/*!
		 * @brief Called when a Exception (or a subclass) caused the thread to terminate.
		 */

		// virtual void exception (const Exception & exc);
		/*!
		 * @brief Called when a std::exception (or a subclass) caused the thread to terminate.
		 */

		// virtual void exception (const std::exception & exc);
		/*!
		 * @brief Invokes the currently registered Error.
		 */

		// static void handle (const Exception & exc);
		/*!
		 * @brief Invokes the currently registered Error.
		 */

		// static void handle (const std::exception & exc);
		/*!
		 * @brief Receive notification of a warning.
		 */

		// virtual void onWarning () = 0;
		/*!
		 * @brief Receive notification of a recoverable error(system is in error conditions).
		 */

		// virtual void error () = 0;
		/*!
		 * @brief Receive notification of a non-recoverable error.
		 */

		// virtual void fatalError () = 0;
		/*!
		 * @brief Receive notification of a critical conditions.
		 */

		// virtual void criticalError () = 0;
		/*!
		 * @brief Receive notification that an action must be taken immediately.
		 */

		// virtual void alertError () = 0;
		/*!
		 * @brief Receive notification that system is unusable.
		 */

		// virtual void emergencyError () = 0;

		private:

        virtual ~ErrorHandler() = default;
	};
}
#endif
