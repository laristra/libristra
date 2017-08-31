The Ristra Library
==================

The ristra library is a set of support utilities for ristra codes, including

* simple mathematical operations (geometry, small matrix operations, and so on)
* physical units
* input parsing

Prerequisites
-------------

* Boost units
* Lua and Python support
* Cinch and the projects it uses as submodules (especially Google Test)

Known Issues
------------

Tests may segfault with Clang 4.0.0/4.0.1 on OSX with XCode 8.3.3. This seems to be an issue between the compiler and possibly the runtime libraries implementation of exceptions.
