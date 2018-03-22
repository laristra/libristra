The Ristra Library
==================

The ristra library is a set of support utilities for ristra codes, including

* simple mathematical operations (geometry, small matrix operations, and so on)
* physical units
* input parsing

Check out: use recursive clone
---------

Be sure to clone recursively in order to get cinch submodule support!

    git clone --recursive git@github.com:laristra/libristra.git

If you do not, you will see an error like this when you run cmake:

    CMake Error at CMakeLists.txt:38 (include):
      include could not find load file:

        /path/to/libristra/cinch/cmake/ProjectLists.txt

Prerequisites
-------------

* Boost units (for units support)
* Lua support libraries (optional, for Lua input utilities, known to work with Lua 5.3.3)

Quick Start
-----------

```sh
mkdir build
cd build
cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_UNIT_TESTS=True \
    -DENABLE_BOOST_PREPROCESSOR=True \
    -DBOOST_INCLUDEDIR=/path/to/boost \
    -DRISTRA_ENABLE_LUA=True \
    -DLUA_INCLUDE_DIR=/path/to/lua/include \
    -DLUA_LIBRARY=/path/to/lua/lib/liblua.a \
    ..
make
make test
```

Known Issues
------------

Tests may segfault with Clang 4.0.0/4.0.1 on OSX with XCode 8.3.3. This seems to be an issue between the compiler and possibly the runtime libraries implementation of exceptions.

