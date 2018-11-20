

#ifndef CFS_EDACL_OBJECT_HPP
#define CFS_EDACL_OBJECT_HPP

namespace cfs::edacl
{
#include <utility>
#include <typeinfo>
    class Object
    {
        class None
        {
            public:

                None();
                virtual ~None();
                virtual const std::type_info &type () = 0;
                virtual None * duplicate () const = 0;
                virtual bool eq (Object &) = 0;
        };

        template < class T >
        class Data : public None
        {
            public:

                Data();
                virtual ~Data();
                Data(const T & value);
                const std::type_info &type ();
                Data * duplicate () const;
                bool eq (Object &Obj);
                T var;
        };

        public:

            Object();
            virtual ~Object();
            template < typename T >
            Object(const T & value);
            Object(const Object & Obj);
            const std::type_info &type ();

            Object &operator = (Object &rhs)
            {
                none = rhs.none->duplicate();

                return *this;
            }

            Object &swap (Object &rhs)
            {
                std::swap(*this, rhs);

                return *this;
            }

            template < typename T >
            Object &operator = (const T & value)
            {
                if (this != &value)
                {
                    none = new Data<T>(value);
                }

                return *this;
            }

            //    Object &operator=(Object & rhs)
            //    {
            //       // none = rhs.none->duplicate();
            //        return *this;
            //    }

            template < typename T >
            T cast ()
            {
                if (type() == typeid(T))
                {
                    return static_cast<Data<T> *>(none)->type;
                }

                // throw std::exception("Invalid cast type");
            }

            bool operator == (Object & rhs)
            {
                return (type() == rhs.none->type() ? none->eq(rhs) : false);
            }

            template < typename T >
            bool operator == (T value)
            {
                return (type() == typeid(T) ? cast<T>() == value : false);
            }

            bool operator != (Object & rhs)
            {
                return !(*this == rhs);
            }

            template < typename T >
            bool operator != (const T & value)
            {
                return !(*this == value);
            }

            bool empty ();

        private:

            None * none;
    };
}
#endif

