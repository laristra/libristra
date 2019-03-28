FROM laristra/flecsi:fedora_serial

ARG CC
ARG CXX
ARG CXXFLAGS
ARG BUILD_TYPE

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

COPY libristra/ /home/flecsi/libristra
USER root
RUN chown -R flecsi:flecsi /home/flecsi/libristra
USER flecsi

WORKDIR /home/flecsi/libristra
RUN mkdir build
WORKDIR build

RUN cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
          -DENABLE_UNIT_TESTS=ON \
          ..
RUN ctest -V -R ristra_elements
RUN make -j2 || make VERBOSE=1
RUN make test ARGS="CTEST_OUTPUT_ON_FAILURE=1"
RUN make install DESTDIR=${PWD}/install && rm -rf ${PWD}/install

USER root
RUN make install

WORKDIR /home/flecsi
