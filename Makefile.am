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
	src/corpus.h \
	src/isledict.cc \
	src/isledict.h \
	src/markov.cc \
	src/markov.h \
	src/poemy.h \
	src/util.cc \
	src/util.h
libpoemy_a_CPPFLAGS = $(poemy_CPPFLAGS)

######################################################################
## testing

check_PROGRAMS = test_corpus
check_LIBRARIES = libgtest.a
TESTS = $(check_PROGRAMS)
GTEST_CPPFLAGS = -I$(GTEST_DIR)/include -pthread
GTEST_LIBS = libgtest.a -lpthread

libgtest_a_SOURCES = \
	$(GTEST_DIR)/include/gtest/gtest.h \
	$(GTEST_DIR)/src/gtest-all.cc
libgtest_a_CPPFLAGS = -I$(GTEST_DIR) $(GTEST_CPPFLAGS)

test_corpus_SOURCES = src/test_corpus.cc
test_corpus_CPPFLAGS = $(poemy_CPPFLAGS) $(GTEST_CPPFLAGS)
test_corpus_LDADD = $(poemy_LDADD) $(GTEST_LIBS)
