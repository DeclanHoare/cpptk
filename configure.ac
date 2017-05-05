#
# Copyright 2017 Declan Hoare
#
# Permission to copy, use, modify, sell and distribute this software
# is granted provided this copyright notice appears in all copies.
# This software is provided "as is" without express or implied
# warranty, and with no claim as to its suitability for any purpose.
#

AC_INIT([cpptk], [1.0.3], [https://github.com/RogueAI42/cpptk/issues], [cpptk], [https://github.com/RogueAI42/cpptk])
AC_CONFIG_SRCDIR([cpptk.cc])
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_ARG_ENABLE([examples],
	AS_HELP_STRING([--enable-examples], [Build example programs]))
AM_INIT_AUTOMAKE([1.11 -Wall foreign subdir-objects])
AM_CONDITIONAL([ENABLE_EXAMPLES], [test "$enable_examples" = "yes"])
AC_CONFIG_FILES([Makefile cpptk.pc])
AC_PROG_CXX
AM_PROG_AR
PKG_CHECK_MODULES([TK], [tk])
PKG_INSTALLDIR
LT_INIT
AC_OUTPUT
