#ifndef CXX_CONTAINER_TESTING_UTILS
#define CXX_CONTAINER_TESTING_UTILS

#include <array>
#include <utility>

namespace utils {

template <typename T, std::size_t... Indices>
constexpr auto make_array(std::integer_sequence<std::size_t, Indices...>) noexcept
    -> std::array<T, sizeof...(Indices)>
{
    return { (static_cast<T>(Indices))... };
}

template <typename T>
constexpr auto is_small() noexcept -> bool
{
    return sizeof(T) <= sizeof(std::size_t);
}

} // namespace utils

#endif // CXX_CONTAINER_TESTING_UTILS
