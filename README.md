NovelRT
=======

NovelRT is a cross-platform, flexible Visual Novel and 2D game engine. It is aimed at designers and developers alike, however many of the designer tools and features we have on our roadmap have yet to be implemented.

| Job | Debug Status | Release Status |
| --- | ------------ | -------------- |
| Windows x64 | [![Build Status](https://ci.novelrt.dev/_apis/build/status/novelrt.novelrt-ci?branchName=master&jobName=windows_debug_x64)](https://ci.novelrt.dev/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://ci.novelrt.dev/_apis/build/status/novelrt.novelrt-ci?branchName=master&jobName=windows_release_x64)](https://ci.novelrt.dev/_build/latest?definitionId=1&branchName=master) |
| Ubuntu x64 | [![Build Status](https://ci.novelrt.dev/_apis/build/status/novelrt.novelrt-ci?branchName=master&jobName=ubuntu_debug_x64)](https://ci.novelrt.dev/_build/latest?definitionId=1&branchName=master) | [![Build Status](https://ci.novelrt.dev/_apis/build/status/novelrt.novelrt-ci?branchName=master&jobName=ubuntu_release_x64)](https://ci.novelrt.dev/_build/latest?definitionId=1&branchName=master) |

[![Discord](https://discordapp.com/api/guilds/543898968380145675/widget.png?style=banner2)](https://discord.novelrt.dev/)

## Current Features

Currently, NovelRT supports the following in its base form:
- Graphics LLAPI
- Audio LLAPI

## Future & Immediate Improvements

Current features in development include:
- C++ HLAPI
- Lua 5.3 LLAPI
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
- Lua 5.3
- OpenAL 1.19.1
- spdlog 1.4.2

### Build instructions

We provide build scripts in the root of the repository which may work for you.
However, you will need to ensure the dependencies are correctly installed.

#### Linux
First, you must install the dependencies. Using Ubuntu 20.04, this looks something like this:
```
sudo apt install clang cmake doxygen graphviz g++ libfreetype-dev libglfw3-dev \
    libglm-dev libgmock-dev libgtest-dev liblua5.3-dev libopenal-dev libsndfile1-dev \
    libspdlog-dev python3-glad
```
Then, clone and build NovelRT:
```
git clone https://github.com/NovelRT/NovelRT.git
mkdir -p NovelRT/build
cd NovelRT/build
cmake ..
make -j
```

#### Windows
First, you must set up [(our fork of*) vcpkg](https://github.com/capnkenny/vcpkg) as shown below:
```
git clone https://github.com/capnkenny/vcpkg
cd vcpkg
./bootstrap-vcpkg.bat
```
Next, use vcpkg and Python 3 to install the dependencies:
```
python -m pip install setuptools
python -m pip install glad
vcpkg.exe install freetype glfw3 glm gtest libsndfile lua openal-soft spdlog --triplet x64-windows
vcpkg integrate install
```
Then, clone and build NovelRT:
```
git clone https://github.com/NovelRT/NovelRT.git
cd NovelRT
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/toolchain.cmake ..
cmake --build . -j
```

Alternatively, you can also specify a single target to build like so:
```
cmake --build . -j -t TargetNameGoesHere
```

*Note: You are more than welcome to try using Microsoft's version of vcpkg - in this case, look up how to [setup vcpkg](https://docs.microsoft.com/en-us/cpp/build/vcpkg?view=vs-2019#installation) here. Please heed our warning however that this will not be supported by the NovelRT team due to versioning and compatibility differences.

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
