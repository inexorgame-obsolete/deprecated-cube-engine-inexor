from conans import ConanFile, CMake
import os, dependencies, multiprocessing

class InexorConan(ConanFile):
    license = "ZLIB"
    url = "https://github.com/inexor-game/code.git"
    settings = "os", "compiler", "build_type", "arch"
    requires = dependencies.requires
    generators = "cmake"
    default_options = dependencies.options

    def configure(self):
        self.requires.add("InexorGlueGen/0.3.0alpha@inexor/testing")

        # THIS IS A VERY DIRTY HACK
        # following is given:
        # 1) InexorGlueGen shares sources with InexorCore, but obviously is a dependency (needed as buildtool)
        # 2) We do not want to double the dependency-list for both
        # -> So we add another conanfile.py for GlueGen
        # -> we create the gluegen package from whithin this script
        # (we can not simply upload InexorGlueGen, since then you won't be able to modify shit without pushing the dependency-list)
        # 3) We can not export files in parent folders (or at least it does not work),
        #    so we temporarily copy the InexorGlueGen conanfile.py to code/conanfile.py and create the InexorGlueGen-package.
        this_conanfile = __file__
        this_conanfile_backup = "{}_inplacebackup".format(this_conanfile)
        dir_path = os.path.dirname(os.path.realpath(this_conanfile))
        gluegen_conanfile = os.path.join(dir_path, "inexor", "gluegen", "conanfile.py")
        self.output.warn("CONFILEGLUGEN: {}".format(gluegen_conanfile))
        os.rename(this_conanfile, this_conanfile_backup)
        os.rename(gluegen_conanfile, this_conanfile)
        self.run('cd {} && conan export inexor'.format(dir_path))
        os.rename(this_conanfile, gluegen_conanfile)
        os.rename(this_conanfile_backup, this_conanfile)
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
        set_number_cores = ""
        if self.settings.compiler != "Visual Studio":
            set_number_cores = 'export MAKEOPTS="-j{}" && '.format(multiprocessing.cpu_count() + 2) # Some padding is ok since i/o is blocking
        cmake = CMake(self.settings)
        self.run('{}cmake "{}" {} {}'.format(set_number_cores, self.conanfile_directory, cmake.command_line, ' '.join(args)))
        self.run('{}cmake --build . --target install {}'.format(set_number_cores, cmake.build_config))

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin") # From bin to bin
        self.copy("*.bin", dst="bin", src="bin") # From bin to bin
        self.copy("*.dat", dst="bin", src="bin") # From bin to bin
        self.copy("*.pak", dst="bin", src="bin") # From bin to bin
        self.copy("*.dylib*", dst="bin", src="lib") # From lib to bin
        