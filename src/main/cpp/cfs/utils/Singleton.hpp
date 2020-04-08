
#ifndef CFS_UTILS_SINGLETON_HPP
#define CFS_UTILS_SINGLETON_HPP

namespace cfs::utils
{

template <typename T>
class Singleton
{
    friend T;

public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;

    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton &&) = delete;

    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

private:
    Singleton() noexcept = default;
    ~Singleton() noexcept = default;
};

}

#endif

