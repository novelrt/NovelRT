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
        char* returnPtr = nullptr;

#ifdef WIN32
        size_t length = cppPath.length() + 1;
        returnPtr = static_cast<char*>(malloc(length));
        strcpy_s(returnPtr, length, cppPath.c_str());
#else
    returnPtr = strdup(cppPath.c_str());
#endif

        return returnPtr;
    }

    const char* Nrt_getExecutableDirPath()
    {
        std::string cppPath = std::string(NovelRT::Utilities::Misc::getExecutableDirPath().string());
        char* returnPtr = nullptr;

#ifdef WIN32
        size_t length = cppPath.length() + 1;
        returnPtr = static_cast<char*>(malloc(length));
        strcpy_s(returnPtr, length, cppPath.c_str());
#else
    returnPtr = strdup(cppPath.c_str());
#endif

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

        char* finalPath = nullptr;
// strcpy_s is not included by all compilers that don't have __STDC_LIB_EXT1__ available, including clang.
#if defined(WIN32)
        finalPath = static_cast<char*>(malloc(finalString.length() + 1));

        if (finalPath == nullptr)
        {
            Nrt_setErrMsgIsOutOfMemoryInternal();
            return NULL;
        }

        strcpy_s(finalPath, finalString.length() + 1, finalString.c_str());
#else
    finalPath = strdup(finalString.c_str());
    if (finalPath == nullptr)
    {
        Nrt_setErrMsgIsOutOfMemoryInternal();
        return NULL;
    }
#endif
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
            Nrt_setErrMsgCustomInternal("Could not properly allocate memory for test!");
            return NULL;
        }

#if defined(WIN32)
        strcpy_s(finalText, finalString.length() + 1, finalString.c_str());
#else
    finalText = strdup(finalString.c_str());
#endif
        return finalText;
    }

#ifdef __cplusplus
}
#endif
