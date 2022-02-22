from conans import ConanFile, CMake, tools

class NovelRTConan(ConanFile):
    name = "NovelRT"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/novelrt/NovelRT"
    description = "A cross-platform 2D game engine accompanied by a strong toolset for visual novels."
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        ("freetype/2.10.1"),
        ("glfw/3.3.6"),
        ("glm/0.9.9.7"),
        ("gtest/1.10.0"),
        ("libsndfile/1.0.30"),
        ("ms-gsl/3.1.0"),
        ("openal/1.21.1"),
        ("onetbb/2021.3.0"),
        ("spdlog/1.8.2"),
        ("vulkan-loader/1.2.198.0"),
        #("vulkan-memory-allocator/2.3.0")
    ]
    generators = "cmake_find_package", "cmake_paths"
    options = {
        "documentation": [True, False],
        "buildtests": [True, False],
        "buildsamples": [True, False],
        "buildinterop": [True, False]
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
        "vulkan-loader:shared":True,
        "spdlog:header_only":True,
        "documentation": False,
        "buildtests":True,
        "buildsamples":True,
        "buildinterop":True
    }
    cmake = None

    def requirements(self):
        if self.settings.os == "Macos":
            self.requires("moltenvk/1.1.6")
            self.options["moltenvk"].shared = True
            self.output.info("Generating for MacOS with MoltenVK support")

    def imports(self):
        if self.settings.os == "Windows":
            self.copy("*.dll", dst="thirdparty", src="bin")
            self.copy("*.dll", dst="thirdparty", src="lib")
        if self.settings.os == "Macos":
            self.copy("*.dylib", dst="thirdparty", src="lib")
            self.copy("*MoltenVK_icd.json", dst="thirdparty", src="lib")


    def source(self):
        self.run("git clone https://github.com/novelrt/NovelRT.git")

    def configure_cmake(self):
        cmake = CMake(self)
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
        if(self.options.buildinterop):
            cmake.definitions["NOVELRT_BUILD_INTEROP"] = "On"
        else:
            cmake.definitions["NOVELRT_BUILD_INTEROP"] = "Off"

        cmake.configure()
        return cmake

    def build(self):
        self.cmake = self.configure_cmake()
        self.cmake.build()
        if(self.options.buildtests):
            self.cmake.test()

    def package_info(self):
        self.cpp_info.libs = ["novelrt", "novelrt.interop"]
