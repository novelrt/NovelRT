NovelRT
=======

NovelRT is a cross-platform, flexible Visual Novel and 2D game engine. It is aimed at designers and developers alike, however many of the designer tools and features we have on our roadmap have yet to be implemented.

| Job | Debug Status | Release Status |
| --- | ------------ | -------------- |
| Windows x64 | [![Build Status](https://github.com/novelrt/NovelRT/workflows/Windows%20x64%20-%20Debug/badge.svg?event=schedule)](https://github.com/novelrt/NovelRT/actions?query=workflow%3A%22Windows+x64+-+Debug%22) | [![Build Status](https://github.com/novelrt/NovelRT/workflows/Windows%20x64%20-%20Release/badge.svg?event=schedule)](https://github.com/novelrt/NovelRT/actions?query=workflow%3A%22Windows+x64+-+Release%22) |
| Ubuntu x64 | [![Build Status](https://github.com/novelrt/NovelRT/workflows/Ubuntu%20x64%20-%20Debug/badge.svg?event=schedule)](https://github.com/novelrt/NovelRT/actions?query=workflow%3A%22Ubuntu+x64+-+Debug%22) | [![Build Status](https://github.com/novelrt/NovelRT/workflows/Ubuntu%20x64%20-%20Release/badge.svg?event=schedule)](https://github.com/novelrt/NovelRT/actions?query=workflow%3A%22Ubuntu+x64+-+Release%22) |

[![Discord](https://discordapp.com/api/guilds/543898968380145675/widget.png?style=banner2)](https://discord.novelrt.dev/)

## Current Features

Currently, NovelRT supports the following in its base form:
- Graphics LLAPI
- Audio LLAPI

## Future & Immediate Improvements

Current features in development include:
- C++ HLAPI
- CoreCLR hosting
- Ink narrative scripting language support

For information on Ink, check it out from [here](https://github.com/inkle/ink).

## Getting Started with NovelRT

Currently there are no binary distributions of the engine as of yet, and we are still in our early alpha for almost everything.

If you wish to attempt to build a basic visual novel with the existing C++ API, you must first install the following dependencies:

### Dependencies
- .NET SDK 5.0.100
- CMake 3.13
- Doxygen 1.8.8 (if building docs)
- Freetype 2.8.1
- GLAD 0.1.30
- GLFW 3.2.1
- glm
- gtest/gmock 1.10.0
- libpng 1.6.34
- libsndfile 1.0.28
- OpenAL 1.19.1
- spdlog 1.4.2
- Microsoft GSL 3.1.0

**If you are compiling on Linux, please note - we do not support GCC at this time. Please use Clang instead. Please also note all supported compiler profiles can be found [here.](https://github.com/novelrt/ConanConfig) Contributions for new profiles are welcome, however we will only be accepting profiles for first-party platforms.**

### Build instructions

These instructions are based on the Conan package manager. you can download Conan from [here.](https://conan.io/)

#### Linux
First, you must install the dependencies. Using Ubuntu 20.04 there are extra requirements on top of Conan. With those dependencies, it looks something like this:
```
sudo apt install clang  libgl-dev xorg-dev libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev \
libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev \
libxcb-xfixes0-dev libxcb-xinerama0-dev xkb-data libxcb-dri3-dev libxcb-util-dev python3-pip \
```

Then, install Conan and our configurations should you require them:
```
pip3 install conan
conan config install https://github.com/novelrt/ConanConfig.git
```

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
mkdir -p NovelRT/build
cd NovelRT/build
conan install .. --build=missing --build=bison --profile linux-clang10-amd64
```

Then you should be able to configure and build, like so:
```
cmake ..
cmake --build . -j
```

#### Windows (x64 only)
_Prerequisites:_
- You must set up [Python 3](https://docs.python.org/3/using/windows.html#the-full-installer) and the [.NET 5 SDK](https://dotnet.microsoft.com/download) (if you have not done so already).
- Windows 10 x64

(32-bit installation _may_ be covered in the future.)

Please download [Python 3 (x64) from here](https://www.python.org/downloads/) or from the Microsoft Store. Once that is done,
install conan and our configurations should you require them:
```
pip install conan
conan config install https://github.com/novelrt/ConanConfig.git
```

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
cd NovelRT
mkdir build
cd build
conan install .. --build=missing --profile windows-vs2019-amd64
```

Then you should be able to configure and build, like so:
```
cmake ..
cmake --build . -j
```

#### Visual studio 2019 specific instructions

When you open the NovelRT folder in VS2019 for the first time the CMakeSettings.json file will contain incorrect values.
Change the buildRoot value to `${projectDir}\\build` and the installRoot to `${projectDir}\\install` and restart Visual Studio this will make sure that it uses the same build path as the CLI commands.
You can delete the `out` folder in the NovelRT root as well as we won't use it anymore.
Afterwards right click on the `conanfile.txt` file in the root and click the `Run conan install windows-vs2019-amd64` option.
This runs the conan install command from the section above to regenerate the files we need to build with cmake as Visual Studio wiped the output from earlier.
Then regenerate the cmake by clicking regenerate on the yellow warning ribbon on the top of Visual Studio.

## Example
Examples will be placed here when we have created some. In the meantime, we advise asking us directly on our discord (invite URL above and below).

## Contributing
First off, if you want to contribute, thanks! Tickets that are not being resolved by the development team will be plainly marked as such via `Help Wanted` or something similar to that should it change. We also would greatly appreciate being reached out to via our discord to discuss what you could work on.

**NovelRT and everyone contributing (this includes issues, pull requests, the wiki, Discord in all forms, etc.) must abide by our code of conduct, which can be found [here](CODE_OF_CONDUCT.md). Instances of abuse, harrassment or otherwise unacceptable behaviour must either be reported to a NovelRT Developer via direct message on Discord or by contacting us via [email](mailto:admin%40novelrt.dev).**

## Licence
Unless otherwise specified, all files are copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT).

See [LICENCE](LICENCE.md) in the repository root for more information.


## Questions?
You can reach us directly via our [discord](https://discord.novelrt.dev/), or you can post your question as an issue on the appropriate repository (but honestly asking us directly might be easier).
