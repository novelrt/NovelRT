#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Utilities/Atom.hpp>

#include <map>
#include <memory>
#include <unordered_map>

namespace NovelRT::Ecs::Graphics
{
    template <typename TGraphicsBackend>
    class EcsGraphicsBuilder;

    template <typename TGraphicsBackend>
    class RenderPassManager
    {
    private:
        std::unordered_map<std::weak_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>, Components::RenderPassId> _registeredRenderPasses;
        std::map<Components::RenderPassId, std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>> _reverseRenderPassMapping;

        explicit RenderPassManager() { }

        friend EcsGraphicsBuilder<TGraphicsBackend>;

    public:
        RenderPassManager(const RenderPassManager& other) = default;
        RenderPassManager& operator=(const RenderPassManager& other) = default;
        RenderPassManager(RenderPassManager&& other) = default;
        RenderPassManager& operator=(RenderPassManager&& other) = default;
        ~RenderPassManager() = default;

        Components::RenderPassId RegisterRenderPass(const std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>& pass)
        {
            static AtomFactory& renderPassIdFactory = AtomFactoryDatabase::GetFactory("NovelRT::Ecs::Graphics::RenderPassId");

            auto [it, inserted] = _registeredRenderPasses.try_emplace(pass, Atom(0));

            if (inserted)
            {
                it->second = renderPassIdFactory.GetNext();
                _reverseRenderPassMapping[it->second] = pass;
            }

            return it->second;
        }
    };
}
