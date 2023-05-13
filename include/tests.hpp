#ifndef TESTS_PUSH_BACK
#define TESTS_PUSH_BACK

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

} // namespace test

#endif // TESTS_PUSH_BACK