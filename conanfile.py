from conans import ConanFile, CMake


class UbitrackCoreConan(ConanFile):
    name = "ubitrack_facade"
    version = "1.3.0"

    description = "Ubitrack Facade Library and Components"
    url = "https://github.com/Ubitrack/utfacade.git"
    license = "GPL"

    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    options = {"shared": [True, False],
               "enable_basicfacade": [True, False],
               "enable_dotnet": [True, False],
               "enable_java": [True, False]}
    requires = (
        "ubitrack_core/%s@ulricheck/stable" % version,
        "ubitrack_vision/%s@ulricheck/stable" % version,
        "ubitrack_dataflow/%s@ulricheck/stable" % version,
       )

    default_options = (
        "shared=True",
        "enable_basicfacade=True",
        "enable_dotnet=False",
        "enable_java=True",
        )

    # all sources are deployed with the package
    exports_sources = "apps/*", "cmake/*", "components/*", "doc/*", "src/*", "CMakeLists.txt"

    def build_requirements(self):
        if self.options.enable_java:
            self.build_requires("java_installer/9.0.0@bincrafters/stable")
        if self.options.enable_java or self.options.enable_dotnet:
            if self.settings.os == "Windows":
                self.build_requires("swig/3.0.12@ulricheck/stable")


    def configure(self):
        if self.settings.os == "Windows":
            self.options.enable_dotnet = True
            
        if self.options.shared:
            self.options['ubitrack_core'].shared = True
            self.options['ubitrack_vision'].shared = True
            self.options['ubitrack_dataflow'].shared = True

    def imports(self):
        self.copy(pattern="*.dll", dst="bin", src="bin") # From bin to bin
        self.copy(pattern="*.dylib*", dst="lib", src="lib") 
       
    def build(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = self.options.shared
        cmake.definitions['ENABLE_BASICFACADE'] = self.options.enable_basicfacade
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
