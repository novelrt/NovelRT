from conans import ConanFile, CMake

class NovelRTConan(ConanFile):
    name = "NovelRT"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/novelrt/NovelRT"
    description = "A cross-platform 2D game engine accompanied by a strong toolset for visual novels."
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        ("freetype/2.10.1"),
        ("glad/0.1.33"),
        ("glfw/3.3.2"),
        ("glm/0.9.9.7"),
        ("gtest/1.10.0"),
        ("libsndfile/1.0.30"),
        ("openal/1.19.1"),
        ("spdlog/1.8.2"),
        ("ms-gsl/3.1.0")
    ]
    generators = "cmake_find_package", "cmake_paths"
    options = {"inksupport": [True, False]}
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
        "inksupport": True
    }

    def imports(self):
        self.copy("*.dll", dst="thirdparty", src="bin")
        self.copy("*.dll", dst="thirdparty", src="lib")

    # def source(self):
    #     self.run("git clone https://github.com/novelrt/NovelRT.git")
