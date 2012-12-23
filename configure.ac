# -*- Autoconf -*-
# poemy - A poetry generator
# Copyright (c) 2012 Justine Alexandra Roberts Tunney

AC_PREREQ(2.61)
AC_INIT([poemy], [0.1], [jtunney@gmail.com])

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_MACRO_DIR(config)
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/main.cc])
ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
PKG_PROG_PKG_CONFIG([0.22])

AC_LANG(C++)
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
AC_PROG_RANLIB

PKG_CHECK_MODULES(LIBGFLAGS, libgflags)
PKG_CHECK_MODULES(LIBGLOG, libglog)
PKG_CHECK_MODULES(LIBSPARSEHASH, libsparsehash)
PKG_CHECK_MODULES(LIBPROFILER, libprofiler,
    [AC_DEFINE([HAVE_PROFILER], [true], [Is gperftools profiler enabled?])],
    [AC_DEFINE([HAVE_PROFILER], [false], [Is gperftools profiler enabled?])])
PKG_CHECK_MODULES(LIBTCMALLOC, libtcmalloc,
    [AC_DEFINE([HAVE_TCMALLOC], [true], [Is gperftools tcmalloc enabled?])],
    [AC_DEFINE([HAVE_TCMALLOC], [false], [Is gperftools tcmalloc enabled?])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
