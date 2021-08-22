ConanSample
=======

This sample is designed to show an end-user how to reference the NovelRT and Interop packages together via Conan.

## Getting Started

Currently, most of the dependencies required for NovelRT are required for this sample, sans .NET.

### Build instructions

These instructions are based on the Conan package manager. you can download Conan from [here.](https://conan.io/)

#### Linux

[TODO: Add Linux instructions]

#### Windows (x64 only)
_Prerequisites:_
- Windows 10 x64

Set up the build folder like so, starting from the ConanSample folder:
```
mkdir build
cd build
conan install .. --build=missing --profile windows-vs2019-amd64
```

Then you should be able to configure and build the sample, like so:
```
cmake ..
cmake --build .
```

## Questions?
You can reach us directly via our [discord](https://discord.novelrt.dev/), or you can post your question as an issue on the appropriate repository (but honestly asking us directly might be easier).
