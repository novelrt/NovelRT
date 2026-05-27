// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsDefaultsBuilder.hpp>
#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>

#include <NovelRT/Ecs/Scripting/EcsScriptingBuilder.hpp>

#include <NovelRT/Timing/StepTimer.hpp>

using namespace NovelRT::Ecs;
using namespace NovelRT::Ecs::Scripting;
using namespace NovelRT::Scripting;
using namespace NovelRT::Timing;
using namespace NovelRT::Utilities;

int main()
{
    SystemSchedulerBuilder builder{};

    auto scriptManager = std::make_shared<ScriptManager>();

    AddDefaults(builder);
    AddScripting(builder)
        .WithScriptManager(scriptManager);

    SystemScheduler scheduler = builder.Build();
    StepTimer timer{};
    Event<Timestamp::duration> TimerCallback{};

    TimerCallback += [&timer, &scheduler](auto /* delta */) { scheduler.ExecuteIteration(timer.getTotalTime()); };

    while (true)
    {
        timer.Tick(TimerCallback);
    }

    return 0;
}
