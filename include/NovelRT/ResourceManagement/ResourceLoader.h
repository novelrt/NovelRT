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
        std::map<uuids::uuid, std::filesystem::path> _guidsToFilePathsMap;
        std::map<std::filesystem::path, uuids::uuid> _filePathsToGuidsMap;
        bool _hasLoadedAssetDatabase = false;

    protected:
        std::filesystem::path _resourcesRootDirectory = Utilities::Misc::getExecutableDirPath() / "Resources";
        std::string _assetDatabaseFileName = "AssetDB.txt";

        [[nodiscard]] inline std::map<uuids::uuid, std::filesystem::path>& GetGuidsToFilePathsMap() noexcept
        {
            return _guidsToFilePathsMap;
        }

        [[nodiscard]] inline std::map<std::filesystem::path, uuids::uuid>& GetFilePathsToGuidsMap() noexcept
        {
            return _filePathsToGuidsMap;
        }

        virtual void WriteAssetDatabaseFile() = 0;
        virtual void LoadAssetDatabaseFile() = 0;

        uuids::uuid RegisterAsset(const std::filesystem::path& filePath);

    public:
        [[nodiscard]] inline std::filesystem::path& ResourcesRootDirectory() noexcept
        {
            return _resourcesRootDirectory;
        }

        [[nodiscard]] inline const std::filesystem::path& ResourcesRootDirectory() const noexcept
        {
            return _resourcesRootDirectory;
        }

        [[nodiscard]] inline const std::map<uuids::uuid, std::filesystem::path>& GetGuidsToFilePathsMap() const noexcept
        {
            return _guidsToFilePathsMap;
        }

        [[nodiscard]] inline const std::map<std::filesystem::path, uuids::uuid>& GetFilePathsToGuidsMap() const noexcept
        {
            return _filePathsToGuidsMap;
        }

        /**
         * @brief Loads a texture from a file on a given path.
         *
         * The path can be either relative or absolute.
         * When using a relative path it will look in the Resources/Images directory.
         *
         * @param filePath Relative or absolute path to the texture.
         * @returns TextureMetadata The texture data contained in the file.
         * @exception NovelRT::Exceptions::FileNotFoundException if there is no file at the specified location.
         */
        [[nodiscard]] virtual TextureMetadata LoadTexture(std::filesystem::path filePath) = 0;

        /**
         * @brief Loads shader from a file on a given path.
         *
         * The path can be either relative or absolute.
         * When using a relative path it will look in the Resources/Shaders directory.
         *
         * @param filePath Relative or absolute path to the shader.
         * @returns ShaderMetadata instance containing the shader bytecode and asset database handle.
         * @exception NovelRT::Exceptions::FileNotFoundException if there is no file at the specified location.
         */
        [[nodiscard]] virtual ShaderMetadata LoadShaderSource(std::filesystem::path filePath) = 0;

        [[nodiscard]] virtual BinaryPackage LoadPackage(std::filesystem::path fileName) = 0;

        virtual void SavePackage(std::filesystem::path filePath, const BinaryPackage& package) = 0;

        [[nodiscard]] virtual AudioMetadata LoadAudioFrameData(std::filesystem::path filePath) = 0;

        virtual ~ResourceLoader() = default;
    };
}

#endif // NOVELRT_RESOURCEMANAGEMENT_RESOURCELOADER_H
