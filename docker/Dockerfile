FROM laristra/flecsi:fedora30

SHELL ["/bin/bash", "-c"]	
		
ENV DEBIAN_FRONTEND=noninteractive \	
    HOME=/home/laristra \	
    BASH_ENV=~/.bashrc

ARG CC
ARG CXX
ARG CXXFLAGS
ARG BUILD_TYPE
ARG MPI_PACKAGE

#for coverage
ENV CI true
ENV TRAVIS true
ARG TRAVIS_BRANCH
ARG TRAVIS_JOB_NUMBER
ARG TRAVIS_PULL_REQUEST 
ARG TRAVIS_JOB_ID
ARG TRAVIS_TAG
ARG TRAVIS_REPO_SLUG
ARG TRAVIS_COMMIT

COPY libristra/ $HOME/libristra
USER root
RUN chown -R laristra:laristra $HOME/libristra
USER laristra

WORKDIR $HOME
RUN export SPACK_SPEC="libristra%gcc ^$MPI_PACKAGE" && \
    spack repo add --scope site $HOME/libristra/spack-repo && \
    spack find && \
    echo "spack install --show-log-on-error $SPACK_SPEC" && \
    spack install -j 1 --show-log-on-error $SPACK_SPEC && \
    rm deps.sh && \
    rm $HOME/load_deps.sh && \
    spack module tcl loads python | tee -a deps.sh && \
    spack module tcl loads --dependencies $SPACK_SPEC | tee -a deps.sh
RUN echo ". $HOME/spack/share/spack/setup-env.sh && . $HOME/deps.sh" >> $HOME/load_deps.sh

RUN source $HOME/load_deps.sh && module list

WORKDIR $HOME/libristra
RUN mkdir build
WORKDIR build

RUN source $HOME/load_deps.sh && \
    cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
          -DENABLE_LUA=ON \
          -DENABLE_UNIT_TESTS=ON \
          .. && \
    make -j2 || make VERBOSE=1 && \
    make test ARGS="CTEST_OUTPUT_ON_FAILURE=1" && \
    make install DESTDIR=${PWD}/install && rm -rf ${PWD}/install

USER root
RUN make install

USER laristra
WORKDIR $HOME
