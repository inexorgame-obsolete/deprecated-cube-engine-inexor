from conans import ConanFile, CMake
import os, multiprocessing

class InexorConan(ConanFile):
    license = "ZLIB"
    url = "https://github.com/inexor-game/code.git"
    settings = "os", "compiler", "build_type", "arch"
    requires = (("InexorGlueGen/0.6.0alpha@inexorgame/testing"),
                ("Protobuf/3.1.0@inexorgame/stable"),
                ("gRPC/1.1.0-dev@inexorgame/stable"),
                ("doxygen/1.8.13@inexorgame/testing"),
                ("Boost/1.60.0@lasote/stable"),
                ("RapidJSON/1.0.2@inexorgame/stable"),
                ("zlib/1.2.8@lasote/stable"),
                ("gtest/1.7.0@lasote/stable"),
                ("ENet/1.3.13@inexorgame/stable"),
                ("spdlog/0.10.0@memsharded/stable"),
                ("SDL2/2.0.5@lasote/stable"),
                ("SDL2_image/2.0.1@lasote/stable"),
                ("CEF/3.2704.1424.gc3f0a5b@a_teammate/testing")
            )

    generators = "cmake"
    default_options = '''
      zlib:shared=False
      gtest:shared=False
      ENet:shared=False
      Boost:shared=False
      SDL2:shared=False
      SDL2_image:shared=False
      CEF:use_sandbox=False
    '''

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
            self.run('cmake --build . --target package {}'.format(cmake.build_config))

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.so*", dst="bin", src="lib") # From lib to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
        self.copy("*.bin", dst="bin", src="bin") # From bin to bin
        self.copy("*.dat", dst="bin", src="bin") # From bin to bin
        self.copy("*.pak", dst="bin", src="bin") # From bin to bin
