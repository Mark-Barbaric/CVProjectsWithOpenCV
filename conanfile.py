from conans import ConanFile

class OpenCVConanFile(ConanFile):

    settings = 'os', 'os_build', 'compiler', 'build_type', 'arch', 'arch_build'

    requires = ['opencv/4.5.2']

    default_options = {
        'libpng:shared' : True
    }

    generators = 'cmake', 'cmake_find_package', 'cmake_paths', 'txt'