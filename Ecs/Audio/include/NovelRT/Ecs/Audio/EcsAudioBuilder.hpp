#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.


#include <NovelRT/Ecs/SystemSchedulerBuilder.hpp>
#include <NovelRT/Ecs/Audio/AudioSystem.hpp>
#include <NovelRT/Ecs/Audio/Components/AudioEmitterComponent.hpp>
#include <NovelRT/Ecs/Audio/Components/AudioEmitterStateComponent.hpp>

#include <NovelRT/Utilities/Macros.hpp>

#include <limits>
#include <memory>
#include <utility>

namespace NovelRT::Ecs::Audio
{
    template<typename TAudioBackend>
    class EcsAudioBuilder
    {
    private:
        std::shared_ptr<NovelRT::Ecs::Audio::AudioSystem<TAudioBackend>> _system;
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;

        EcsAudioBuilder()
        {
        }

        template<typename T1>
        friend EcsAudioBuilder<T1>& AddAudio(SystemSchedulerBuilder&);

    public:
        EcsAudioBuilder(const EcsAudioBuilder& other) = default;
        EcsAudioBuilder& operator=(const EcsAudioBuilder& other) = default;
        EcsAudioBuilder(EcsAudioBuilder&& other) = default;
        EcsAudioBuilder& operator=(EcsAudioBuilder&& other) = default;
        ~EcsAudioBuilder() = default;

        EcsAudioBuilder& WithAudioSystem(
            const std::shared_ptr<NovelRT::Ecs::Audio::AudioSystem<TAudioBackend>>&
                system)
        {
            _system = system;
            return *this;
        }

        EcsAudioBuilder& WithResourceLoader(const std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader>& provider)
        {
            _resourceLoader = provider;
            return *this;
        }
        
        EcsAudioBuilder& WithDefaultAudioSystem()
        {
            return WithAudioSystem(std::make_shared<NovelRT::Ecs::Audio::AudioSystem<TAudioBackend>>(_resourceLoader));
        }

        void operator()(SystemScheduler& scheduler)
        {
            auto& cache = scheduler.GetComponentCache();

            cache.RegisterComponentType(NovelRT::Ecs::Audio::Components::AudioEmitterComponent{},
                                        "NovelRT::Ecs::Audio::AudioEmitterComponent");
            cache.RegisterComponentType(NovelRT::Ecs::Audio::Components::AudioEmitterStateComponent{}, "NovelRT::Ecs::Audio::AudioEmitterStateComponent");

            unused(scheduler.RegisterSystem(_system));
        }
    };

    template<typename TAudioBackend>
    EcsAudioBuilder<TAudioBackend>& AddAudio(SystemSchedulerBuilder& builder)
    {
        return builder.Configure(EcsAudioBuilder<TAudioBackend>{});
    };
}
