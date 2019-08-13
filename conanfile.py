from conans import ConanFile, CMake


class UbitrackCoreConan(ConanFile):
    name = "ubitrack_facade"
    version = "1.3.0"

    description = "Ubitrack Facade Library and Components"
    url = "https://github.com/Ubitrack/utfacade.git"
    license = "GPL"

    short_paths = True
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "ubitrack_virtualenv_generator"
    options = {"shared": [True, False],
               "workspaceBuild" : [True, False],
               "enable_basicfacade": [True, False],
               "enable_simplefacade": [True, False],
               "enable_dotnet": [True, False],
               "enable_java": [True, False],
                }

    default_options = {
        "shared" :True,
        "enable_basicfacade":True,
        "enable_simplefacade":False,
        "enable_dotnet":False,
        "enable_java":False,
        "workspaceBuild" : False,
        }

    # all sources are deployed with the package
    exports_sources = "apps/*", "cmake/*", "components/*", "doc/*", "src/*", "CMakeLists.txt", "utfacadeConfig.cmake"

    def requirements(self):
        userChannel = "ubitrack/stable"
        if self.options.workspaceBuild:
            userChannel = "local/dev"
        self.requires("ubitrack_core/%s@%s" % (self.version, userChannel))
        self.requires("ubitrack_vision/%s@%s" % (self.version, userChannel))
        self.requires("ubitrack_dataflow/%s@%s" % (self.version, userChannel) )
        self.requires("ubitrack_virtualenv_generator/1.3.0@ubitrack/stable")

    def build_requirements(self):
        if self.options.enable_java:
            self.build_requires("java_installer/9.0.0@bincrafters/stable")
        if self.options.enable_java or self.options.enable_dotnet:
            if self.settings.os == "Windows":
                self.build_requires("swig/3.0.12@camposs/stable")
            # if linux, then apt-get install swig


    def configure(self):
        if self.settings.os == "Windows":
            self.options.enable_dotnet = True
            
        if self.options.shared:
            self.options['ubitrack_core'].shared = True
            self.options['ubitrack_vision'].shared = True
            self.options['ubitrack_dataflow'].shared = True

        # can't build java/dotnet wrappers without simplefacade
        if not self.options.enable_simplefacade:
            self.options.enable_java = False
            self.options.enable_dotnet = False


    # def imports(self):
    #     self.copy(pattern="*.dll", dst="bin", src="bin") # From bin to bin
    #     self.copy(pattern="*.dylib*", dst="lib", src="lib") 
       
    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = self.options.shared
        cmake.definitions['ENABLE_BASICFACADE'] = self.options.enable_basicfacade
        cmake.definitions['ENABLE_SIMPLEFACADE'] = self.options.enable_simplefacade
        cmake.definitions['ENABLE_DOTNET_WRAPPER'] = self.options.enable_dotnet
        cmake.definitions['ENABLE_JAVA_WRAPPER'] = self.options.enable_java
        cmake.configure()
        cmake.build()
        cmake.install()

    def package(self):
        # self.copy("*.h", dst="include", src="src")
        # self.copy("*.lib", dst="lib", excludes="*/lib/ubitrack/*.lib", keep_path=False)
        # self.copy("*.dll", dst="bin", excludes="*/lib/ubitrack/*.dll", keep_path=False)
        # self.copy("*.dylib*", dst="lib", excludes="*/lib/ubitrack/*.dylib", keep_path=False)
        # self.copy("*.so", dst="lib", excludes="*/lib/ubitrack/*.so", keep_path=False)
        # self.copy("*.a", dst="lib", keep_path=False)
        # self.copy("*", dst="bin", src="bin", keep_path=False)

        # # components
        # self.copy("ubitrack/*.lib", dst="lib/ubitrack", keep_path=False)
        # self.copy("ubitrack/*.dll", dst="bin/ubitrack", keep_path=False)
        # self.copy("ubitrack/*.dylib*", dst="lib/ubitrack", keep_path=False)
        # self.copy("ubitrack/*.so", dst="lib/ubitrack", keep_path=False)
        pass

    def package_info(self):
        suffix = ""
        if self.settings.os == "Windows":
            suffix += self.version.replace(".", "")
            if self.settings.build_type == "Debug":
                suffix += "d"
        self.cpp_info.libs.append("utfacade%s" % (suffix))


    def package_id(self):
        self.info.requires["ubitrack_vision"].full_package_mode()
