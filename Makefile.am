#
# Copyright 2017 Declan Hoare
#
# Permission to copy, use, modify, sell and distribute this software
# is granted provided this copyright notice appears in all copies.
# This software is provided "as is" without express or implied
# warranty, and with no claim as to its suitability for any purpose.
#

ACLOCAL_AMFLAGS = -I m4

# the library
lib_LTLIBRARIES = libcpptk.la
nobase_pkginclude_HEADERS = base/cpptkbase.h cpptkoptions.x cpptkconstants.x cpptk.h
libcpptk_la_SOURCES = base/cpptkbase.cc cpptk.cc
libcpptk_la_CXXFLAGS = @TK_CFLAGS@
libcpptk_la_LDFLAGS = -version-info 0:0:0 @TK_LIBS@

# pkg-config information
pkgconfig_DATA = cpptk.pc

# test suite
check_PROGRAMS = cpptktest cpptktest2
cpptktest_SOURCES = base/cpptkbase.cc cpptk.cc test/test.cc
cpptktest_CXXFLAGS = @TK_CFLAGS@ -DCPPTK_DUMP_COMMANDS -DCPPTK_DONT_EVALUATE
cpptktest_LDFLAGS = @TK_LIBS@
cpptktest2_SOURCES = test/test2.cc
cpptktest2_CXXFLAGS = @TK_CFLAGS@
cpptktest2_LDFLAGS = @TK_LIBS@ -lcpptk
TESTS = $(check_PROGRAMS)

# example programs
if ENABLE_EXAMPLES
bin_PROGRAMS = cpptk-example0 cpptk-example1 cpptk-example2 cpptk-example3 cpptk-example4 cpptk-example5 cpptk-example6
cpptk_example0_SOURCES = examples/example0.cc
cpptk_example0_CXXFLAGS = @TK_CFLAGS@
cpptk_example0_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example0_DEPENDENCIES = libcpptk.la
cpptk_example1_SOURCES = examples/example1.cc
cpptk_example1_CXXFLAGS = @TK_CFLAGS@
cpptk_example1_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example1_DEPENDENCIES = libcpptk.la
cpptk_example2_SOURCES = examples/example2.cc
cpptk_example2_CXXFLAGS = @TK_CFLAGS@
cpptk_example2_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example2_DEPENDENCIES = libcpptk.la
cpptk_example3_SOURCES = examples/example3.cc
cpptk_example3_CXXFLAGS = @TK_CFLAGS@
cpptk_example3_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example3_DEPENDENCIES = libcpptk.la
cpptk_example4_SOURCES = examples/example4.cc
cpptk_example4_CXXFLAGS = @TK_CFLAGS@
cpptk_example4_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example4_DEPENDENCIES = libcpptk.la
cpptk_example5_SOURCES = examples/example5.cc
cpptk_example5_CXXFLAGS = @TK_CFLAGS@
cpptk_example5_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example5_DEPENDENCIES = libcpptk.la
cpptk_example6_SOURCES = examples/example6.cc
cpptk_example6_CXXFLAGS = @TK_CFLAGS@
cpptk_example6_LDFLAGS = @TK_LIBS@ -lcpptk
EXTRA_cpptk_example6_DEPENDENCIES = libcpptk.la
endif

# documentation
html_DATA = doc/doc.html
