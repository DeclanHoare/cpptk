# C++/Tk
C++/Tk (cpptk) is a complete C++ interface to the Tk GUI toolkit.
It aims to replicate Tcl syntax within C++.
It was created by Maciej Sobczak and modified by me for compatibility
with Tcl 8.6 and g++ 6, and for Autotools support.
It is licensed under permissive terms similar to the MIT license (see
the LICENSE file).

The recommended installation method is with Autotools. Run
```
autoreconf -i
./configure
make
```
to build the library and then `make install` as root to install. You can
then link against the library using pkg-config.

Complete documentation can be found in the "doc" directory.

## TODO
* Some tests are currently disabled due to floating point errors.
There may be a way to fix them properly.
* Remove Boost dependency if at all possible.
