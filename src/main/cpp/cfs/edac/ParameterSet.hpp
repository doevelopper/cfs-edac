

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

            void add(const std::string line);
            void addParam(const std::string param, const std::string value = NULL, bool atStart = false);
            bool isSet(const std::string key) const;
            template<typename T>
            T get(const std::string key) const;
            const std::string& get(const std::string key) const;
            std::string getParameters () const;
            void erase(const std::string key);

        private:

            std::map<std::string, std::string> m_values;
            std::vector<std::string> m_params;
    }
}

#endif

