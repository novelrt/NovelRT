// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <iostream>

using namespace NovelRT::Ecs;
using namespace NovelRT::PluginManagement;

NovelRT::Utilities::Event<NovelRT::Timing::Timestamp> DummyUpdateStuff;

int main()
{
    /*
    DefaultPluginSelector selector;
    auto scheduler =
        Configurator()
            //.WithDefaultSystemsAndComponents()
            .WithSystems({[&](auto, auto){ std::cout << "system" << std::endl; }})
            .WithThreadCount(32)
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IGraphicsPluginProvider>())
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IWindowingPluginProvider>())
            .WithPluginProvider(selector.GetDefaultPluginTypeOnCurrentPlatformFor<IResourceManagementPluginProvider>())
            .InitialiseAndRegisterComponents();

    DummyUpdateStuff += [&](auto delta) { scheduler.ExecuteIteration(delta); };

    NovelRT::Timing::StepTimer timer;

    while (true)
    {
        timer.tick(DummyUpdateStuff);
    }
     */

    std::atomic_uint64_t test = 0;

    test ^= (1ULL << 30);

    auto result = NovelRT::Maths::Utilities::LeadingZeroCount64(test);

    std::cout << result << std::endl;

    return 0;
}
