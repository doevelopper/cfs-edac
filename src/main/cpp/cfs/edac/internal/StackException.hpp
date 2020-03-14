

#ifndef CFS_EDAC_INTERNAL_STACKEXCEPTION_HPP
#define CFS_EDAC_INTERNAL_STACKEXCEPTION_HPP

#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <stdexcept>
#include <memory>
#include <log4cxx/logger.h>

namespace cfs::edac::internal
{
template <class T>
class StackException
{
    public:

        using valueType = T;
        using sizeType = std::size_t;

        explicit StackException() noexcept;
        explicit StackException(sizeType capacity);
        StackException(const StackException&) = delete;
        StackException(StackException&&) = delete;
        virtual ~StackException() noexcept;

        template <class ... Args>
        void constructAt(sizeType pos, Args&& ... args)
        {
            LOG4CXX_ASSERT(logger,pos < m_capacity,"pos < m_capacity");
            new (&m_data[pos]) T(std::forward<Args>(args)...);
        }

    protected:

        void swap(StackException<T>&);

        T*       m_data;
        sizeType m_capacity;
        sizeType m_size;

    private:

        /*!
         * @brief Class logger.
         */
        static log4cxx::LoggerPtr logger;
};
}
#endif

