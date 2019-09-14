

#ifndef CFS_EDACL_INTERNAL_REGISTRY_HPP
#define CFS_EDACL_INTERNAL_REGISTRY_HPP

#include <cstdint>
#include <type_traits>
#include <functional>
#include <limits>

namespace cfs::edacl::internal
{
    template <typename T>
    struct Mask
    {
        constexpr static const T value = std::numeric_limits<T>::max();
    };

    enum class Length : std::uint8_t
    {
        B_8 = 8,
        B_16 = 16,
        B_32 = 32,
        B_64 = 64,
        B_128 = 128
    };

    template <Length S>
    struct TypeTraits {};

    template <>
    struct TypeTraits<Length::B_8>
    {
        using type = std::uint8_t;
        constexpr static auto BIT_SIZE = std::uint8_t{Length::B_8};
        constexpr static auto BYTE_SIZE = std::uint8_t{BIT_SIZE / Length::B_8};
    };

    template <>
    struct TypeTraits<Length::B_16>
    {
        using type = std::uint16_t;
        constexpr static auto BIT_SIZE = std::uint8_t{Length::B_16};
        constexpr static auto BYTE_SIZE = std::uint8_t{BIT_SIZE / Length::B_8};
    };

    template <>
    struct TypeTraits<Length::B_32>
    {
        using type = std::uint32_t;
        constexpr static auto BIT_SIZE = std::uint8_t{Length::B_32};
        constexpr static auto BYTE_SIZE = std::uint8_t{BIT_SIZE / Length::B_8};
    };

    template <>
    struct TypeTraits<Length::B_64>
    {
        using type = std::uint64_t;
        constexpr static auto BIT_SIZE = std::uint8_t{Length::B_64};
        constexpr static auto BYTE_SIZE = std::uint8_t{BIT_SIZE / Length::B_8};
    };

    template <>
    struct TypeTraits<Length::B_128>
    {
        using type = std::uint64_t;
        constexpr static auto BIT_SIZE = std::uint8_t{Length::B_128};
        constexpr static auto BYTE_SIZE = std::uint8_t{BIT_SIZE / Length::B_8};
    };

    namespace internals
    {
        template <typename T, T value, T limit>
        struct CheckUSL : std::integral_constant<bool, value <= limit> {};
        template <std::uintptr_t address, std::size_t alignment>
        struct Aligned
            : std::integral_constant<bool, (address & (alignment - 1)) == 0> {};
    }

    template <std::uintptr_t B, std::uint32_t P>
    struct RegisterPack
    {
        constexpr static const std::uintptr_t pack_base = B;
        constexpr static const std::uint32_t size_in_bytes = P;
    };

    template <std::uintptr_t memorySection, std::size_t memoryByteCapacity>
    struct Memory
    {
        using memoryPlaceHolder = std::array<volatile std::uint8_t, memoryByteCapacity>;
        static memoryPlaceHolder& memoryStorage;

        template <Length reg_size, std::size_t byte_offset>
        static const volatile typename TypeTraits<reg_size>::type& ro_memory()
        {
            static_assert(internals::Aligned<memorySection + byte_offset
                                             , std::alignment_of<typename TypeTraits<reg_size>::type>::value>::value
                          , "Memory::ro request not aligned");

            return *(reinterpret_cast<const volatile typename
                                      TypeTraits<reg_size>::type*>( &memoryStorage[byte_offset]));
        }

        template <Length reg_size, std::size_t byte_offset>
        static volatile typename TypeTraits<reg_size>::type& rw_memory()
        {
            static_assert( internals::Aligned<memorySection + byte_offset
                                              , std::alignment_of<typename TypeTraits<reg_size>::type>::value>::value
                           , "Memory::rw request not aligned");

            return *( reinterpret_cast<volatile typename TypeTraits<reg_size>::type*>( &memoryStorage[byte_offset]));
        }
    };

    template <std::uintptr_t a, std::size_t s>
    typename Memory<a, s>::memoryPlaceHolder& Memory<a, s>::memoryStorage =
        *(reinterpret_cast<typename Memory<a, s>::memoryPlaceHolder*>(a));

    template <typename RegisterPack>
    struct RegisterMemoryDevice
    {
        using mem_device = Memory<RegisterPack::pack_base, RegisterPack::size_in_bytes>;
    };

    template <typename T, T mask, std::uint8_t offset>
    struct is_trivial_rw : std::integral_constant<bool
        , (mask == Mask<T>::value) && (offset == std::uint8_t {0})> {};

    template <typename T, T mask, std::uint8_t offset, typename U>
    using is_trivial = typename std::enable_if<is_trivial_rw<T, mask, offset>::value, U>::type;

    template <typename T, T mask, std::uint8_t offset, typename U>
    using is_not_trivial = typename std::enable_if<!is_trivial_rw<T, mask, offset>::value, U>::type;

    template <typename MMIORregisters, typename T, T mask, std::uint8_t offset>
    struct RegisterRead
    {
        template <typename U = void>
        static T read(const MMIORregisters& mmio_device, is_not_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            return static_cast<T>((mmio_device & mask) >> offset);
        }

        template <typename U = void>
        static T read(const MMIORregisters& mmio_device, is_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            return static_cast<T>(mmio_device);
        }
    };

    template <typename MMIORregisters, typename T, T mask, std::uint8_t offset>
    struct RegisterWrite
    {
        template <typename U = void>
        static void write(MMIORregisters& mmio_device, T value, is_not_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            mmio_device = static_cast<T>((mmio_device & ~mask) | ((value << offset) & mask));
        }

        template <typename U = void>
        static void write(MMIORregisters& mmio_device, T value, is_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            mmio_device = value;
        }
    };

    template <typename MMIORregisters, typename T, T mask, std::uint8_t offset, T value>
    struct RegisterWriteConstant
    {
        template <typename U = void>
        static void write(MMIORregisters& mmio_device, is_not_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            mmio_device = static_cast<T>((mmio_device & ~mask) | ((value << offset) & mask));
        }

        template <typename U = void>
        static void write(MMIORregisters& mmio_device, is_trivial<T, mask, offset, U>* = nullptr) noexcept
        {
            mmio_device = value;
        }
    };

    struct read_only
    {
        template <typename MMIORregisters, typename T, T mask, std::uint8_t offset>
        static T read(const MMIORregisters& mmio_device) noexcept
        {
            return RegisterRead<MMIORregisters, T, mask, offset>::read(mmio_device);
        }
    };

    struct read_write : read_only
    {
        template <typename MMIORregisters, typename T, T mask, std::uint8_t offset>
        static void write(MMIORregisters& mmio_device, const T value) noexcept
        {
            RegisterWrite<MMIORregisters, T, mask, offset>::write(mmio_device, value);
        }

        template <typename MMIORregisters, typename T, T mask, std::uint8_t offset, T value>
        static void write(MMIORregisters& mmio_device) noexcept
        {
            RegisterWriteConstant<MMIORregisters, T, mask, offset, value>::write(mmio_device);
        }

        template <typename MMIORregisters, typename T, T mask>
        static void set(MMIORregisters& mmio_device) noexcept
        {
            RegisterWriteConstant<MMIORregisters, T, mask, std::uint8_t{0}, mask>::write(mmio_device);
        }

        template <typename MMIORregisters, typename T, T mask>
        static void clear(MMIORregisters& mmio_device) noexcept
        {
            RegisterWriteConstant<MMIORregisters, T, mask, std::uint8_t{0}, static_cast<T>(~mask)>::write(mmio_device);
        }

        template <typename MMIORregisters, typename T, T mask>
        static void toggle(MMIORregisters& mmio_device) noexcept
        {
            mmio_device = static_cast<T>((mmio_device) ^ mask);
        }
    };

    struct write_only
    {
        template <typename MMIORregisters, typename T, T mask, std::uint8_t offset>
        static void write(MMIORregisters& mmio_device, const T value) noexcept
        {
            RegisterWrite<MMIORregisters, T, Mask<T>::value, std::uint8_t{0}>::write( mmio_device, ((value << offset) &
                                                                                                    mask));
        }

        template <typename MMIORregisters, typename T, T mask, std::uint8_t offset, T value>
        static void write(MMIORregisters& mmio_device) noexcept
        {
            RegisterWriteConstant<MMIORregisters, T, Mask<T>::value, std::uint8_t{0}, ((value << offset) & mask)>
            ::write(mmio_device);
        }
    };

    template <typename Mask>
    constexpr Mask make_mask(const std::uint8_t width) noexcept
    {
        return width == 0 ? static_cast<Mask>(0u) : static_cast<Mask>((make_mask<Mask>(std::uint8_t(width - 1)) << 1) |
                                                                      1);
    }

    template <typename Mask>
    constexpr Mask make_shifted_mask(const std::uint8_t width, const std::uint8_t offset) noexcept
    {
        return static_cast<Mask>(make_mask<Mask>(width) << offset);
    }

    template <typename Register, bool use_shadow>
    struct Shadow : std::false_type {};

    template <typename Register>
    struct Shadow<Register, true> : std::true_type
    {
        static typename Register::type shadow_value;
    };

    template <typename Register>
    typename Register::type Shadow<Register, true>::shadow_value = Register::reset;

    template <typename Register, typename Register::type mask, std::uint8_t offset, typename Register::type value>
    class Impl
    {
        private:

            using base_type = typename Register::type;
            constexpr static auto m_accumulated = base_type{(value << offset) & mask};
            constexpr static auto m_combinedMask = mask;
            template <typename F, base_type new_value>
            using propagated = Impl<Register
            , (m_combinedMask | F::mask), std::uint8_t {0}
            , (m_accumulated & ~F::mask) | ((new_value << F::offset ) & F::mask)>;
            Impl() = default;
            static_assert(!Register::shadow::value, "merge write is not available for shadow value register");

        public:

            static Impl create() noexcept
            {
                return {};
            }

            Impl(const Impl&) = delete;
            Impl& operator=(const Impl&) = delete;
            Impl& operator=(Impl&&) = delete;
            Impl operator=(Impl) = delete;
            Impl(Impl&&) = delete;

            void done() const&& noexcept
            {
                typename Register::MMIORregisters& mmio_device = Register::rw_mem_device();
                RegisterWriteConstant<typename Register::MMIORregisters
                , typename Register::type
                , m_combinedMask
                , std::uint8_t{0}
                , m_accumulated>::write(mmio_device);
            }

            template <typename F, base_type field_value>
            propagated<F, field_value>&& with() const&& noexcept
            {
                static_assert( std::is_same<typename F::parent_register, Register>::value
                               , "Impl:: field is not from the same register");
                constexpr auto no_overflow = internals::CheckUSL<typename Register::type
                                                                 , field_value
                                                                 , (F::mask >> F::offset)>::value;
                static_assert(no_overflow
                              , "Impl:: field overflow in with() call");

                return std::move(propagated<F, field_value>{});
            }
    };

    template <typename Register, typename Register::type mask>
    class MergeWrite
    {
        private:

            using base_type = typename Register::type;
            base_type m_accumulated;
            constexpr static auto m_combinedMask = mask;
            template <typename F>
            using propagated = MergeWrite<Register, m_combinedMask | F::mask>;
            constexpr MergeWrite()
                : m_accumulated{0} {
            };
            constexpr explicit MergeWrite(const base_type v)
                : m_accumulated{v} {
            };
            static_assert(!Register::shadow::value,"merge write is not available for shadow value register");

        public:

            constexpr static MergeWrite create(const base_type value) noexcept
            {
                return MergeWrite(value);
            }

            MergeWrite(MergeWrite&& mw) noexcept
                : m_accumulated{mw.m_accumulated} {
            };
            MergeWrite(const MergeWrite&) = delete;
            MergeWrite& operator=(const MergeWrite&) = delete;
            MergeWrite& operator=(MergeWrite&&) = delete;

            void done() const&& noexcept
            {
                typename Register::MMIORregisters& mmio_device = Register::rw_mem_device();
                RegisterWrite<typename Register::MMIORregisters
                , base_type
                , m_combinedMask
                , std::uint8_t{0}>::write(mmio_device, m_accumulated);
            }

            template <typename F>
            propagated<F> with(const base_type value) const&& noexcept
            {
                static_assert( std::is_same<typename F::parent_register, Register>::value
                               , "field is not from the same register in merge_write");
                const auto new_value = static_cast<base_type>( (m_accumulated & ~F::mask) | ((value << F::offset) &
                                                                                             F::mask));

                return std::move(propagated<F>::create(new_value));
            }
    };

    template <std::uintptr_t reg_address
              , Length reg_size
              , typename TypeTraits<reg_size>::type reset_value = 0x0
              , bool use_shadow = false>
    struct Register
    {
        using type = typename TypeTraits<reg_size>::type;
        using MMIORregisters = volatile type;
        using shadow = Shadow<Register, use_shadow>;
        constexpr static auto base_address = reg_address;
        constexpr static auto size = TypeTraits<reg_size>::BIT_SIZE;
        constexpr static auto reset = reset_value;
        using pack = RegisterPack<base_address, size / 8u>;
        static MMIORregisters& rw_mem_device()
        {
            using mem_device = typename RegisterMemoryDevice<pack>::mem_device;

            return mem_device::template rw_memory<reg_size, 0>();
        }

        static const MMIORregisters& ro_mem_device()
        {
            using mem_device = typename RegisterMemoryDevice<pack>::mem_device;

            return mem_device::template ro_memory<reg_size, 0>();
        }

        template <typename F>
        static MergeWrite<typename F::parent_register, F::mask> merge_write(
            const typename F::type value) noexcept
        {
            return MergeWrite<typename F::parent_register, F::mask>::create(
                static_cast<type>((value << F::offset) & F::mask));
        }

        template <typename F, type value, typename T = Impl<typename F::parent_register,
                                                            F::mask,
                                                            F::offset,
                                                            value> >
        static T&& merge_write() noexcept
        {
            static_assert(internals::CheckUSL<type, value, (F::mask >> F::offset)>::value
                          , "Register::merge_write<value>:: value too large for the field");

            return std::move(T::create());
        }

        static_assert(size != 0u, "Register:: register definition with zero size");
        static_assert(internals::Aligned<reg_address
                                         , TypeTraits<reg_size>::BYTE_SIZE>::value
                      ,  "Register:: address is mis-aligned for register type");
    };

    template <typename RegisterPack,
              Length reg_size,
              std::uint32_t bit_offset,
              typename TypeTraits<reg_size>::type reset_value = 0x0,
              bool use_shadow = false>
    struct PackedRegister : Register<RegisterPack::pack_base + (bit_offset / 8u),
                                     reg_size,
                                     reset_value,
                                     use_shadow>
    {
        using pack = RegisterPack;
        using base_reg = Register<RegisterPack::pack_base + (bit_offset / 8u),
                                  reg_size,
                                  reset_value,
                                  use_shadow>;
        static typename base_reg::MMIORregisters& rw_mem_device() noexcept
        {
            using mem_device = typename RegisterMemoryDevice<RegisterPack>::mem_device;

            return mem_device::template rw_memory<reg_size, (bit_offset / 8u)>();
        }

        static const typename base_reg::MMIORregisters& ro_mem_device() noexcept
        {
            using mem_device = typename RegisterMemoryDevice<RegisterPack>::mem_device;

            return mem_device::template ro_memory<reg_size, (bit_offset / 8u)>();
        }

        static_assert(TypeTraits<reg_size>::BYTE_SIZE + (bit_offset / 8u)
                      <= RegisterPack::size_in_bytes
                      , "PackRegister:: packed register is overflowing the pack");
        static_assert( internals::Aligned<RegisterPack::pack_base
                                          , TypeTraits<reg_size>::BYTE_SIZE>::value
                       ,  "PackedRegister:: pack base address is mis-aligned for register type");
        static_assert( internals::Aligned<RegisterPack::pack_base + (bit_offset / 8u)
                                          , TypeTraits<reg_size>::BYTE_SIZE>::value
                       ,  "PackedRegister:: offset address is mis-aligned for register type");
    };

    template <typename ... T>
    struct PackIndexing
    {
        using tuple_t = typename std::tuple<T...>;
        constexpr static const std::size_t n_elems = std::tuple_size<tuple_t>::value;
        template <std::size_t N>
        using elem = typename std::tuple_element<N, tuple_t>::type;
    };

    template <std::size_t start, std::size_t end>
    struct for_loop
    {
        template <typename Func>
        static void apply() noexcept
        {
            Func().template operator()<start>();
            if (start < end)
                for_loop<start + 1ul, end>::template apply<Func>();
        }

        template <typename Op>
        static void apply(Op&& f) noexcept
        {
            if (start < end)
            {
                f(std::integral_constant<std::size_t, start>{});
                for_loop<start + 1ul, end>::apply(std::forward<Op>(f));
            };
        }
    };

    template <std::size_t end>
    struct for_loop<end, end>
    {
        template <typename Func>
        static void apply() noexcept {
        }

        template <typename Op>
        static void apply(Op&& f) noexcept {
        }
    };

    template <typename IndexedPack>
    struct pack_loop : for_loop<0, IndexedPack::n_elems> {};

    template <typename BaseRegister,
              std::uint8_t field_width,
              std::uint8_t field_offset,
              typename AccessPolicy>
    struct Field
    {
        using parent_register = BaseRegister;
        using type = typename parent_register::type;
        using MMIORregisters = typename parent_register::MMIORregisters;
        using policy = AccessPolicy;
        constexpr static auto width = field_width;
        constexpr static auto offset = field_offset;
        constexpr static auto mask = make_shifted_mask<type>(width, offset);

        template <type value, typename T>
        using if_no_shadow = typename std::enable_if<!parent_register::shadow::value, T>::type;

        template <type value, typename T>
        using if_shadow = typename std::enable_if<parent_register::shadow::value, T>::type;

        static type read() noexcept
        {
            return policy::template read<MMIORregisters, type, mask, offset>(
                parent_register::ro_mem_device());
        }

        template <typename T = type>
        static void write(const if_no_shadow<type{0}, T> value) noexcept
        {
            policy::template write<MMIORregisters, type, mask, offset>(
                parent_register::rw_mem_device(), value);
        }

        template <typename T = type>
        static void write(const if_shadow<type{0}, T> value) noexcept
        {
            RegisterWrite<type, type, mask, offset>::write(
                parent_register::shadow::shadow_value, value);
            policy::template write<MMIORregisters, type, Mask<type>::value, std::uint8_t{0}>(
                parent_register::rw_mem_device()
                , parent_register::shadow::shadow_value);
        }

        template <type value, typename T = void>
        static void write(if_no_shadow<value, T>* = nullptr) noexcept
        {
            policy::template write<MMIORregisters, type, mask, offset, value>(
                parent_register::rw_mem_device());
            static_assert( internals::CheckUSL<type, value, (mask >> offset)>::value
                           , "Field::write<value>: value too large for the field");
        }

        template <type value, typename T = void>
        static void write(if_shadow<value, T>* = nullptr) noexcept
        {
            write(value);
            static_assert( internals::CheckUSL<type, value, (mask >> offset)>::value
                           , "Field::write<value>: value too large for the field");
        }

        static void set() noexcept
        {
            policy::template set<MMIORregisters, type, mask>( parent_register::rw_mem_device());
        }

        static void clear() noexcept
        {
            policy::template clear<MMIORregisters, type, mask>( parent_register::rw_mem_device());
        }

        static void toggle() noexcept
        {
            policy::template toggle<MMIORregisters, type, mask>( parent_register::rw_mem_device());
        }

        static bool is_set() noexcept
        {
            return (Field::read() == (mask >> offset));
        }

        static bool is_clear() noexcept
        {
            return (Field::read() == type{0});
        }

        static_assert(parent_register::size >= width
                      , "Field:: field width is larger than parent register size");

        static_assert(parent_register::size >= width + offset
                      , "Field:: offset + width is larger than parent register size");

        static_assert(width != std::uint8_t{0}
                      , "Field:: defining a Field type of zero width is not allowed");
    };
}

#endif

