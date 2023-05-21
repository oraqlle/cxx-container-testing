#ifndef CXX_CONTAINER_TESTING_CONCEPTS
#define CXX_CONTAINER_TESTING_CONCEPTS

#include <concepts>

namespace concepts {

template <template <typename Container> class TestType>
concept Test = requires(TestType<Container> test, Container container) {
    test::run(container, std::size_t {});
};

template <template <typename Container> class MakerType>
concept Maker = requires(MakerType<Container> maker, Container container) {
    maker::make(std::size_t {})->std::convertible_to<Container>
};

} // namespace tests

#endif // CXX_CONTAINER_TESTING_CONCEPTS
