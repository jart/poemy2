# poemy - A poetry generator
# Copyright (c) 2012 Justine Alexandra Roberts Tunney

ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = \
	autogen.sh \
	config/ax_check_compile_flag.m4 \
	config/ax_cxx_compile_stdcxx_11.m4 \
	config/pkg.m4 \
	README.md \
	$(shell find gtest-1.6.0)

DISTCLEANFILES = \
	src/cmudict_parse.cc \
	src/isledict_parse.cc

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
	src/MurmurHash3.cc \
	src/cmudict.cc \
	src/cmudict_parse.cc \
	src/cmudict_parse.rl \
	src/corpus.cc \
	src/error.cc \
	src/isledict.cc \
	src/isledict_parse.cc \
	src/isledict_parse.rl \
	src/markov.cc \
	src/memoryfile.cc \
	src/poemy/cmudict.h \
	src/poemy/corpus.h \
	src/poemy/defines.h \
	src/poemy/dict.h \
	src/poemy/error.h \
	src/poemy/hash.h \
	src/poemy/isledict.h \
	src/poemy/markov.h \
	src/poemy/memoryfile.h \
	src/poemy/pronounce.h \
	src/poemy/timeit.h \
	src/poemy/util.h \
	src/pronounce.cc \
	src/timeit.cc \
	src/util.cc
libpoemy_a_CPPFLAGS = $(poemy_CPPFLAGS)

src/isledict_parse.cc: src/isledict_parse.rl
src/cmudict_parse.cc: src/cmudict_parse.rl

src/%.cc: src/%.rl
	@echo "  RL    " $@;
	@ragel -G2 -o $@ $<

######################################################################
## testing

check_PROGRAMS = test
TESTS = $(check_PROGRAMS)

test_SOURCES = \
	gtest-1.6.0/src/gtest-all.cc \
	src/cmudict_test.cc \
	src/corpus_test.cc \
	src/error_test.cc \
	src/hash_test.cc \
	src/isledict_test.cc \
	src/pronounce_test.cc \
	src/test.cc
test_CPPFLAGS = $(poemy_CPPFLAGS) -Igtest-1.6.0 -Igtest-1.6.0/include -pthread
test_LDADD = $(poemy_LDADD) -lpthread
