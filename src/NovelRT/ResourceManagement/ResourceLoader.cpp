// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/ResourceManagement/ResourceManagement.h>

namespace NovelRT::ResourceManagement
{
    void ResourceLoader::RegisterAsset(const std::filesystem::path& filePath)
    {
        if (!_hasLoadedAssetDatabase)
        {
            _hasLoadedAssetDatabase = true;
            LoadAssetDatabaseFile();
        }

        auto& pathGuidMap = GetFilePathsToGuidsMap();

        auto it = pathGuidMap.find(filePath);

        if (it == pathGuidMap.end())
        {
            auto& guidPathMap = GetGuidsToFilePathsMap();

            std::random_device rd;
            auto seed_data = std::array<int, std::mt19937::state_size> {};
            std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
            std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
            std::mt19937 generator(seq);
            uuids::uuid_random_generator gen{generator};

            uuids::uuid guid = gen();

            while (guidPathMap.find(guid) != guidPathMap.end())
            {
                guid = gen();
            }

            guidPathMap.emplace(guid, filePath);
            pathGuidMap.emplace(filePath, guid);
        }

        WriteAssetDatabaseFile();
    }
}