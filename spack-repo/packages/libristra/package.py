# Copyright 2013-2019 Lawrence Livermore National Security, LLC and other
# Spack Project Developers. See the top-level COPYRIGHT file for details.
#
# SPDX-License-Identifier: (Apache-2.0 OR MIT)


from spack import *


class Libristra(CMakePackage):
    '''Libristra is a support library for other ristra codes.
    '''
    git      = 'https://github.com/laristra/libristra.git'

    version('master', branch='master', submodules=False, preferred=True)
    version('1.0.0', commit='33235fe0334ca7f1f99b386a90932d9f8e1e71de')

    variant('build_type', default='Release', values=('Debug', 'Release'),
            description='The build type to build', multi=False)
    variant('paraview', default=False,
            description='Enable ParaView')
    variant('cinch', default=True,
            description='Enable External Cinch')

    depends_on('cmake@3.12:',  type='build')
    # Requires cinch > 1.0 due to cinchlog installation issue
    depends_on('cinch@1.01:', type='build', when='+cinch')
    depends_on('mpi')
    depends_on('boost@1.70.0: cxxstd=14 +program_options')
    depends_on('lua@5.3.5')
    # TODO: might want to move paraview out of libristra
    depends_on('paraview', when='+paraview')

    def cmake_args(self):
        spec = self.spec
        options = []
        
        if '+cinch' in spec:
            options.append('-DCINCH_SOURCE_DIR=' + spec['cinch'].prefix)

        if self.run_tests:
            options.append('-DENABLE_UNIT_TESTS=ON')
        else:
            options.append('-DENABLE_UNIT_TESTS=OFF')

        return options
