The Ristra Library
==================

The ristra library is a set of support utilities for ristra codes, including

* simple mathematical operations (geometry, small matrix operations, and so on)
* physical units
* input parsing

Prerequisites
-------------

* Boost units (for units support)
* Lua support libraries (optional, for Lua input utilities, known to work with Lua 5.3.3)

Known Issues
------------

Tests may segfault with Clang 4.0.0/4.0.1 on OSX with XCode 8.3.3. This seems to be an issue between the compiler and possibly the runtime libraries implementation of exceptions.

Quick Start
-----------

    1. module load lua   # Or define LUA_INCLUDE_DIR
    1. mkdir build
    2. cd build
    3. cmake .. -DENABLE_UNIT_TESTS=1
    4. make
    5. cd test/ristra
    6. ./ristra-test
    ...
        [----------] Global test environment tear-down
        [==========] 34 tests from 8 test cases ran. (3 ms total)
        [  PASSED  ] 34 tests.
