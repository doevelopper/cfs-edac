

#ifndef CFS_EDAC_NOTFOUNDERROR_HPP
#define CFS_EDAC_NOTFOUNDERROR_HPP

namespace cfs::edac
{

    template< class T >
    class NotFoundError : public std::runtime_error
    {
        public:

            NotFoundError(const std::string& message, const T& value) throw();
            ~NotFoundError() throw();
/*!
 * @brief Returns a copy of the value that could not be found.
 */
            const T& get_value(void) const throw();

        private:

            T m_value;
    }

}
#endif

