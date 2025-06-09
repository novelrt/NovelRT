#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <filesystem>

namespace NovelRT::Utilities
{
    /**
     * @brief Gets the path to the executable.
     *
     * @return The path to the executable.
     */
    std::filesystem::path GetExecutablePath();

    /**
     * @brief Gets the path to the directory that contains the executable. <br/>
     * For example, `/home/stuff/game/best-game-executable` will return `/home/stuff/game`
     *
     * @return The path to the directory that contains the executable.
     */
    std::filesystem::path GetExecutableDirPath();
}
