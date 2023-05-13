#ifndef MAKERS
#define MAKERS

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

} // namespace makers

#endif // MAKERS
