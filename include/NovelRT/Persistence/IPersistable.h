// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IPERSISTABLE_H
#define NOVELRT_IPERSISTABLE_H

namespace NovelRT::Persistence
{
    class IPersistable
    {
    public:
        [[nodiscard]] virtual ResourceManagement::BinaryPackage ToFileData() const noexcept = 0;
        virtual void LoadFileData(const ResourceManagement::BinaryPackage& data) = 0;
    };
}

#endif // NOVELRT_IPERSISTABLE_H
