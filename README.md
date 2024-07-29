NovelRT
=======

NovelRT is a cross-platform, flexible Visual Novel and 2D game engine. It is aimed at designers and developers alike, however many of the designer tools and features we have on our roadmap have yet to be implemented.

[![Latest Nightly Build](https://img.shields.io/github/actions/workflow/status/novelrt/NovelRT/build-system.yml?branch=main&color=blueviolet&label=Nightly%20Build&style=plastic)](https://github.com/novelrt/NovelRT/actions/workflows/build-system.yml)

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/novelrt/NovelRT?color=blueviolet&label=Latest%20Release&style=plastic)

[![Discord](https://discordapp.com/api/guilds/543898968380145675/widget.png?style=banner2)](https://discord.novelrt.dev/)

## Current Features

Currently, NovelRT supports the following in its base form:
- Graphics LLAPI
- Audio LLAPI

## Future & Immediate Improvements

Current features in development include:
- C++ HLAPI
- Fabulist narrative scripting language support

For information on Fabulist, check it out from [here](https://github.com/novelrt/fabulist).

## Getting Started with NovelRT

Currently there are no binary distributions of the engine as of yet, and we are still in our early alpha for almost everything.

### Dependencies

If you wish to attempt to build a basic visual novel with the existing C++ API, you must first install the following dependencies:

- [CMake](https://cmake.org/download/) >= 3.19.8
- [Vulkan SDK](https://vulkan.lunarg.com) >= 1.3.231.1
- [Python](https://www.python.org/downloads/) >= 3.11

The dependencies that are handled by CMake that do not need to be manually installed are as follows:

- Doxygen 1.8.17 (building docs)
- fmt 10.2.1
- GLFW 3.3.7
- glm 0.9.9.9
- gtest/gmock 1.11.0
- fmt 10.2.1
- libpng 1.6.35
- libsndfile 1.1.0
- Microsoft GSL 4.0.0
- OneTBB 2021.5.0
- OpenAL 1.23.1
- spdlog 1.13.0

### Build instructions

These instructions are based on the CMake build system generator. You can download the latest version here [here.](https://cmake.org/download/)

**If you are compiling on Linux, please note - we do not support GCC at this time. Please use Clang 10+ instead. We will gladly accept contributions towards making GCC compatible, but until support is guaranteed we will _only_ officially support first-party compilers as described in our CI builds found** [here.](https://github.com/novelrt/NovelRT/blob/6d9caf2cb2426f6d3661575c7dbd24014d4260b9/.github/workflows/build-system.yml)


#### Linux

First, you must install the dependencies. On Ubuntu 20.04, it looks like this:
```
sudo apt install clang  libgl-dev xorg-dev libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev \
libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev \
libxcb-xfixes0-dev libxcb-xinerama0-dev xkb-data libxcb-dri3-dev libxcb-util-dev python \
```

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
mkdir -p NovelRT/build
cd NovelRT/build
```

Then, you can configure and build using CMake, like so:
```
cmake ..
cmake --build . -j
```

#### Windows (x64 only)
_Prerequisites:_
- Windows 10 x64
- Either:
  - Visual Studio 2019 w/ "Desktop development with C++" Workload,
  - Visual Studio 2022 w/ "Desktop development with C++" Workload,
  _OR_
  - Build Tools for Visual Studio 2019/2022 w/ "Desktop development with C++" Workload
- CMake 3.19 or above
_(note: Do not use the included one with Visual Studio at this time! It is outdated as of this time of writing and is considered incompatible.)_
- Python 3.11 or above

(32-bit builds _will not be supported at this time_.)

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
cd NovelRT
mkdir build
cd build
```

Then, you can configure and build using CMake, like so:
```
cmake ..
cmake --build . -j
```

##### Visual studio 2019/2022 specific instructions

When you open the NovelRT folder in VS2019 or VS2022 for the first time the CMakeSettings.json file will contain incorrect values.
Change the buildRoot value to `${projectDir}\\build` and the installRoot to `${projectDir}\\install` and restart Visual Studio this will make sure that it uses the same build path as the CLI commands.
You can delete the `out` folder in the NovelRT root as well as we won't use it anymore.
Then regenerate the cmake by clicking regenerate on the yellow warning ribbon on the top of Visual Studio.


#### macOS 10.15 (and above)
_Prerequisites:_
- XCode 12
- XCode Command Line Tools matching the installed version
- CMake 3.19.8
- Vulkan SDK 1.3.231.1
- Python 3.11 or above

**NOTE: Until native Metal support is introduced at a future time, it is _required_ that you install Vulkan SDK version 1.3.231.1 as a prerequisite to configuring/building NovelRT. The instructions below will indicate directions _assuming_ that the Vulkan SDK is already installed in a non-system path. If it is not installed, NovelRT's build system will fail to properly configure.**

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
mkdir -p NovelRT/build
cd NovelRT/build
```

Once you have cloned the repository, ensure that the terminal performing configuration of NovelRT runs the `source setup-env.sh` from within the Vulkan SDK directory.

If you have an Intel Mac you can configure the cmake files like so:
```
cmake ..
```
However, if you have Apple-Silicon Mac (M1, M2, etc), you must add an additional flag to the configuration command, like so:
```
cmake .. -DCMAKE_APPLE_SILICON_PROCESSOR="arm64"
```

If Vulkan SDK is not installed in a system path and the `setup-env.sh` file did not properly add the required environment variables, you can specify the `VULKAN_SDK` environment variable to your local Vulkan SDK location as such:
```
VULKAN_SDK=/Users/youruser/Vulkan SDK/1.3.231.1/macOS cmake ..
```
Please ensure that the path includes the macOS folder, otherwise finding the proper libraries will fail.

Once NovelRT is configured, you can build it like so:
```
cmake --build . -j
```

To run the samples, you will need to navigate to the folder the executable resides in, and
launch from there. This is due to how macOS and CMake handle's RPATHs.


## Example
Examples will be placed here when we have created some. In the meantime, we advise asking us directly on our discord (invite URL above and below).

## Contributing
First off, if you want to contribute, thanks!

If you would like to contribute to the development of NovelRT, please see our [contribution guide here](Contributing.md).
If this doesn't answer any questions that you have, feel free to reach out to us on Discord to discuss what you can work on - we greatly appreciate it!

**NovelRT and everyone contributing (this includes issues, pull requests, the wiki, Discord in all forms, etc.) must abide by our code of conduct, which can be found [here](CODE_OF_CONDUCT.md). Instances of abuse, harrassment or otherwise unacceptable behaviour must either be reported to a NovelRT Developer via direct message on Discord or by contacting us via [email](mailto:admin%40novelrt.dev).**

## Licence
Unless otherwise specified, all files are copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT).

See [LICENCE](LICENCE.md) in the repository root for more information.


## Questions?
You can reach us directly via our [discord](https://discord.novelrt.dev/), or you can post your question as an issue on the appropriate repository (but honestly asking us directly might be easier).
