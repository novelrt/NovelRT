// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_GRAPHICS_RENDERINGCOMPONENTPERSISTENCERULE_H
#define NOVELRT_PERSISTENCE_GRAPHICS_RENDERINGCOMPONENTPERSISTENCERULE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence::Graphics
{
    class RenderingComponentPersistenceRule final : public ICustomSerialisationRule
    {
    private:
        std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> _renderingSystem;

    public:
        explicit RenderingComponentPersistenceRule(
            std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> renderingSystem) noexcept;

        [[nodiscard]] inline size_t GetSerialisedSize() const noexcept final
        {
            return sizeof(uuids::uuid) * 3;
        }

        [[nodiscard]] std::vector<uint8_t> ExecuteSerialiseModification(
            NovelRT::Core::Utilities::Misc::Span<const uint8_t> component) const noexcept final;

        [[nodiscard]] std::vector<uint8_t> ExecuteDeserialiseModification(
            NovelRT::Core::Utilities::Misc::Span<const uint8_t> component) const noexcept final;
    };
}

#endif // NOVELRT_PERSISTENCE_GRAPHICS_RENDERINGCOMPONENTPERSISTENCERULE_H
