

#ifndef CFS_EDAC_NAMEDTYPE_NAMEDTYPETEST_HPP
#define CFS_EDAC_NAMEDTYPE_NAMEDTYPETEST_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <gtest/gtest.h>

#include <cfs/edac/namedType/UnderlyingFunctionalities.hpp>
#include <cfs/edac/namedType/internal/NamedTypeInternal.hpp>

namespace cfs::edac::namedtype::test
{
    template<typename T>
    decltype(auto) tee(T&& value)
    {
        std::cout << value << '\n';

        return std::forward<T>(value);
    }

    using Meter = fluent::NamedType<double, struct MeterParameter, fluent::Addable, fluent::Comparable>;
    Meter operator"" _meter(unsigned long long value)
    {
        return Meter(value);
    }

//Meter operator"" _meter(long double value) { return Meter(value); }
    using Width = fluent::NamedType<Meter, struct WidthParameter>;
    using Height = fluent::NamedType<Meter, struct HeightParameter>;

    class Rectangle
    {
public:

        Rectangle(Width width, Height height)
            : width_(width.get())
            , height_(height.get())
        {
        }

        Meter getWidth() const
        {
            return width_;
        }

        Meter getHeight() const
        {
            return height_;
        }

private:

        Meter width_;
        Meter height_;
    };

    class NamedTypeTest : public ::testing::Test
    {
public:

        NamedTypeTest();
        ~NamedTypeTest();

protected:

        void Setup() override;
        void TearDown override;
    };
}
#endif

