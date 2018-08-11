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

    def build(self):
        cmake = CMake(self)
        if 'build_test' in os.environ or 'build_all' in os.environ:
            cmake.definitions['BUILD_TEST'] = "1"
        if 'build_server' in os.environ or 'build_all' in os.environ:
            cmake.definitions['BUILD_SERVER'] = "1"
        if 'create_package' in os.environ:
            cmake.definitions['CREATE_PACKAGE'] = "1"

        cmake.configure(source_folder='{}'.format(self.source_folder))
        cmake.build()
        cmake.install()
        if 'create_package' in os.environ:
            cmake.build(target="package_debug")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.so*", dst="bin", src="lib")  # From lib to bin
        self.copy("*.dylib*", dst="bin", src="lib")  # From lib to bin
        self.copy("*.bin", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dat", dst="bin", src="bin")  # From bin to bin
        self.copy("*.pak", dst="bin", src="bin")  # From bin to bin
