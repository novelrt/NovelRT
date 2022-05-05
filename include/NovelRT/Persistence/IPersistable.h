// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IPERSISTABLE_H
#define NOVELRT_IPERSISTABLE_H

namespace NovelRT::Persistence
{
    class IPersistable
    {
    public:
        struct ComponentBufferInformation
        {
            size_t amountOfEntities;
            size_t sizeOfComponentType;
            std::vector<uint8_t> entityComponentData;
        };

        [[nodiscard]] virtual std::map<std::string, ComponentBufferInformation> ToFileData() const noexcept = 0;
        virtual void LoadFileData(const std::map<std::string, ComponentBufferInformation>& data) noexcept = 0;
    };
}

#endif // NOVELRT_IPERSISTABLE_H
