from conans import ConanFile, CMake
import dependencies
import os


class InexorConan(ConanFile):
    license = "ZLIB"
    description = "Inexor's private root Conan recipe"
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
        if os.environ['build_test'] or os.environ['build_all']:
            args += ["-DBUILD_TEST=1"]
        if os.environ['build_server'] or os.environ['build_all']:
            args += ["-DBUILD_SERVER=1"]
        if os.environ['build_master'] or os.environ['build_all']:
            args += ["-DBUILD_MASTER=1"]
        if os.environ['create_package']:
            args += ["-DCREATE_PACKAGE=1"]
        cmake = CMake(self)
        self.run('cmake "{}" {} {}'.format(self.source_folder, cmake.command_line, ' '.join(args)))
        self.run('cmake --build . --target install {}'.format(cmake.build_config))
        if self.scope.create_package:
            self.run('cmake --build . --target package_debug {}'.format(cmake.build_config))

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.so*", dst="bin", src="lib")  # From lib to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin
        self.copy("*.bin", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dat", dst="bin", src="bin")  # From bin to bin
        self.copy("*.pak", dst="bin", src="bin")  # From bin to bin
