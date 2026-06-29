// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Exceptions/FileNotFoundException.hpp>
#include <NovelRT/Exceptions/IOException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/ResourceManagement/Desktop/DesktopResourceLoader.hpp>
#include <NovelRT/ResourceManagement/Desktop/ImageData.hpp>
#include <NovelRT/Utilities/Strings.hpp>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <png.h>
#include <samplerate.h>
#include <sndfile.h>

namespace NovelRT::ResourceManagement::Desktop
{
    void DesktopResourceLoader::LoadAssetDatabaseFile()
    {
        auto filePath = _resourcesRootDirectory / _assetDatabaseFileName;
        std::ifstream file(filePath);

        if (!file.is_open())
        {
            std::ofstream unusedOutputStream(filePath);
            unusedOutputStream.close();

            file = std::ifstream(filePath);
            if (!file.is_open())
            {
                throw NovelRT::Exceptions::IOException(
                    filePath.string(),
                    "Unable to open asset database file even after a creation attempt. Please validate that there is "
                    "room on the local disk, and that folder permissions are correct.");
            }
        }

        auto& guidToPathMap = GetGuidsToFilePathsMap();
        auto& pathToGuidMap = GetFilePathsToGuidsMap();

        std::string line;
        while (std::getline(file, line))
        {
            auto subStrings = Utilities::SplitString(line, ":");

            if (subStrings.size() != 2)
            {
                throw Exceptions::InvalidOperationException(
                    "Invalid record detected in asset database. Is the asset database corrupted?");
            }

            auto parsedGuid = uuids::uuid::from_string(subStrings[0]).value();
            auto parsedAssetPath = std::filesystem::path(subStrings[1]);

            guidToPathMap.emplace(parsedGuid, parsedAssetPath);
            pathToGuidMap.emplace(parsedAssetPath, parsedGuid);
        }
    }

    void DesktopResourceLoader::WriteAssetDatabaseFile()
    {
        auto filePath = _resourcesRootDirectory / _assetDatabaseFileName;
        std::ofstream inputStream(filePath);

        if (!inputStream.is_open())
        {
            throw NovelRT::Exceptions::IOException(
                filePath.string(), "Unable to open asset database file for append-write. Please validate that there is "
                                   "room on the local disk, and that folder permissions are correct.");
        }

        auto& guidToPathMap = GetGuidsToFilePathsMap();

        std::string pathStr;
        for (auto [guid, path] : guidToPathMap)
        {
            pathStr = path.string();
            std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
            inputStream << to_string(guid) << ":" << pathStr << '\n';
        }

        inputStream.flush();
        inputStream.close();
    }

    void DesktopResourceLoader::InitAssetDatabase()
    {
        auto filePath = _resourcesRootDirectory;

        LoadAssetDatabaseFile();

        std::vector<uuids::uuid> filesToUnregister{};

        for (auto [path, guid] : GetFilePathsToGuidsMap())
        {
            if (std::filesystem::exists(path))
            {
                filesToUnregister.emplace_back(guid);
            }
        }

        for (const auto& guid : filesToUnregister)
        {
            UnregisterAssetNoFileWrite(guid);
        }

        for (const auto& directoryEntry : std::filesystem::recursive_directory_iterator(filePath))
        {
            if (!directoryEntry.is_regular_file() ||
                directoryEntry.path().filename().string().find("AssetDB") != std::string::npos)
            {
                continue;
            }

            RegisterAsset(std::filesystem::relative(directoryEntry.path(), filePath));
        }

        WriteAssetDatabaseFile();

        _isAssetDBInitialised = true;
    }

    TextureMetadata DesktopResourceLoader::LoadTexture(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Images" / filePath.filename();
        }

        std::ifstream file(filePath.string(), std::ios::binary);
        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        auto handle_error = [](png_structp png, png_const_charp message)
        {
            auto* logger = static_cast<NovelRT::Logging::LoggingService*>(png_get_error_ptr(png));
            logger->logError("libpng error: {}", message);
            throw Exceptions::InvalidOperationException("LibPNG error occured");
        };

        auto handle_warning = [](png_structp png, png_const_charp message)
        {
            auto* logger = static_cast<NovelRT::Logging::LoggingService*>(png_get_error_ptr(png));
            logger->logWarning("libpng warning: {}", message);
        };

        auto* png = png_create_read_struct(PNG_LIBPNG_VER_STRING, &_logger, handle_error, handle_warning);
        if (png == nullptr)
        {
            throw Exceptions::InvalidOperationException("Failed to create libpng read struct");
        }

        auto read = [](png_structp png, png_bytep data, size_t length)
        {
            auto* stream = static_cast<std::ifstream*>(png_get_io_ptr(png));
            stream->read(reinterpret_cast<char*>(data), std::streamsize(length));
        };

        png_set_read_fn(png, &file, read);

        auto* info = png_create_info_struct(png);
        if (info == nullptr)
        {
            _logger.logError("Image at path {} failed to provide an info struct! Aborting...", filePath.string());
            throw Exceptions::IOException(filePath.string(),
                                          "Unable to continue! File failed to provide an info struct.");
        }

        png_read_info(png, info);

        struct
        {
            uint32_t width;
            uint32_t height;
            png_byte colourType;
            png_byte bitDepth;
            png_byte interlaceType;
            int interlacePasses;
        } data = {
            .width = png_get_image_width(png, info),
            .height = png_get_image_height(png, info),
            .colourType = png_get_color_type(png, info),
            .bitDepth = png_get_bit_depth(png, info),
            .interlaceType = png_get_interlace_type(png, info),
            .interlacePasses = 0
        };

        if (data.bitDepth == 16)
        {
            png_set_strip_16(png);
        }

        if (data.colourType == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(png);
        }
        else if (data.colourType == PNG_COLOR_TYPE_GRAY && data.bitDepth < 8)
        {
            png_set_expand_gray_1_2_4_to_8(png);
        }
        else if (data.colourType == PNG_COLOR_TYPE_GRAY || data.colourType == PNG_COLOR_TYPE_GRAY_ALPHA)
        {
            png_set_gray_to_rgb(png);
        }

        if (data.colourType == PNG_COLOR_TYPE_RGB ||
            data.colourType == PNG_COLOR_TYPE_GRAY ||
            data.colourType == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
        }

        if (png_get_valid(png, info, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(png);
        }

        if (data.interlaceType != PNG_INTERLACE_NONE)
        {
            data.interlacePasses = png_set_interlace_handling(png);
        }

        png_read_update_info(png, info);

        auto bytesPerRow = png_get_rowbytes(png, info);
        std::vector<uint8_t> pixels(bytesPerRow * data.height);
        std::vector<png_bytep> rowPointers(data.height);
        std::generate(rowPointers.begin(), rowPointers.end(),
                      [base = pixels.data(), rowSize = bytesPerRow, offset = 0]() mutable
                      { return base + (offset++ * rowSize); });

        png_read_image(png, rowPointers.data());
        png_read_end(png, info);

        png_destroy_read_struct(&png, &info, nullptr);
        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);

        return TextureMetadata{pixels, data.width, data.height, pixels.size(),
                               RegisterAsset(relativePathForAssetDatabase)};
    }

    TextureMetadata DesktopResourceLoader::LoadTexture(uuids::uuid assetId)
    {
        return LoadTexture(GetGuidsToFilePathsMap().at(assetId));
    }

    ShaderMetadata DesktopResourceLoader::LoadShaderSource(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Shaders" / filePath.filename();
        }

        std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<uint8_t> buffer(fileSize);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()),
                  std::streamsize(fileSize)); // TODO: Why on earth do we have to cast to char*?!
        file.close();

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);

        return ShaderMetadata{buffer, RegisterAsset(relativePathForAssetDatabase)};
    }

    ShaderMetadata DesktopResourceLoader::LoadShaderSource(uuids::uuid assetId)
    {
        return LoadShaderSource(GetGuidsToFilePathsMap().at(assetId));
    }

    ScriptMetadata DesktopResourceLoader::LoadScript(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Scripts" / filePath.filename();
        }

        std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<uint8_t> buffer(fileSize);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(fileSize));
        file.close();

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);

        bool is_precompiled = buffer.size() >= 4 && std::all_of(buffer.begin(), std::next(buffer.begin(), 4),
                                                                [i = 0](const auto c) mutable
                                                                {
                                                                    // Precompiled Lua code always starts with
                                                                    // '<esc>Lua'
                                                                    constexpr const char signature[] = "\x1bLua";

                                                                    return c == signature[i++];
                                                                });

        return ScriptMetadata{is_precompiled, buffer, RegisterAsset(relativePathForAssetDatabase)};
    }

    ScriptMetadata DesktopResourceLoader::LoadScript(uuids::uuid assetId)
    {
        return LoadScript(GetGuidsToFilePathsMap().at(assetId));
    }

    PlaintextAsset DesktopResourceLoader::LoadPlaintextAsset(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / filePath.filename();
        }

        std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<uint8_t> buffer(fileSize);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()),
                  std::streamsize(fileSize)); // TODO: Why on earth do we have to cast to char*?!
        file.close();

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);

        return PlaintextAsset{buffer, RegisterAsset(relativePathForAssetDatabase)};
    }

    PlaintextAsset DesktopResourceLoader::LoadPlaintextAsset(uuids::uuid assetId)
    {
        return LoadPlaintextAsset(GetGuidsToFilePathsMap().at(assetId));
    }

    FontMetadata DesktopResourceLoader::LoadFont(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Fonts" / filePath.filename();
        }

        std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<uint8_t> buffer(fileSize);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(fileSize));
        file.close();

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);

        return FontMetadata{buffer, fileSize, RegisterAsset(relativePathForAssetDatabase)};
    }

    FontMetadata DesktopResourceLoader::LoadFont(uuids::uuid assetId)
    {
        return LoadFont(GetGuidsToFilePathsMap().at(assetId));
    }

    BinaryPackage DesktopResourceLoader::LoadPackage(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / filePath;
        }

        std::ifstream file(filePath.string(), std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<uint8_t> buffer(fileSize);
        file.seekg(0);
        file.read(reinterpret_cast<char*>(buffer.data()), std::streamsize(fileSize));
        file.close();

        BinaryPackage package{};
        package.memberMetadata = {};

        auto j = nlohmann::json::from_bson(buffer);
        auto metadata = j["memberMetadata"];

        for (auto&& obj : metadata)
        {
            BinaryMemberMetadata newMemberMetadata{obj.value<std::string>("name", std::string()),
                                                   obj.value<BinaryDataType>("type", BinaryDataType::NullOrUnknown),
                                                   obj.value<size_t>("location", 0),
                                                   obj.value<size_t>("sizeOfTypeInBytes", 0),
                                                   obj.value<size_t>("length", 0),
                                                   obj.value<size_t>("sizeOfSerialisedDataInBytes", 0)};

            package.memberMetadata.emplace_back(newMemberMetadata);
        }

        package.data = j.value<std::vector<uint8_t>>("data", std::vector<uint8_t>());

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        package.databaseHandle = RegisterAsset(relativePathForAssetDatabase);

        return package;
    }

    BinaryPackage DesktopResourceLoader::LoadPackage(uuids::uuid assetId)
    {
        return LoadPackage(GetGuidsToFilePathsMap().at(assetId));
    }

    void DesktopResourceLoader::SavePackage(std::filesystem::path filePath, const BinaryPackage& package)
    {
        filePath = _resourcesRootDirectory / filePath;

        nlohmann::json j{};
        nlohmann::json memberMetadataJson = nlohmann::json::array();

        for (auto&& member : package.memberMetadata)
        {
            nlohmann::json newMemberJson{};

            newMemberJson["name"] = member.name;
            newMemberJson["type"] = member.type;
            newMemberJson["location"] = member.location;
            newMemberJson["sizeOfTypeInBytes"] = member.sizeOfTypeInBytes;
            newMemberJson["length"] = member.length;
            newMemberJson["sizeOfSerialisedDataInBytes"] = member.sizeOfSerialisedDataInBytes;

            memberMetadataJson.push_back(newMemberJson);
        }

        j["memberMetadata"] = memberMetadataJson;
        j["data"] = package.data;

        std::vector<uint8_t> buffer = nlohmann::json::to_bson(j);

        std::ofstream file(filePath.string(), std::ios::out | std::ios::binary);

        if (!file.is_open())
        {
            throw NovelRT::Exceptions::InvalidOperationException("Unable to create file at " + filePath.string());
        }

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        RegisterAsset(relativePathForAssetDatabase);

        file.write(reinterpret_cast<const char*>(buffer.data()), std::streamsize(buffer.size()));
        file.close();
    }

    AudioMetadata DesktopResourceLoader::LoadAudioFrameData(std::filesystem::path filePath)
    {
        constexpr size_t _bufferSize = 2048;
        constexpr int32_t _sampleRate = 44100;

        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Audio" / filePath.filename();
        }

        SF_INFO info;
        info.format = 0;
        auto filePathString = filePath.string();
        SNDFILE* file = sf_open(filePathString.c_str(), SFM_READ, &info);

        if (file == nullptr)
        {
            throw NovelRT::Exceptions::IOException(filePath.string(), std::string(sf_strerror(file)));
        }

        std::vector<float> data;
        std::vector<float> readBuffer;
        readBuffer.resize(_bufferSize);

        sf_count_t readSize = 0;

        while ((readSize = sf_read_float(file, readBuffer.data(), static_cast<sf_count_t>(readBuffer.size()))) != 0)
        {
            data.insert(data.end(), readBuffer.begin(), readBuffer.begin() + readSize);
        }

        sf_close(file);

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        uuids::uuid databaseHandle = RegisterAsset(relativePathForAssetDatabase);

        if (info.samplerate != _sampleRate)
        {
            _logger.logDebug("Detected sample rate of {0}", info.samplerate);
            info.samplerate > 44100 ? _logger.logDebug("Downscaling...") : _logger.logDebug("Upscaling...");
            std::vector<float> resampledData = std::vector<float>(data.size());
            SRC_DATA conversionInfo = SRC_DATA{};
            conversionInfo.data_in = data.data();
            conversionInfo.data_out = resampledData.data();
            conversionInfo.input_frames = static_cast<long>(
                info.channels == 1
                    ? data.size()
                    : data.size() / static_cast<size_t>(info.channels)); // This is a mess, good lord. - Matt J.
            conversionInfo.output_frames = conversionInfo.input_frames;
            double rate = 44100.0 / static_cast<double>(info.samplerate);
            _logger.logDebug("Scaling by ratio of {0:f}", rate);
            conversionInfo.src_ratio = rate;
            int result = src_simple(&conversionInfo, SRC_SINC_MEDIUM_QUALITY, info.channels);
            if (result != 0)
            {
                std::string err = src_strerror(result);
                _logger.logErrorLine(err);
                throw new NovelRT::Exceptions::InvalidOperationException(err);
            }

            return AudioMetadata{resampledData, info.channels, _sampleRate, databaseHandle};
        }

        return AudioMetadata{data, info.channels, info.samplerate, databaseHandle};
    }

    AudioMetadata DesktopResourceLoader::LoadAudioFrameData(uuids::uuid assetId)
    {
        return LoadAudioFrameData(GetGuidsToFilePathsMap().at(assetId));
    }

    StreamableAssetMetadata DesktopResourceLoader::GetStreamToAsset(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / filePath;
        }

        auto file = std::make_unique<std::ifstream>(filePath.string());

        if (!file->is_open())
        {
            throw NovelRT::Exceptions::FileNotFoundException(filePath.string());
        }

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        uuids::uuid databaseHandle = RegisterAsset(relativePathForAssetDatabase);

        return StreamableAssetMetadata{std::move(file), databaseHandle};
    }

    StreamableAssetMetadata DesktopResourceLoader::GetStreamToAsset(uuids::uuid assetId)
    {
        return GetStreamToAsset(GetGuidsToFilePathsMap().at(assetId));
    }
}
