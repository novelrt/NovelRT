#include <NovelRT/Timing/Timestamp.hpp>

auto NovelRT::Timing::GameClock::now() noexcept -> time_point
{
    auto time = std::chrono::high_resolution_clock::now().time_since_epoch();

    return time_point{ std::chrono::duration_cast<time_point::duration>(time) };
}
