// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCELOADER_H
#define NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCELOADER_H

#ifndef NOVELRT_RESOURCEMANAGEMENT_DESKTOP_H
#error NovelRT does not support including types explicitly by default. Please include ResourceManagement.Desktop.h instead for the ResourceManagement::Desktop namespace subset.
#endif

namespace NovelRT::ResourceManagement::Desktop
{
    class DesktopResourceLoader final : public ResourceLoader
    {
    private:
        LoggingService _logger;

    protected:
        void WriteAssetDatabaseFile() final;
        void LoadAssetDatabaseFile() override;

    public:
        [[nodiscard]] TextureMetadata LoadTexture(std::filesystem::path filePath) final;
        [[nodiscard]] std::vector<uint8_t> LoadShaderSource(std::filesystem::path filePath) final;
        [[nodiscard]] BinaryPackage LoadPackage(std::filesystem::path filePath) final;
        void SavePackage(std::filesystem::path filePath, const BinaryPackage& package) final;
        ~DesktopResourceLoader() final = default;
    };
}

#endif // !NOVELRT_RESOURCEMANAGEMENT_DESKTOP_DESKTOPRESOURCELOADER_H
