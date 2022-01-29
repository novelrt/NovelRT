from conans import ConanFile, CMake
import os

class NovelRTTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package", "cmake_paths"
    requires = [
        ("NovelRT/0.1")]
    default_options = {
        "NovelRT:documentation": False,
        "NovelRT:buildtests":False,
        "NovelRT:buildsamples":False,
        "NovelRT:packagemode":True
    }

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")

    def test(self):
        os.chdir("bin")
        self.run(".%sexample" % os.sep)
