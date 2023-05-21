#ifndef CXX_CONTAINER_TESTING_TESTS
#define CXX_CONTAINER_TESTING_TESTS

#include <string_view>

namespace tests {

template <typename Container>
struct PushBack {

    using value_type = typename Container::value_type;

    inline static auto run(Container& container, std::size_t size) noexcept -> void
    {
        for (auto i { 0uL }; i < size; ++i)
            container.push_back(value_type {});
    }

}; // struct PushBack

template <>
struct PushBack<void> {
    constexpr static std::string_view name = "pushback";
};

} // namespace test

#endif // CXX_CONTAINER_TESTING_TESTS
