// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/ResourceManagement/ResourceManagement.h>

namespace NovelRT::ResourceManagement
{
    void ResourceLoader::RegisterAsset(const std::filesystem::path& filePath)
    {
        static std::random_device rd;
        static auto seed_data = std::array<int, std::mt19937::state_size>{};
        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
        static std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
        static std::mt19937 generator(seq);
        static uuids::uuid_random_generator gen{generator};

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
