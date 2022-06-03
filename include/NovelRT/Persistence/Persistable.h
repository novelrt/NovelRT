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
    private:
        static std::unordered_map<std::string, std::unique_ptr<ICustomSerialisationRule>> _serialisationRules;

    protected:
        inline void ApplySerialisationRule(const std::string& serialisedName, uint8_t* componentData) const
        {

        }

    public:
        [[nodiscard]] inline static std::unordered_map<std::string, std::unique_ptr<ICustomSerialisationRule>>& GetSerialisationRules() noexcept
        {
            return _serialisationRules;
        }

        [[nodiscard]] virtual ResourceManagement::BinaryPackage ToFileData() const noexcept = 0;
        virtual void LoadFileData(const ResourceManagement::BinaryPackage& data) = 0;
    };
}

#endif // NOVELRT_PERSISTENCE_PERSISTABLE_H
