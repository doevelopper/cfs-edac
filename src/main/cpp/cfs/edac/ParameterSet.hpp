

#ifndef CFS_EDAC_PARAMETERSET_HPP
#define CFS_EDAC_PARAMETERSET_HPP

#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <stdexcept>

namespace cfs::edac
{
    class ParameterSet
    {
public:

/*!
 * @brief
 *
 * @param line
 */
        void add(const std::string line);

/*!
 * @brief
 *
 * @param param
 * @param value
 * @param atStart
 */
        void addParam(const std::string param, const std::string value = NULL, bool atStart = false);

/*!
 * @brief
 *
 * @param key
 * @return true
 * @return false
 */
        bool isSet(const std::string key) const;

/*!
 * @brief
 *
 * @tparam T
 * @param key
 * @return T
 */
        template<typename T>
        T get(const std::string key) const;

/*!
 * @brief
 *
 * @param key
 * @return const std::string&
 */
        const std::string& get(const std::string key) const;

/*!
 * @brief Get the Parameters object
 *
 * @return std::string
 */
        std::string getParameters () const;

/*!
 * @brief
 *
 * @param key
 */
        void erase(const std::string key);

private:

        std::map<std::string, std::string> m_values;
        std::vector<std::string> m_params;
    }
}

#endif

