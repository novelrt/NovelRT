// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_PERSISTABLE_H
#define NOVELRT_PERSISTENCE_PERSISTABLE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class Persistable
    {
    protected:
        void ApplySerialisationRule(const std::string& serialisedName,
                                    NovelRT::Utilities::Misc::Span<const uint8_t> componentData,
                                    NovelRT::Utilities::Misc::Span<uint8_t> writeToData) const;

        void ApplyDeserialisationRule(const std::string& serialisedName,
                                      NovelRT::Utilities::Misc::Span<const uint8_t> serialisedData,
                                      NovelRT::Utilities::Misc::Span<uint8_t> writeToData) const;

    public:
        [[nodiscard]] static std::unordered_map<std::string, std::unique_ptr<ICustomSerialisationRule>>&
        GetSerialisationRules() noexcept;

        [[nodiscard]] static std::unordered_map<std::string, std::unique_ptr<ICustomComponentLoadRule>>&
        GetComponentLoadRules() noexcept;

        static void LoadDefaultRules(std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> renderingSystem) noexcept;

        [[nodiscard]] virtual ResourceManagement::BinaryPackage ToFileData() const noexcept = 0;
        virtual void LoadFileData(const ResourceManagement::BinaryPackage& data) = 0;
    };
}

#endif // NOVELRT_PERSISTENCE_PERSISTABLE_H
