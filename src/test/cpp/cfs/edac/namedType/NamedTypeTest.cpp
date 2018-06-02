
#include <cfs/edac/namedType/NamedTypeTest.hpp>

using namespace cfs::edac::namedtype::test

NamedTypeTest::NamedTypeTest()
{
}

NamedTypeTest::~NamedTypeTest
{

}

void NamedTypeTest::SetUp()
{
}

void NamedTypeTest::TearDown()
{
}
/*
TEST_CASE("Basic usage")
{
    Rectangle r(Width(10_meter), Height(12_meter));
    EXPECT_TRUE(r.getWidth().get() == 10);
    EXPECT_TRUE(r.getHeight().get() == 12);
}

using NameRef = fluent::NamedType<std::string&, struct NameRefParameter>;

void changeValue(const NameRef name)
{
    name.get() = "value2";
}

TEST_F(NamedTypeTest,"Passing a strong reference")
{
    std::string value = "value1";
    changeValue(NameRef(value));
    EXPECT_TRUE(value == "value2");
}

TEST_F(NamedTypeTest,"Construction of NamedType::ref from the underlying type")
{
    using StrongInt = fluent::NamedType<int, struct StrongIntTag>;
    auto addOne = [](StrongInt::ref si) { ++(si.get()); };
    
    int i = 42;
    addOne(StrongInt::ref(i));
    EXPECT_TRUE(i == 43);
}

TEST_F(NamedTypeTest,"Implicit conversion of NamedType to NamedType::ref")
{
    using StrongInt = fluent::NamedType<int, struct StrongIntTag>;
    auto addOne = [](StrongInt::ref si) { ++(si.get()); };
    
    StrongInt i(42);
    addOne(i);
    EXPECT_TRUE(i.get() == 43);

    StrongInt j(42);
    addOne(StrongInt::ref(j));
    EXPECT_TRUE(j.get() == 43);
}

template<typename Function>
using Comparator = fluent::NamedType<Function, struct ComparatorParameter>;

template <typename Function>
std::string performAction(Comparator<Function> comp)
{
    return comp.get()();
}

TEST_F(NamedTypeTest,"Strong generic type")
{
    EXPECT_TRUE(performAction(fluent::make_named<Comparator>([](){ return std::string("compare"); })) == "compare");
}

TEST_F(NamedTypeTest,"Addable")
{
    using AddableType = fluent::NamedType<int, struct SubtractableTag, fluent::Addable>;
    AddableType s1(12);
    AddableType s2(10);
    EXPECT_TRUE((s1 + s2).get() == 22);
}

TEST_F(NamedTypeTest,"Subtractable")
{
    using SubtractableType = fluent::NamedType<int, struct SubtractableTag, fluent::Subtractable>;
    SubtractableType s1(12);
    SubtractableType s2(10);
    EXPECT_TRUE((s1 - s2).get() == 2);
}

TEST_F(NamedTypeTest,"Multiplicable")
{
    using MultiplicableType = fluent::NamedType<int, struct MultiplicableTag, fluent::Multiplicable>;
    MultiplicableType s1(12);
    MultiplicableType s2(10);
    EXPECT_TRUE((s1 * s2).get() == 120);
}

TEST_F(NamedTypeTest,"Comparable")
{
    EXPECT_TRUE((10_meter == 10_meter));
    EXPECT_TRUE(!(10_meter == 11_meter));
    EXPECT_TRUE((10_meter != 11_meter));
    EXPECT_TRUE(!(10_meter != 10_meter));
    EXPECT_TRUE((10_meter <  11_meter));
    EXPECT_TRUE(!(10_meter <  10_meter));
    EXPECT_TRUE((10_meter <= 10_meter));
    EXPECT_TRUE((10_meter <= 11_meter));
    EXPECT_TRUE(!(10_meter <= 9_meter));
    EXPECT_TRUE((11_meter >  10_meter));
    EXPECT_TRUE(!(10_meter > 11_meter));
    EXPECT_TRUE((11_meter >= 10_meter));
    EXPECT_TRUE((10_meter >= 10_meter));
    EXPECT_TRUE(!(9_meter >= 10_meter));
}

TEST_F(NamedTypeTest,"ConvertibleWithOperator")
{
    struct B
    {
        B(int x) : x(x) {}
        int x;
    };
    
    struct A
    {
        A(int x) : x(x) {}
        operator B () const { return B(x);}
        int x;
    };
        
    using StrongA = fluent::NamedType<A, struct StrongATag, fluent::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B b = strongA;
    EXPECT_TRUE(b.x == 42);
}

TEST_F(NamedTypeTest,"ConvertibleWithConstructor")
{
    struct A
    {
        A(int x) : x(x) {}
        int x;
    };
        
    struct B
    {
        B(A a) : x(a.x) {}
        int x;
    };
        
    using StrongA = fluent::NamedType<A, struct StrongATag, fluent::ImplicitlyConvertibleTo<B>::templ>;
    StrongA strongA(A(42));
    B b = strongA;
    EXPECT_TRUE(b.x == 42);
}
    
TEST_F(NamedTypeTest,"ConvertibleToItself")
{
    using MyInt = fluent::NamedType<int, struct MyIntTag, fluent::ImplicitlyConvertibleTo<int>::templ>;
    MyInt myInt(42);
    int i = myInt;
    EXPECT_TRUE(i == 42);
}
    
TEST_F(NamedTypeTest,"Hash")
{
    using SerialNumber = fluent::NamedType<std::string, struct SerialNumberTag, fluent::Comparable, fluent::Hashable>;

    std::unordered_map<SerialNumber, int> hashMap = { {SerialNumber{"AA11"}, 10}, {SerialNumber{"BB22"}, 20} };
    SerialNumber cc33{"CC33"};
    hashMap[cc33] = 30;
    EXPECT_TRUE(hashMap[SerialNumber{"AA11"}] == 10);
    EXPECT_TRUE(hashMap[SerialNumber{"BB22"}] == 20);
    EXPECT_TRUE(hashMap[cc33] == 30);
}

struct testFunctionCallable_A
{
    testFunctionCallable_A(int x) : x(x) {}
    testFunctionCallable_A(testFunctionCallable_A const&) = delete; // ensures that passing the argument to a function doesn't make a copy
    testFunctionCallable_A(testFunctionCallable_A&&) = default;
    testFunctionCallable_A& operator+=(testFunctionCallable_A const& other) { x += other.x; return *this; }
    int x;
};
    
testFunctionCallable_A operator+(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2)
{
    return testFunctionCallable_A(a1.x + a2.x);
}
    
bool operator==(testFunctionCallable_A const& a1, testFunctionCallable_A const& a2)
{
    return a1.x == a2.x;
}

TEST_F(NamedTypeTest,"Function callable")
{
    using A = testFunctionCallable_A;
    auto functionTakingA = [](A const& a){ return a.x; };
    
    using StrongA = fluent::NamedType<A, struct StrongATag, fluent::FunctionCallable>;
    StrongA strongA(A(42));
    const StrongA constStrongA(A(42));
    EXPECT_TRUE(functionTakingA(strongA) == 42);
    EXPECT_TRUE(functionTakingA(constStrongA) == 42);
    EXPECT_TRUE(strongA + strongA == 84);
}

TEST_F(NamedTypeTest,"Method callable")
{
    class A
    {
    public:
        A(int x) : x(x) {}
        A(A const&) = delete; // ensures that invoking a method doesn't make a copy
        A(A&&) = default;
        
        int method(){ return x; }
        int constMethod() const{ return x; }
    private:
        int x;
    };
    
    using StrongA = fluent::NamedType<A, struct StrongATag, fluent::MethodCallable>;
    StrongA strongA(A(42));
    const StrongA constStrongA(A((42)));
    EXPECT_TRUE(strongA->method() == 42);
    EXPECT_TRUE(constStrongA->constMethod() == 42);
}

TEST_F(NamedTypeTest,"Callable")
{
    class A
    {
    public:
        A(int x) : x(x) {}
        A(A const&) = delete; // ensures that invoking a method or function doesn't make a copy
        A(A&&) = default;
        
        int method(){ return x; }
        int constMethod() const{ return x; }
    private:
        int x;
    };
    
    auto functionTakingA = [](A const& a){ return a.constMethod(); };
    
    using StrongA = fluent::NamedType<A, struct StrongATag, fluent::Callable>;
    StrongA strongA(A(42));
    const StrongA constStrongA(A((42)));
    EXPECT_TRUE(functionTakingA(strongA) == 42);
    EXPECT_TRUE(strongA->method() == 42);
    EXPECT_TRUE(constStrongA->constMethod() == 42);
}

TEST_F(NamedTypeTest,"Named arguments")
{
    using FirstName = fluent::NamedType<std::string, struct FirstNameTag>;
    using LastName = fluent::NamedType<std::string, struct LastNameTag>;
    static const FirstName::argument firstName;
    static const LastName::argument lastName;
    auto getFullName = [](FirstName const& firstName, LastName const& lastName)
    {
        return firstName.get() + lastName.get();
    };
    
    auto fullName = getFullName(firstName = "James", lastName = "Bond");
    EXPECT_TRUE(fullName == "JamesBond");
}

TEST_F(NamedTypeTest,"Empty base class optimization")
{
    EXPECT_TRUE(sizeof(Meter) == sizeof(double));
}

*/


