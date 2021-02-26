from conans import ConanFile, CMake
import platform


class NovelRTGlobalDependenciesConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "doxygen/1.8.20", "freetype/2.10.1", "glad/0.1.33", "glfw/3.3.2", "glm/0.9.9.7", "gtest/1.10.0", \
               "libsndfile/1.0.30", "lua/5.3.5", "openal/1.19.1", "spdlog/1.8.2"
    generators = "cmake_paths", "cmake_find_package"
    default_options = {"freetype:shared": True, "glfw:shared": True, "libsndfile:shared": True, "lua:shared": True,
                       "openal:shared": True, "glad:gl_profile": "core", "glad:gl_version": 4.0,
                       "glad:gles2_version": 3.0, "spdlog:header_only": True}
    build_policy = "missing"

    def imports(self):
        self.copy("*.dll", dst="src/NovelRT", src="bin")
        self.copy("*.dll", dst="src/NovelRT", src="lib")

    def build_requirements(self):
        if platform.system() == "Linux":
            self.build_requires("bison/3.7.1")  # WHAT PUT HERE?

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
