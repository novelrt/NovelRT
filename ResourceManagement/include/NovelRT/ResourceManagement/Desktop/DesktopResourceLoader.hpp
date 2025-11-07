#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/ResourceManagement/ResourceLoader.hpp>
#include <NovelRT/Logging/LoggingService.hpp>

namespace NovelRT::ResourceManagement::Desktop
{
    class DesktopResourceLoader final : public ResourceLoader
    {
    private:
        Logging::LoggingService _logger;
        bool _isAssetDBInitialised;

    protected:
        void WriteAssetDatabaseFile() final;
        void LoadAssetDatabaseFile() final;

    public:
        [[nodiscard]] inline bool GetIsAssetDBInitialised() const noexcept final
        {
            return _isAssetDBInitialised;
        }

        void InitAssetDatabase() final;
        [[nodiscard]] TextureMetadata LoadTexture(std::filesystem::path filePath) final;
        [[nodiscard]] TextureMetadata LoadTexture(uuids::uuid assetId) final;
        [[nodiscard]] ShaderMetadata LoadShaderSource(std::filesystem::path filePath) final;
        [[nodiscard]] ShaderMetadata LoadShaderSource(uuids::uuid assetId) final;
        [[nodiscard]] BinaryPackage LoadPackage(std::filesystem::path filePath) final;
        [[nodiscard]] BinaryPackage LoadPackage(uuids::uuid assetId) final;
        void SavePackage(std::filesystem::path filePath, const BinaryPackage& package) final;
        [[nodiscard]] AudioMetadata LoadAudioFrameData(std::filesystem::path filePath) final;
        [[nodiscard]] AudioMetadata LoadAudioFrameData(uuids::uuid assetId) final;
        [[nodiscard]] StreamableAssetMetadata GetStreamToAsset(std::filesystem::path filePath) final;
        [[nodiscard]] StreamableAssetMetadata GetStreamToAsset(uuids::uuid assetId) final;
        ~DesktopResourceLoader() final = default;
    };
}

