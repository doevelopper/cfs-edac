

#include </cfs/edacl/Object.hpp>

using namespace cfs::edacl;

Object::None::None()
{
}

Object::None::~None()
{
}

template < class T >
Object::Data<T>::Data()
{
}

/*
   template < class T >
   Object::Data<T>::Data(const T & value)
   :type(value)
   {

   }
   template < class T >
   Object::Data<T>::~Data()
   {

   }
   template < class T >
   const std::type_info &Object::Data<T>::type()
   {
    return (typeid(T));
   }
   template < class T >
   Object::Data * Object::Data<T>::duplicate() const
   {
    return new Object::Data<T>(type);
   }

   template < class T >
   bool Object::Data<T>::eq(Object &Obj)
   {
    return Obj.cast<T>() == type;
   }
 */
Object::Object()
	: none(nullptr)
{
}

Object::Object(const Object & orig) {
}

Object::~Object() {
	if (!empty())
	{
		delete none;
	}
}

/*
   //template < typename T >
   //Object<T>::Object(const T & value)
   //: none(new Object::Data<T>(value))
   //{
   //}

   Object::Object(const Object &Obj)
   : none(Obj.none->duplicate())
   {
   }

   const std::type_info & Object::type()
   {
    return (empty() ? typeid(void) : none->type());
   }

   bool Object::empty()
   {
    return (!none);
   }


   template <class T>
   Object<T> Object<T>::operator=(const Object<T> & value)
   {
   none = new Data<T>(value);
   return *this;
   Object::None::None()
   {

   }

   Object::None::~None()
   {

   }

   template < class T >
   Object::Data<T>::Data()
   {

   }

   /*
   template < class T >
   Object::Data<T>::Data(const T & value)
   :type(value)
   {

   }
   template < class T >
   Object::Data<T>::~Data()
   {

   }
   template < class T >
   const std::type_info &Object::Data<T>::type()
   {
    return (typeid(T));
   }
   template < class T >
   Object::Data * Object::Data<T>::duplicate() const
   {
    return new Object::Data<T>(type);
   }

   template < class T >
   bool Object::Data<T>::eq(Object &Obj)
   {
    return Obj.cast<T>() == type;
   }
 */
Object::Object()
	: none(nullptr)
{
}

Object::Object(const Object & orig) {
}

Object::~Object() {
	if (!empty())
	{
		delete none;
	}
}

/*
   //template < typename T >
   //Object<T>::Object(const T & value)
   //: none(new Object::Data<T>(value))
   //{
   //}

   Object::Object(const Object &Obj)
   : none(Obj.none->duplicate())
   {
   }

   const std::type_info & Object::type()
   {
    return (empty() ? typeid(void) : none->type());
   }

   bool Object::empty()
   {
    return (!none);
   }


   template <class T>
   Object<T> Object<T>::operator=(const Object<T> & value)
   {
   none = new Data<T>(value);
   return *this;
   // return Object<T>()
   }
 */

