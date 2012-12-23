# poemy - A poetry generator
# Copyright (c) 2012 Justine Alexandra Roberts Tunney

ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = \
	autogen.sh \
	config/ax_check_compile_flag.m4 \
	config/ax_cxx_compile_stdcxx_11.m4 \
	config/pkg.m4 \
	README.md

bin_PROGRAMS = poemy
noinst_LIBRARIES = libpoemy.a

poemy_SOURCES = src/main.cc
poemy_CPPFLAGS = \
	-Isrc \
	$(LIBGFLAGS_CFLAGS) \
	$(LIBGLOG_CFLAGS) \
	$(LIBPROFILER_CFLAGS) \
	$(LIBSPARSEHASH_CFLAGS) \
	$(LIBTCMALLOC_CFLAGS)
poemy_LDADD = \
	libpoemy.a \
	$(LIBGFLAGS_LIBS) \
	$(LIBGLOG_LIBS) \
	$(LIBPROFILER_LIBS) \
	$(LIBSPARSEHASH_LIBS) \
	$(LIBTCMALLOC_LIBS)

libpoemy_a_SOURCES = \
	src/corpus.cc \
	src/error.cc \
	src/isledict.cc \
	src/markov.cc \
	src/poemy/corpus.h \
	src/poemy/defines.h \
	src/poemy/error.h \
	src/poemy/isledict.h \
	src/poemy/markov.h \
	src/poemy/util.h \
	src/util.cc
libpoemy_a_CPPFLAGS = $(poemy_CPPFLAGS)

######################################################################
## testing

check_PROGRAMS = test
TESTS = $(check_PROGRAMS)

test_SOURCES = \
	src/corpus_test.cc \
	src/error_test.cc \
	src/test.cc \
	gtest-1.6.0/src/gtest-all.cc
test_CPPFLAGS = $(poemy_CPPFLAGS) -Igtest-1.6.0 -Igtest-1.6.0/include -pthread
test_LDADD = $(poemy_LDADD) -lpthread
