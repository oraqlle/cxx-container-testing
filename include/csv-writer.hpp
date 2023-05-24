#ifndef CSV_WRITER
#define CSV_WRITER

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/std.h>

#include <rapidcsv.h>

#include <chrono>
#include <filesystem>
#include <ios>
#include <source_location>
#include <string>
#include <string_view>
#include <vector>

namespace csv {

namespace fs = std::filesystem;
using namespace std::literals;

[[nodiscard]] auto src_absolute_path(const std::source_location src_loc = std::source_location::current()) noexcept
    -> fs::path
{
    return fs::weakly_canonical(fs::path { src_loc.file_name() });
}

template <typename T>
auto write(
    fs::path sub_dir,
    std::string fname,
    std::string column_name,
    const std::vector<T>& data,
    const std::source_location src_loc = std::source_location::current()) -> void
{
    fmt::print(
        "    {}\n        {} {}\n        {} {}\n        {} {}\n",
        fmt::styled(
            "[ Started CSV Write ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::red)),
        fmt::styled(
            "[ Benchmark ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::magenta)),
        sub_dir.string(),
        fmt::styled(
            "[ Container Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::indigo)),
        column_name,
        fmt::styled(
            "[ Element Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::teal)),
        fname.substr(0uL, fname.size() - 4));

    auto data_path = src_absolute_path().parent_path() / ".."sv / "data"sv;
    auto sub_data_path = data_path / sub_dir;
    auto file_path = sub_data_path / fname;

    if (!fs::exists(data_path))
        fs::create_directory(data_path);

    if (!fs::exists(sub_data_path))
        fs::create_directory(sub_data_path);

    if (!fs::exists(file_path)) {
        auto doc = rapidcsv::Document {};

        auto file = std::fstream {
            file_path,
            std::ios::out | std::ios::trunc | std::ios::binary
        };
        doc.Save(file);
        file.close();
    }

    auto doc = rapidcsv::Document { file_path };

    auto idx = doc.GetColumnIdx(column_name);

    if (idx < 0) {
        auto size = doc.GetColumnCount();
        size = size == 0 ? 1 : size;
        doc.InsertColumn(size - 1, data, column_name);
    } else {
        doc.SetColumn(idx, data);
        doc.SetColumnName(idx, column_name);
    }

    doc.Save();

    fmt::print(
        "    {}\n        {} {}\n        {} {}\n        {} {}\n",
        fmt::styled(
            "[ Finished CSV Write ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::olive)),
        fmt::styled(
            "[ Benchmark ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::magenta)),
        sub_dir.string(),
        fmt::styled(
            "[ Container Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::indigo)),
        column_name,
        fmt::styled(
            "[ Element Type ]:",
            fmt::emphasis::bold | fmt::fg(fmt::color::teal)),
        fname.substr(0uL, fname.size() - 4));
}

} // namespace csv

#endif // CSV_WRITER
