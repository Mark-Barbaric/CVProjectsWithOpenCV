from conans import ConanFile

class OpenCVConanFile(ConanFile):

    settings = 'os', 'os_build', 'compiler', 'build_type', 'arch', 'arch_build'
    generators = 'cmake', 'cmake_find_package', 'cmake_paths', 'txt'

    def requirements(self):
        self.requires('opencv/4.5.2')

        if self.settings.os == "Windows":
            ...
        #    self.requires('OpenSSL/1.1.1n@conan/stable')
        else:
            self.requires('openssl/1.1.1c')
