from conans import ConanFile, CMake, tools
import sys

class NovelRTConan(ConanFile):
    name = "NovelRT"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/novelrt/NovelRT"
    description = "A cross-platform 2D game engine accompanied by a strong toolset for visual novels."
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        ("freetype/2.10.1"),
        ("glfw/3.3.2"),
        ("glm/0.9.9.7"),
        ("gtest/1.10.0"),
        ("libsndfile/1.0.30"),
        ("ms-gsl/3.1.0"),
        ("openal/1.21.1"),
        ("onetbb/2021.3.0"),
        ("spdlog/1.8.2"),
        ("vulkan-loader/1.2.182"),
        ("vulkan-memory-allocator/2.3.0")
    ]
    generators = "cmake_find_package", "cmake_paths"
    options = {
        "inksupport": [True, False],
        "documentation": [True, False],
        "buildtests": [True, False],
        "buildsamples": [True, False]
    }
    default_options = {
        "freetype:shared":True,
        "glfw:shared":True,
        "libsndfile:shared":True,
        "openal:shared":True,
        "PNG:shared":True,
        "BZip2:shared":True,
        "flac:shared":True,
        "fmt:shared":True,
        "Opus:shared":True,
        "Ogg:shared":True,
        "Vorbis:shared":True,
        "glad:gl_profile":"core",
        "glad:gl_version":4.0,
        "glad:gles2_version":3.0,
        "spdlog:header_only":True,
        "vulkan-loader:shared":True,
        "inksupport": True,
        "documentation": False,
        "buildtests":True,
        "buildsamples":True
    }
    cmake = None

    def imports(self):
        self.copy("*.dll", dst="thirdparty", src="bin")
        self.copy("*.dll", dst="thirdparty", src="lib")
        self.copy("*.json", dst="thirdparty", src="bin")
        self.copy("*.json", dst="thirdparty", src="lib")

    def source(self):
        self.run("git clone https://github.com/novelrt/NovelRT.git")

    def configure_cmake(self):
        cmake = CMake(self)
        if(self.options.inksupport):
            cmake.definitions["NOVELRT_INCLUDE_INK"] = "On"
        else:
            cmake.definitions["NOVELRT_INCLUDE_INK"] = "Off"
        if(self.options.documentation):
            cmake.definitions["NOVELRT_BUILD_DOCUMENTATION"] = "On"
        else:
            cmake.definitions["NOVELRT_BUILD_DOCUMENTATION"] = "Off"
        if(self.options.buildtests):
            cmake.definitions["NOVELRT_BUILD_TESTS"] = "On"
        else:
            cmake.definitions["NOVELRT_BUILD_TESTS"] = "Off"
        if(self.options.buildsamples):
            cmake.definitions["NOVELRT_BUILD_SAMPLES"] = "On"
        else:
            cmake.definitions["NOVELRT_BUILD_SAMPLES"] = "Off"

        cmake.configure()
        return cmake

    def build(self):
        self.cmake = self.configure_cmake()
        self.cmake.build()
        if(self.options.buildtests):
            self.cmake.test()

    # def package(self):
    #    self.copy("*.h", dst="include", src="NovelRT/include")
    #     # self.copy("*.h", dst="include/NovelRT", src="NovelRT/include/NovelRT")
    #     # self.copy("*.h", dst="include/NovelRT.Interop", src="NovelRT/include/NovelRT.Interop")
    #     if sys.platform.startswith('win32'):
    #         self.copy("*NovelRT.lib", dst="lib", keep_path=False)
    #         self.copy("*NovelRT.Interop.lib", dst="lib", keep_path=False)
    #         self.copy("*NovelRT.dll", dst="bin", keep_path=False)
    #         self.copy("*NovelRT.Interop.dll", dst="bin", keep_path=False)
    #         self.copy("*bz2.dll", dst="bin", keep_path=False)
    #         self.copy("*FLAC.dll", dst="bin", keep_path=False)
    #         self.copy("*FLAC++.dll", dst="bin", keep_path=False)
    #         self.copy("*fmt.dll", dst="bin", keep_path=False)
    #         self.copy("*freetype.dll", dst="bin", keep_path=False)
    #         self.copy("*glfw3.dll", dst="bin", keep_path=False)
    #         self.copy("*ogg.dll", dst="bin", keep_path=False)
    #         self.copy("*OpenAL32.dll", dst="bin", keep_path=False)
    #         self.copy("*opus.dll", dst="bin", keep_path=False)
    #         self.copy("*sndfile.dll", dst="bin", keep_path=False)
    #         self.copy("*vorbis.dll", dst="bin", keep_path=False)
    #         self.copy("*vorbisenc.dll", dst="bin", keep_path=False)
    #         self.copy("*vorbisfile.dll", dst="bin", keep_path=False)


    def package_info(self):
        self.cpp_info.libs = ["novelrt", "novelrt.interop"]
