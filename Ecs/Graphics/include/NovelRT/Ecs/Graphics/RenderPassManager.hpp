#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Graphics/Components/RenderPass.hpp>
#include <NovelRT/Graphics/GraphicsRenderPass.hpp>
#include <NovelRT/Utilities/Atom.hpp>

#include <map>
#include <memory>
#include <set>
#include <tuple>

namespace NovelRT::Ecs::Graphics
{
    template<typename TGraphicsBackend>
    class EcsGraphicsBuilder;

    template<typename TGraphicsBackend>
    class RenderPassManager
    {
    private:
        using RenderPass = std::weak_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>;
        using Tuple = std::tuple<RenderPass, Components::RenderPassId>;
        struct Compare
        {
            constexpr bool operator()(const Tuple& lhs, const Tuple& rhs) const
            {
                std::less<Components::RenderPassId> impl{};
                return impl(std::get<Components::RenderPassId>(lhs), std::get<Components::RenderPassId>(rhs));
            }
        };

        std::set<Tuple, Compare> _registeredRenderPasses;
        std::map<Components::RenderPassId, std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>>
            _reverseRenderPassMapping;

        explicit RenderPassManager()
        {
        }

        friend EcsGraphicsBuilder<TGraphicsBackend>;

    public:
        RenderPassManager(const RenderPassManager& other) = default;
        RenderPassManager& operator=(const RenderPassManager& other) = default;
        RenderPassManager(RenderPassManager&& other) = default;
        RenderPassManager& operator=(RenderPassManager&& other) = default;
        ~RenderPassManager() = default;

        Components::RenderPassId RegisterRenderPass(
            const std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>>& pass)
        {
            static AtomFactory& renderPassIdFactory =
                AtomFactoryDatabase::GetFactory("NovelRT::Ecs::Graphics::RenderPassId");

            auto [it, inserted] = _registeredRenderPasses.emplace(std::make_tuple(pass, renderPassIdFactory.GetNext()));

            if (inserted)
            {
                _reverseRenderPassMapping[std::get<Components::RenderPassId>(*it)] = pass;
            }

            return std::get<Components::RenderPassId>(*it);
        }

        std::shared_ptr<NovelRT::Graphics::GraphicsRenderPass<TGraphicsBackend>> GetRenderPass(
            Components::RenderPassId id) const
        {
            return _reverseRenderPassMapping.at(id);
        }
    };
}
