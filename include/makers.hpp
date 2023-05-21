#ifndef CXX_CONTAINER_TESTING_MAKERS
#define CXX_CONTAINER_TESTING_MAKERS

namespace makers {

template <typename Container>
struct Empty {
    inline static auto make([[maybe_unused]] std::size_t size) noexcept
        -> Container
    {
        return Container {};
    }

    inline static auto clean() noexcept -> void { }
};

template <typename Container>
struct Preallocated {
    inline static auto make([[maybe_unused]] std::size_t size) noexcept
        -> Container
    {
        auto container = Container {};
        container.reserve(size);
        return container;
    }

    inline static auto clean() noexcept -> void { }
};

} // namespace makers

#endif // CXX_CONTAINER_TESTING_MAKERS
