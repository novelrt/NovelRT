// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/ResourceManagement/Desktop/ResourceManagement.Desktop.h>

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
            auto subStrings = Utilities::Misc::SplitString(line, ":");

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

    TextureMetadata DesktopResourceLoader::LoadTexture(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Images" / filePath;
        }

        std::string filePathStr = filePath.string();
        FILE* cFile;
#if defined(__STDC_LIB_EXT1__) || defined(_MSC_VER)
        // todo: replace with file not found exc
        _logger.throwIfNotZero(
            fopen_s(&cFile, filePathStr.c_str(), "rb"),
            "Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");
#else
        cFile = fopen(filePathStr.c_str(), "rb");
        _logger.throwIfNullPtr(
            cFile, "Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");
#endif

        auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr,
                                          nullptr); // TODO: Figure out how the error function ptr works

        if (png == nullptr)
        {
            _logger.logError(
                "Image file cannot be opened! Please ensure the path is correct and that the file is not locked.");
            throw Exceptions::FileNotFoundException(filePath.string(),
                                                    "Unable to continue! File failed to load for texture. Please "
                                                    "ensure the path is correct and that the file is not locked.");
        }

        auto info = png_create_info_struct(png);

        if (info == nullptr)
        {
            _logger.logError("Image at path {} failed to provide an info struct! Aborting...", filePath.string());
            throw Exceptions::IOException(filePath.string(),
                                          "Unable to continue! File failed to provide an info struct.");
        }

        if (setjmp(png_jmpbuf(png)))
        { // This is how libpng does error handling.
            _logger.logError("Image at path {} appears to be corrupted! Aborting...", filePath.string());
            throw Exceptions::IOException(filePath.string(), "Unable to continue! File appears to be corrupted.");
        }

        png_init_io(png, cFile);
        png_read_info(png, info);

        ImageData data;
        data.width = png_get_image_width(png, info);
        data.height = png_get_image_height(png, info);
        data.colourType = png_get_color_type(png, info);
        data.bitDepth = png_get_bit_depth(png, info);

        if (data.bitDepth == 16)
            png_set_strip_16(png);

        if (data.colourType == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png);

        if (data.colourType == PNG_COLOR_TYPE_GRAY && data.bitDepth < 8)
            png_set_expand_gray_1_2_4_to_8(png);

        if (png_get_valid(png, info, PNG_INFO_tRNS))
            png_set_tRNS_to_alpha(png);

        if (data.colourType == PNG_COLOR_TYPE_RGB || data.colourType == PNG_COLOR_TYPE_GRAY ||
            data.colourType == PNG_COLOR_TYPE_PALETTE)
        { // id one line this but it looks ugly
            png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
        }

        if (data.colourType == PNG_COLOR_TYPE_GRAY || data.colourType == PNG_COLOR_TYPE_GRAY_ALPHA)
            png_set_gray_to_rgb(png);

        png_read_update_info(png, info);

        auto rowBytes = png_get_rowbytes(png, info);
        auto bpp = static_cast<uint32_t>(rowBytes) / data.width;

        // Allows us to get the final image data, not interlaced.
        png_set_interlace_handling(png);

        // Props to Kenny for debugging this without asking me and saving me the mental strain lmao
        auto pixelBufferAmount = (data.width * data.height * bpp);
        auto rawImage = new unsigned char[pixelBufferAmount]; // We allocate the pixel buffer here.

        if (rawImage == nullptr)
        {
            png_destroy_read_struct(&png, &info, nullptr);
            fclose(cFile);
            throw Exceptions::OutOfMemoryException(
                std::string("Couldn't allocate space for PNG, file: \"").append(filePath.string()).append("\"."));
        }

        data.rowPointers = new png_bytep[data.height]; // Setup row pointer array and set it into the pixel buffer.
        uint8_t* p = reinterpret_cast<uint8_t*>(rawImage);

        // TODO: Proper error check on data.rowPointers
        if (data.rowPointers == nullptr)
        {
            _logger.logError("Unable to continue! Couldn't allocate memory for the PNG pixel data! Aborting...");
            throw Exceptions::OutOfMemoryException(std::string("Could not allocate memory for pixel data from \"")
                                                       .append(filePath.string())
                                                       .append("\"."));
        }

        for (uint32_t i = 0; i < data.height; i++)
        {
            data.rowPointers[i] = p;
            p += data.width * bpp;
        }

        // Read all the rows (data will flow into the pixel buffer)
        png_read_image(png, data.rowPointers);
        png_read_end(png, info); // Finish reading the file - this will also check for corruption

        fclose(cFile);

        std::vector<uint8_t> returnImage{};

        size_t finalLength = data.width * data.height;

        returnImage.reserve(finalLength * 4);

        for (size_t i = 0; i < finalLength * 4; ++i)
        {
            returnImage.emplace_back(rawImage[i]);
        }

        if (data.colourType != PNG_COLOR_TYPE_RGBA)
        {
            throw std::runtime_error("reeeeeeee");
        }

        delete[] rawImage;
        delete[] data.rowPointers;
        png_destroy_read_struct(&png, &info, nullptr);

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        RegisterAsset(relativePathForAssetDatabase);

        return TextureMetadata{returnImage, data.width, data.height, finalLength};
    }

    std::vector<uint8_t> DesktopResourceLoader::LoadShaderSource(std::filesystem::path filePath)
    {
        if (filePath.is_relative())
        {
            filePath = _resourcesRootDirectory / "Shaders" / filePath;
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
        RegisterAsset(relativePathForAssetDatabase);

        return buffer;
    }

    BinaryPackage DesktopResourceLoader::LoadPackage(std::filesystem::path filePath)
    {
        filePath = _resourcesRootDirectory / filePath;

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

        jsoncons::json j = jsoncons::bson::decode_bson<jsoncons::json>(buffer);
        jsoncons::json metadata = j["memberMetadata"];

        for (auto&& obj : metadata.array_value())
        {
            BinaryMemberMetadata newMemberMetadata{
                obj["name"].as<std::string>(), static_cast<BinaryDataType>(obj["type"].as<uint32_t>()),
                obj["location"].as<size_t>(),  obj["sizeOfTypeInBytes"].as<size_t>(),
                obj["length"].as<size_t>(),    obj["sizeOfSerialisedDataInBytes"].as<size_t>()};

            package.memberMetadata.emplace_back(newMemberMetadata);
        }

        package.data = j["data"].as<std::vector<uint8_t>>();

        auto relativePathForAssetDatabase = std::filesystem::relative(filePath, _resourcesRootDirectory);
        RegisterAsset(relativePathForAssetDatabase);

        return package;
    }

    void DesktopResourceLoader::SavePackage(std::filesystem::path filePath, const BinaryPackage& package)
    {
        filePath = _resourcesRootDirectory / filePath;

        jsoncons::json j(jsoncons::json_object_arg);
        std::vector<jsoncons::json> memberMetadataJson{};

        for (auto&& member : package.memberMetadata)
        {
            jsoncons::json newMemberJson(jsoncons::json_object_arg);

            newMemberJson["name"] = member.name;
            newMemberJson["type"] = static_cast<uint32_t>(member.type);
            newMemberJson["location"] = member.location;
            newMemberJson["sizeOfTypeInBytes"] = member.sizeOfTypeInBytes;
            newMemberJson["length"] = member.length;
            newMemberJson["sizeOfSerialisedDataInBytes"] = member.sizeOfSerialisedDataInBytes;

            memberMetadataJson.emplace_back(newMemberJson);
        }

        j["memberMetadata"] = memberMetadataJson;
        j["data"] = package.data;

        std::vector<uint8_t> buffer{};
        jsoncons::bson::encode_bson(j, buffer);

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
}
