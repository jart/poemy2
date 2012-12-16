ACLOCAL_AMFLAGS = -I config

EXTRA_DIST = \
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
poemy_CPPFLAGS = $(LIBSPARSEHASH_CFLAGS)
poemy_LDADD = $(LIBSPARSEHASH_LIBS)

src/islelex.c: src/islelex.rl
	ragel -G2 -o src/islelex.c src/islelex.rl
