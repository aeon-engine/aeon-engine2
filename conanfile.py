from conans.errors import ConanInvalidConfiguration
from conans import ConanFile, CMake, tools
import os


class AeonEngineConan(ConanFile):
    name = 'aeon-engine'
    description = 'The Aeon Game Engine'
    license = 'BSD-2-Clause'
    homepage = 'https://git.aeons.dev/aeon-engine/aeon-engine'
    url = 'https://git.aeons.dev/aeon-engine/aeon-engine'
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_multi"
    exports_sources = "engine/*"
    options = {
        'shared': [True, False],
        'fPIC': [True, False],
        'enable_unittests': [True, False]
    }
    default_options = {
        'shared': False,
        'fPIC': True,
        'enable_unittests': True
    }

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

        if self.settings.os != 'Windows':
            del self.options.with_platform
            del self.options.with_gl
            del self.options.with_gl_utils

    def requirements(self):
        self.requires('gtest/1.11.0@aeon/stable')
        self.requires('icu/69.1@aeon/stable')
        self.requires('zlib/1.2.11@aeon/stable')
        self.requires('freetype/2.10.4@aeon/stable')
        self.requires('libpng/1.6.37@aeon/stable')
        self.requires('libjpeg-turbo/2.1.0@aeon/stable')
        self.requires('asio/1.18.2@aeon/stable')
        self.requires('assimp/5.0.1@aeon/stable')

    def configure(self):
        if self.options.shared:
            del self.options.fPIC

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['BUILD_SHARED_LIBS'] = self.options.shared
        cmake.definitions['CMAKE_POSITION_INDEPENDENT_CODE'] = \
            self.options.get_safe('fPIC', default=False) or self.options.shared

        cmake.definitions['AEON_ENABLE_TESTING'] = self.options.enable_unittests

        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

        tools.remove_files_by_mask(self.package_folder, "*.pdb")
