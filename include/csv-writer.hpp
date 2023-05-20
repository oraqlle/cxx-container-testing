#ifndef CSV_WRITER
#define CSV_WRITER

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
    std::string fname,
    std::string column_name,
    const std::vector<T>& data,
    const std::source_location src_loc = std::source_location::current()) -> void
{
    auto data_path = src_absolute_path().parent_path() / ".."sv / "data"sv;
    auto file_path = data_path / fname;

    if (!fs::exists(data_path))
        fs::create_directory(data_path);

    if (!fs::exists(file_path))
    {
        auto doc = rapidcsv::Document { };

        auto file = std::fstream {
            file_path,
            std::ios::out | std::ios::trunc | std::ios::binary
        };
        doc.Save(file);
        file.close();
    }

    auto doc = rapidcsv::Document { data_path / fname, rapidcsv::LabelParams { 0, 0 } };

    auto size = doc.GetColumnCount();
    doc.InsertColumn(size - 1, data, column_name);
    doc.Save();
}

auto erase(std::string fname) -> void
{
}

} // namespace csv

#endif // CSV_WRITER
