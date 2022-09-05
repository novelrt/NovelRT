// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_TEXTUREPERSISTENCERULE_H
#define NOVELRT_TEXTUREPERSISTENCERULE_H

namespace NovelRT::Persistence::Graphics
{
    class TexturePersistenceRule final : public ICustomSerialisationRule
    {
    private:
        std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> _renderingSystem;

    public:
        explicit TexturePersistenceRule(std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> renderingSystem) noexcept;

        [[nodiscard]] inline size_t GetSerialisedSize() const noexcept final
        {
            return sizeof(uuids::uuid) * 3;
        }

        [[nodiscard]] std::vector<uint8_t> ExecuteSerialiseModification(gsl::span<const uint8_t> component) const noexcept final;

        [[nodiscard]] std::vector<uint8_t> ExecuteDeserialiseModification(gsl::span<const uint8_t> component) const noexcept final;
    };
}

#endif // NOVELRT_TEXTUREPERSISTENCERULE_H
