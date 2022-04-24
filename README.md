NovelRT
=======

NovelRT is a cross-platform, flexible Visual Novel and 2D game engine. It is aimed at designers and developers alike, however many of the designer tools and features we have on our roadmap have yet to be implemented.

[![Latest Nightly Build](https://img.shields.io/github/workflow/status/novelrt/NovelRT/Continuous%20Integration%20v2/main?label=Nightly%20Build&style=plastic)](https://github.com/novelrt/NovelRT/actions/workflows/build-system.yml)

[![Latest Release](https://img.shields.io/github/v/release/novelrt/NovelRT?color=blueviolet&label=Latest%20Release&style=plastic)](https://github.com/novelrt/NovelRT/releases)

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

If you wish to attempt to build a basic visual novel with the existing C++ API, you must first install the following dependencies:

### Dependencies
- CMake 3.19
- Doxygen 1.8.17 (if building docs)
- Freetype 2.10.1
- GLFW 3.3.6
- glm 0.9.9.7
- gtest/gmock 1.10.0
- libpng 1.6.37
- libsndfile 1.0.30
- Microsoft GSL 3.1.0
- OneTBB 2021.3.0
- OpenAL 1.21.1
- spdlog 1.8.2
- Vulkan SDK 1.2.198.0 (if you require debug/validation layers)
- Vulkan Loader 1.2.298
- Vulkan Memory Allocator 2.3.0 (not directly used currently, but will be used in a future update)

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
conan install .. --build=missing --profile linux-clang10-amd64
```

If you would like to change any of the settings prior to building, pass them in like so:
```
conan install .. --build=missing --profile linux-clang10-amd64 -o NovelRT:buildtests=False -o NovelRT:documentation=False -o NovelRT:buildsamples=False -o NovelRT:buildinterop=False
```
(Please note: the above command shows the only four options we support at the moment - anything else is considered unsupported at this time.)


Then you should be able to configure and build the default setup, like so:
```
conan build .. --build-folder .
```

If you would like to build using CMake instead, you can configure and build, like so:
```
cmake ..
cmake --build . -j
```

#### Windows (x64 only)
_Prerequisites:_
- You must set up [Python 3](https://docs.python.org/3/using/windows.html#the-full-installer)(if you have not done so already).
- Windows 10 x64
- Either:
  - Visual Studio 2019 w/ "Desktop development with C++" Workload,
  - Visual Studio 2022 w/ "Desktop development with C++" Workload,
  _OR_
  - Build Tools for Visual Studio 2019/2022 w/ "Desktop development with C++" Workload
- CMake 3.19 or above
_(note: Do not use the included one with Visual Studio at this time! It is outdated as of this time of writing and is considered incompatible.)_

(32-bit builds _will not be supported at this time_.)

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
conan install .. --build=missing --profile windows-vs2022-amd64
```

If you would like to change any of the settings prior to building, pass them in like so:
```
conan install .. --build=missing --profile windows-vs2022-amd64 -o NovelRT:buildtests=False -o NovelRT:documentation=False -o NovelRT:buildsamples=False -o NovelRT:buildinterop=False
```
(Please note: the above command shows the only four options we support at the moment - anything else is considered unsupported at this time.)

Then you should be able to configure and build the default setup, like so:
```
conan build .. --build-folder .
```

If you would like to build using CMake instead, you can configure and build, like so:
```
cmake ..
cmake --build . -j
```

##### Visual studio 2019/2022 specific instructions

When you open the NovelRT folder in VS2019 or VS2022 for the first time the CMakeSettings.json file will contain incorrect values.
Change the buildRoot value to `${projectDir}\\build` and the installRoot to `${projectDir}\\install` and restart Visual Studio this will make sure that it uses the same build path as the CLI commands.
You can delete the `out` folder in the NovelRT root as well as we won't use it anymore.
Afterwards right click on the `conanfile.py` file in the root and click the `Run conan install windows-vs2022-amd64` option. (Respectfully, use the `windows-vs2019-amd64` option when building with VS2019.)
This runs the conan install command from the section above to regenerate the files we need to build with cmake as Visual Studio wiped the output from earlier.
Then regenerate the cmake by clicking regenerate on the yellow warning ribbon on the top of Visual Studio.


#### macOS 10.15 (and above)
_Prerequisites:_
- Python 3 x64 (installed via Homebrew _or_ run as any user other than root)
- XCode 12
- XCode Command Line Tools matching the installed version
- CMake 3.19

First, install Conan and our configurations should you require them:
```
pip3 install conan
conan config install https://github.com/novelrt/ConanConfig.git
```

If you are building from a command line terminal, clone NovelRT and set up the build folder like so:
```
git clone https://github.com/NovelRT/NovelRT.git
mkdir -p NovelRT/build
cd NovelRT/build
conan install .. --build=missing --profile macos-appleclang12-amd64
```

If you would like to change any of the settings prior to building, pass them in like so:
```
conan install .. --build=missing --profile macos-appleclang12-amd64 -o NovelRT:buildtests=False -o NovelRT:documentation=False -o NovelRT:buildsamples=False -o NovelRT:buildinterop=False
```
(Please note: the above command shows the only four options we support at the moment - anything else is considered unsupported at this time.)

Then you should be able to configure and build the default setup, like so:
```
conan build .. --build-folder .
```

If you would like to build using CMake instead, you can configure and build, like so:
```
cmake ..
cmake --build . -j
```


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
