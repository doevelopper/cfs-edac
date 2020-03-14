

#ifndef CFS_EDAC_INTERNAL_STACK_HPP
#define CFS_EDAC_INTERNAL_STACK_HPP

#include <cfs/edac/internal/StackException.hpp>

namespace cfs::edac::internal
{
template <class T>
class Stack : private StackException<T>
{
    using StackException<T>::m_size;
    using StackException<T>::m_capacity;
    using StackException<T>::m_data;
    using StackException<T>::swap;
    using StackException<T>::constructAt;

    public:

        using valueType = T;
        using reference = T&;
        using constReference = const T&;
        using sizeType = std::size_t;

        Stack() noexcept;
        virtual ~Stack() noexcept;
        Stack(const Stack&) noexcept(std::is_nothrow_copy_constructible<T>::value);
        Stack& operator=(Stack) noexcept(std::is_nothrow_copy_constructible<T>::value);

        stack(Stack&&) noexcept(std::is_nothrow_move_constructible<T>::value);
        Stack& operator=(Stack&&) noexcept(std::is_nothrow_move_constructible<T>::value);

        sizeType size() const noexcept;
        sizeType capacity() const noexcept;
        bool empty() const noexcept;

        reference top();
        constReference top() const;

        void push(const T&);
        template <class ... Args> void emplace(Args&& ...);
        T pop();
        void reserve(sizeType);

    private:

        Stack(sizeType capacity);
        /*!
         * @brief Class logger.
         */
        static log4cxx::LoggerPtr logger;
};
}
#endif

