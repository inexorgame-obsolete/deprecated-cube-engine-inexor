from conans import ConanFile, CMake
import os, dependencies, multiprocessing

class InexorConan(ConanFile):
    license = "ZLIB"
    url = "https://github.com/inexorgame/inexor-core.git"
    settings = "os", "compiler", "build_type", "arch"

    requires = dependencies.requires
    generators = "cmake"
    default_options = dependencies.options

    def configure(self):
        if self.settings.compiler == "gcc":
            self.options["SDL2"].shared = True
            self.options["SDL2_image"].shared = True

    def build(self):
        args = []
        if self.scope.build_test or self.scope.build_all:
            args += ["-DBUILD_TEST=1"]
        if self.scope.build_server or self.scope.build_all:
            args += ["-DBUILD_SERVER=1"]
        if self.scope.build_master or self.scope.build_all:
            args += ["-DBUILD_MASTER=1"]
        if self.scope.create_package:
            args += ["-DCREATE_PACKAGE=1"]
        cmake = CMake(self.settings)
        self.run('cmake "{}" {} {}'.format(self.conanfile_directory, cmake.command_line, ' '.join(args)))
        self.run('cmake --build . --target install {}'.format(cmake.build_config))
        if self.scope.create_package:
            self.run('cmake --build . --target package_debug {}'.format(cmake.build_config))

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.so*", dst="bin", src="lib") # From lib to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
        self.copy("*.bin", dst="bin", src="bin") # From bin to bin
        self.copy("*.dat", dst="bin", src="bin") # From bin to bin
        self.copy("*.pak", dst="bin", src="bin") # From bin to bin
