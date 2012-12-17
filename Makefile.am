ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = \
	README.md \
	autogen.sh \
	config/ax_check_compile_flag.m4 \
	config/ax_cxx_compile_stdcxx_11.m4 \
	config/pkg.m4

bin_PROGRAMS = poemy

poemy_SOURCES = \
	src/corpus.cc src/corpus.h \
	src/main.cc \
	src/isledict.cc src/isledict.h \
	src/markov.cc src/markov.h \
	src/poemy.h \
	src/util.cc src/util.h
poemy_CPPFLAGS = \
	$(LIBGFLAGS_CFLAGS) \
	$(LIBGLOG_CFLAGS) \
	$(LIBPROFILER_CFLAGS) \
	$(LIBSPARSEHASH_CFLAGS) \
	$(LIBTCMALLOC_CFLAGS)
poemy_LDADD = \
	$(LIBGFLAGS_LIBS) \
	$(LIBGLOG_LIBS) \
	$(LIBPROFILER_LIBS) \
	$(LIBSPARSEHASH_LIBS) \
	$(LIBTCMALLOC_LIBS)

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
