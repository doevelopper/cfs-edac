

#include <map>
#include <array>   /* for std::array */
#include <cassert> /* for assert() */
#include <cerrno>  /* for E*, errno */
#include <cstdarg> /* for va_*() */
#include <cstdio>  /* for std::snprintf() */
#include <cstring> /* for stpncpy() */
#include <cfs/edac/Error.hpp>

using namespace cfs::osgi::edac;

Error::Error()
    : m_codeMask( ~0 )
    , m_facilityMask( ~0 )
    , m_ErrorCode( ~0 )
    , m_ErrorFacility( ~0 )
{
    // this->m_codeMask >>= 16;
    // this->m_facilityMask >>= 21;
    // this->m_facilityMask <<= 16;
    // this->m_ErrorCode = (/*hresult*/ & this->m_codeMask);;
    // this->m_ErrorFacility = (/*hresult*/ & this->m_facilityMask) >> 16;
}

const char *
Error::what () const throw ( )
{
    return ( m_message.c_str());
}

const char *
Error::where () const throw ( )
{
    return ( m_location.c_str());
}

void
Error::throw_error ()
{
    throw_error( errno, nullptr, nullptr );
}

void
Error::throw_error (
    const char * const origin,
    const char * const format,
    ...
    )
{
    va_list args;


    va_start( args, format );
    throw_error( errno, origin, format, args );
    va_end( args );   /* never reached */
}

void
Error::throw_error (
    const int code,
    const char * const origin,
    const char * const format,
    va_list args
    )
{
    static thread_local std::array < char, 4096 > buffer;

    // switch (auto res = severity(); res.second)
    auto res = severity();


    switch ( /*res.second*/ code )
    {
        // case cfs::STATUS_OK:
        // break;
        // case cfs::STATUS_FAILURE:
        // break;
        // case cfs::STATUS_BUSY:
        // break;
        // default:
        // break;
    }

    switch ( code )
    {
    }
}

// std::pair<size_t err, cfs::osgi::edac::Error::CfsErrorSeverity>
// cfs::osgi::edac::Error::severity()
// {
//
// }
// std::pair<size_t err, cfs::osgi::edac::Error::CfeServiceIdentifiers>
// cfs::osgi::edac::Error::serviceId()
// {
//
// }
//
// std::pair<size_t err, cfs::osgi::edac::Error::CfeOperationStatus>
// cfs::osgi::edac::Error::operationStatus()
// {
//
// }

