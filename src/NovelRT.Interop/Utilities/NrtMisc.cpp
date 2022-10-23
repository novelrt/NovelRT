// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Utilities/NrtMisc.h>
#include <NovelRT/NovelRT.h>
#include <cstring>

#ifdef __cplusplus
extern "C"
{
#endif

    const char* Nrt_getExecutablePath()
    {
        std::string cppPath = std::string(NovelRT::Utilities::Misc::getExecutablePath().string());

        size_t length = cppPath.length() + 1;
        char* returnPtr = static_cast<char*>(malloc(length));
        strcpy(returnPtr, cppPath.c_str());

        return returnPtr;
    }

    const char* Nrt_getExecutableDirPath()
    {
        std::string cppPath = std::string(NovelRT::Utilities::Misc::getExecutableDirPath().string());

        size_t length = cppPath.length() + 1;
        char* returnPtr = static_cast<char*>(malloc(length));
        strcpy(returnPtr, cppPath.c_str());

        return returnPtr;
    }

    const char* Nrt_appendFilePath(int32_t numberOfArgs, const char* const* args)
    {
        if (numberOfArgs <= 1)
        {
            Nrt_setErrMsgCustomInternal("Cannot append file path when nothing is being appended!");
            return NULL;
        }

        const char* dirMarker = static_cast<const char*>("/");
#if defined(WIN32)
        dirMarker = "\\";
#endif

        std::string finalString = "";

        for (int i = 0; i < numberOfArgs; i++)
        {
            const char* arg = args[i];
            std::cout << arg << std::endl;
            finalString.append(arg);
            if (i < numberOfArgs - 1)
            {
                finalString.append(dirMarker);
            }
        }

        char* finalPath = static_cast<char*>(malloc(finalString.length() + 1));

        if (finalPath == nullptr)
        {
            Nrt_setErrMsgIsOutOfMemoryInternal();
            return NULL;
        }

        strcpy(finalPath, finalString.c_str());

        return finalPath;
    }

    const char* Nrt_appendText(int32_t numberOfArgs, const char* const* args)
    {
        if (numberOfArgs <= 1)
        {
            Nrt_setErrMsgCustomInternal("Cannot append text when nothing is being appended!");
            return NULL;
        }

        std::string finalString = "";

        for (int i = 0; i < numberOfArgs; i++)
        {
            finalString.append(args[i]);
        }

        char* finalText = new char[finalString.length() + 1];
        if (strlen(finalText) < (finalString.length() + 1))
        {
            Nrt_setErrMsgCustomInternal("Could not properly allocate memory for text!");
            return NULL;
        }

        strcpy(finalText, finalString.c_str());

        return finalText;
    }

#ifdef __cplusplus
}
#endif
