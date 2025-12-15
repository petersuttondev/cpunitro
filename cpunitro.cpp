#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <gsl/util>
#include <iostream>
#include <new>
#include <string>
#include <unistd.h>

namespace
{

[[nodiscard]] auto get_cpu_count()
{
    auto const cpu_count = ::sysconf(_SC_NPROCESSORS_ONLN);

    if (cpu_count == -1)
    {
        throw std::exception{};
    }

    return cpu_count;
}

[[noreturn]] auto run_as_root()
{
    auto const sudo = ::strdup("sudo");

    if (sudo == nullptr)
    {
        throw std::bad_alloc{};
    }

    auto const free_sudo = gsl::finally([sudo]() {
        ::free(sudo);
    });

    auto const exe =
        ::strdup(std::filesystem::read_symlink("/proc/self/exe").c_str());

    if (exe == nullptr)
    {
        throw std::bad_alloc{};
    }

    auto const free_exe = gsl::finally([exe]() {
        ::free(exe);
    });

    char *const argv[] = {sudo, exe, nullptr};
    ::execv("/usr/bin/sudo", argv);
    throw std::exception{};
}

auto set_scaling_governor_to_performance(auto const cpu_index)
{
    std::ofstream file(
        "/sys/devices/system/cpu/cpu" + std::to_string(cpu_index) +
        "/cpufreq/scaling_governor"
    );

    if (!file)
    {
        throw std::exception{};
    }

    file << "performance";

    if (!file)
    {
        throw std::exception{};
    }

    file.close();

    if (!file)
    {
        throw std::exception{};
    }
}

} // namespace

auto main() -> int
{
    if (::geteuid() != 0u)
    {
        ::run_as_root();
    }

    auto const cpu_count = ::get_cpu_count();

    for (auto i = decltype(cpu_count){0}; i < cpu_count; ++i)
    {
        ::set_scaling_governor_to_performance(i);
    }
}
