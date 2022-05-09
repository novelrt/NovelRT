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
    private:
        std::filesystem::path _resourcesRootDirectory = Utilities::Misc::getExecutableDirPath() / "Resources";

    protected:
        [[nodiscard]] virtual TextureMetadata LoadTexture(
            std::filesystem::path filePath) = 0; // TODO: I've realised these should probably be overloads, not internal
                                                 // methods. Monke brain. :(
        [[nodiscard]] virtual std::vector<uint8_t> LoadShaderSourceInternal(std::filesystem::path filePath) = 0;

    public:
        [[nodiscard]] inline std::filesystem::path& ResourcesRootDirectory() noexcept
        {
            return _resourcesRootDirectory;
        }

        [[nodiscard]] inline const std::filesystem::path& ResourcesRootDirectory() const noexcept
        {
            return _resourcesRootDirectory;
        }

        [[nodiscard]] inline TextureMetadata LoadTextureFromFile(const std::string& fileName)
        {
            return LoadTexture(_resourcesRootDirectory / "Images" /
                               fileName); // TODO: This should probably either be textures or sprites, not image? Thonk.
        }

        [[nodiscard]] inline std::vector<uint8_t> LoadShaderSource(const std::string& fileName)
        {
            return LoadShaderSourceInternal(_resourcesRootDirectory / "Shaders" / fileName);
        }

        //[[nodiscard]] inline Persistence::BinaryPackage LoadPackage(const std::string& fileName) = 0;

        virtual ~ResourceLoader() = default;
    };
}

#endif // NOVELRT_RESOURCEMANAGEMENT_RESOURCELOADER_H
