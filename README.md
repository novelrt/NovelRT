# NovelRT
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

Currently there are no binary distributions of the engine as of yet, and we are still in our early alpha for almost everything. If you wish to attempt to build a basic visual novel with the existing C++ API, you must first `git clone` this repository and set up vcpkg, which you can find out more about [here](https://github.com/microsoft/vcpkg).

### Our dependency list currently includes:
- GLAD
- GLFW
- glm
- Freetype
- Libsndfile
- libpng
- Lua 5.3
- OpenAL-Soft
- spdlog
(and their respective dependencies)

*The minimum CMake version required for this project is 3.13.*

## Example
Examples will be placed here when we have created some. In the meantime, we advise asking us directly on our discord (invite URL above and below).

## Contributing
First off, if you want to contribute, thanks! Tickets that are not being resolved by the development team will be plainly marked as such via `Help Wanted` or something similar to that should it change. We also would greatly appreciate being reached out to via our discord to discuss what you could work on.

**NovelRT and everyone contributing (this includes issues, pull requests, the wiki, Discord in all forms, etc.) must abide by our code of conduct, which can be found [here](CODE_OF_CONDUCT.md). Instances of abuse, harrassment or otherwise unacceptable behaviour must either be reported to a NovelRT Discord via direct message or by contacting us via email at admin@novelrt.dev.**

## Licence
Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See [LICENCE](LICENCE.md) in the repository root for more information.


## Questions?
You can reach us directly via our [discord](https://discord.novelrt.dev/), or you can post your question as an issue on the appropriate repository (but honestly asking us directly might be easier).
