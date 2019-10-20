

#ifndef CFS_EDAC_ERRORHANDLER_HPP
#define CFS_EDAC_ERRORHANDLER_HPP

namespace cfs::edac
{
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

virtual void exception (const std::exception & exc);
/*!
 * @brief Invokes the currently registered Error.
 */

// static void handle (const Exception & exc);
/*!
 * @brief Invokes the currently registered Error.
 */

static void handle (const std::exception & exc);
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
Beep Generates simple tones on the speaker.
CaptureStackbackTrace Captures a stack back trace by walking up the stack and recording the information for each frame.
FatalAppExit Displays a message box and terminates the application when the message box is closed.
FlashWindow Flashes the specified window one time.
FlashWindowEx Flashes the specified window.
FormatMessage Formats a message string.
GetErrorMode Retrieves the error mode for the current process.
GetLastError Retrieves the calling thread
's last-error code value.
GetThreadErrorMode  Retrieves the error mode for the calling thread.
MessageBeep     Plays a waveform sound.
RtlLookupFunctionEntry  Searches the active function tables for an entry that corresponds to the specified PC value.
RtlNtStatusToDosError   Retrieves the system error code that corresponds to the specified NT error code.
RtlPcToFileHeader   Retrieves the base address of the image that contains the specified PC value.
RtlUnwind   Initiates an unwind of procedure call frames.
RtlUnwind2  Initiates an unwind of procedure call frames.
RtlUnwindEx     Initiates an unwind of procedure call frames.
RtlVirtualUnwind    Retrieves the invocation context of the function that precedes the specified function context.
SetErrorMode    Controls whether the system will handle the specified types of serious errors, or whether the process will handle them.
SetLastError    Sets the last-error code for the calling thread.
SetLastErrorEx  Sets the last-error code for the calling thread.
SetThreadErrorMode  Controls whether the system will handle the specified types of serious errors or whether the calling thread will handle them.





