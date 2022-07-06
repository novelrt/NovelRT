// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_RESOURCELOADER_H
#define NOVELRT_RESOURCEMANAGEMENT_RESOURCELOADER_H

#ifndef NOVELRT_RESOURCEMANAGEMENT_H
#error NovelRT does not support including types explicitly by default. Please include ResourceManagement.h instead for the ResourceManagement namespace subset.
#endif

namespace NovelRT::ResourceManagement
{
    class ResourceLoader : public std::enable_shared_from_this<ResourceLoader>
    {
    protected:
        std::filesystem::path _resourcesRootDirectory = Utilities::Misc::getExecutableDirPath() / "Resources";

    public:
        [[nodiscard]] inline std::filesystem::path& ResourcesRootDirectory() noexcept
        {
            return _resourcesRootDirectory;
        }

        [[nodiscard]] inline const std::filesystem::path& ResourcesRootDirectory() const noexcept
        {
            return _resourcesRootDirectory;
        }

        /**
         * @brief Loads texture from file on given path.
         *
         * Path can both be relative as well as absolute.
         * When using relative path it will look in the Resources + Images directory
         *
         * @param filePath Relative or absolute path to the texture
         * @return TextureMetadata of the file that was requested to load
         */
        [[nodiscard]] virtual TextureMetadata LoadTextureFromFile(std::filesystem::path filePath) = 0;

        /**
         * @brief Loads shader from file on given path.
         *
         * Path can both be relative as well as absolute.
         * When using relative path it will look in the Resources + Shaders directory
         *
         * @param filePath Relative or absolute path to the texture
         * @return TextureMetadata of the file that was requested to load
         */
        [[nodiscard]] virtual std::vector<uint8_t> LoadShaderSource(std::filesystem::path filePath) = 0;

        [[nodiscard]] virtual BinaryPackage LoadPackage(std::filesystem::path fileName) = 0;

        virtual void SavePackage(std::filesystem::path filePath, const BinaryPackage& package) = 0;

        virtual ~ResourceLoader() = default;
    };
}

#endif // NOVELRT_RESOURCEMANAGEMENT_RESOURCELOADER_H
