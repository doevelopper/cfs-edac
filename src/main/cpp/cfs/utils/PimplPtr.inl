/*!**************************************************************************
**
** Copyright (C) 2009 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the GICS library.
**
** Commercial Usage
** Licensees holding valid GICS Commercial licenses may use this file in
** accordance with the GICS Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and TECHNOGERMA Systems France.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at sales@technogerma.fr.
**
****************************************************************************/


// <insert copyright>

//qt5/qtbase/src/corelib/global/qglobal.h

#define Q_D(Class) Class ## Private * const d = d_func()
#define Q_Q(Class) Class * const q = q_func()
/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).
*/

#define Q_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#define Q_DISABLE_MOVE(Class) \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define Q_DISABLE_COPY_MOVE(Class) \
    Q_DISABLE_COPY(Class) \
    Q_DISABLE_MOVE(Class)

template <typename T>
inline T *qGetPtrHelper(T *ptr) { return ptr; }

template <typename Ptr>
inline auto qGetPtrHelper(Ptr &ptr) -> decltype(ptr.operator->()) { return ptr.operator->(); }

//https://www.fluentcpp.com/2019/08/30/how-to-disable-a-warning-in-cpp/

#define QT_DO_PRAGMA(text)            _Pragma(#text)
#define QT_WARNING_PUSH               QT_DO_PRAGMA(GCC diagnostic push)
#define QT_WARNING_POP                QT_DO_PRAGMA(GCC diagnostic pop)
#define QT_WARNING_DISABLE_GCC(text)  QT_DO_PRAGMA(GCC diagnostic ignored text)

// The body must be a statement:
#define Q_CAST_IGNORE_ALIGN(body) QT_WARNING_PUSH QT_WARNING_DISABLE_GCC("-Wcast-align") body QT_WARNING_POP

/*
#define Q_CAST_IGNORE_ALIGN(body) \
    #pragma GCC diagnostic push \
    #pragma GCC diagnostic ignored "-Wcast-align" \
    body \
    #pragma GCC diagnostic pop
*/

#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qGetPtrHelper(d_ptr));) } \
    inline const Class##Private* d_func() const \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qGetPtrHelper(d_ptr));) } \
    friend class Class##Private;

#define Q_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(qGetPtrHelper(Dptr));) } \
    inline const Class##Private* d_func() const \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(qGetPtrHelper(Dptr));) } \
    friend class Class##Private;

#define Q_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class *>(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class *>(q_ptr); } \
    friend class Class;

namespace cfs::utils
{
    template <typename T>
    PimplPtr<T>::PimplPtr()
        : m_data(new T)
    {
    }

    template <typename T>
    PimplPtr<T>::~PimplPtr()
    {

    }

    template <typename T>
    PimplPtr<T>::PimplPtr(T* data)
        : m_data(data)
    {
        assert(data != nullptr);
    }

    template <typename T>
    PimplPtr<T>::PimplPtr(const PimplPtr<T>& copy)
        : m_data(new T(*copy.m_data))
    {
    }

    template <typename T>
    template <typename T1>
    PimplPtr<T>::PimplPtr(T1 arg1)
        : m_data(new T(arg1))
    {
    }

    template <typename T>
    template <typename T1, typename T2>
    PimplPtr<T>::PimplPtr(T1 arg1, T2 arg2)
        : m_data(new T(arg1, arg2))
    {
    }

    template <typename T>
    template <typename T1, typename T2, typename T3>
    PimplPtr<T>::PimplPtr(T1 arg1, T2 arg2, T3 arg3)
        : m_data(new T(arg1, arg2, arg3))
    {
    }

    template <typename T>
    T* PimplPtr<T>::operator->()
    {
        return m_data.get();
    }

    template <typename T>
    const T* PimplPtr<T>::operator->() const
    {
        return m_data.get();
    }

    template <typename T>
    T& PimplPtr<T>::operator*()
    {
        return *m_data;
    }

    template <typename T>
    const T& PimplPtr<T>::operator*() const
    {
        return *m_data;
    }

    template <typename T>
    void PimplPtr<T>::swap(PimplPtr<T>& other)
    {
          m_data.swap(other.m_data);
    }

}
