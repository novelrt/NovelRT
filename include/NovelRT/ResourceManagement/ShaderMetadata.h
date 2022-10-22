// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_SHADERMETADATA_H
#define NOVELRT_RESOURCEMANAGEMENT_SHADERMETADATA_H

#ifndef NOVELRT_RESOURCEMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include ResourceManagement.h instead for the ResourceManagement namespace subset.
#endif

namespace NovelRT::ResourceManagement
{
    struct ShaderMetadata
    {
        std::vector<uint8_t> shaderCode;
        uuids::uuid databaseHandle;
    };
}

#endif // NOVELRT_RESOURCEMANAGEMENT_SHADERMETADATA_H
