#include <NovelRT/Timing/Timestamp.hpp>

auto NovelRT::Timing::GameClock::now() noexcept -> time_point
{
    // N.B. We need to use steady_clock here as it is guaranteed to be monotonic (within reason)
    auto time = std::chrono::steady_clock::now().time_since_epoch();

    return time_point{std::chrono::duration_cast<time_point::duration>(time)};
}
