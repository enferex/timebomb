timebomb: C++ header for implementing compile time asserts based on date.
=========================================================================

This header-only "library" provides utility functions that can be used to write
static assertions that trigger on a particular `__DATE__`. This might be useful
when planning a future deprecation of an API.

This header requires c++20 or later and also makes use of the compiler provided
`__DATE__` macro.

Usage
-----
Include "timebomb.hh" in your source file(s).
See test.cc and example.hh

Building
--------
Run `make`

Contact
-------
Matt Davis: https://github.com/enferex
