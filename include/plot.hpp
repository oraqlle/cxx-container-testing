#ifndef PLOT
#define PLOT

#include <matplot/matplot.h>

#include <chrono>
#include <vector>
#include <cmath>

namespace plot {

namespace mp = matplot;

// template <typename Duration>
// auto graph(std::string_view name, const std::vector<Duration>& results) -> void
auto graph() -> void
{
    std::vector<double> x = mp::linspace(0, 2 * mp::pi);
    std::vector<double> y = mp::transform(x, [](auto x) { return std::sin(x); });

    mp::plot(x, y, "-o");
    mp::hold(mp::on);
    mp::plot(x, mp::transform(y, [](auto y) { return -y; }), "--xr");
    mp::plot(x, mp::transform(x, [](auto x) { return x / mp::pi - 1.; }), "-:gs");
    mp::plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");

    mp::show();
}

} // namespace plot

#endif // PLOT
