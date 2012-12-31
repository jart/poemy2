# poemy - A poetry generator

Poemy is a program that creates computer-generated poetry in any meter or
rhyming scheme. It was written by Justine Tunney using C++11 and lots of
Googley libraries. Poemy works by using markov chains and the isledict speech
pronunciation dictionary.

## Getting Started

First you need to install some dependencies:

- `sudo apt-get install build-essential pkg-config autoconf automake ragel`
- Google gflags: <http://code.google.com/p/gflags/>
- Google glog: <http://code.google.com/p/google-glog/>
- Google SparseHash: <http://code.google.com/p/sparsehash/>
- Optional: libunwind: <http://www.nongnu.org/libunwind/>
- Optional: Google gperftools: <http://code.google.com/p/gperftools/>

Then build / install poemy as follows:

    ./autogen.sh
    ./configure CPPFLAGS="-Wall -Werror -pipe -march=native"
    make check -j4

Here's some example invocations of poemy:

    ./poemy
    ./poemy --help
    ./poemy --alsologtostderr --minloglevel=0
    ./poemy --alsologtostderr --tries=500 --lines=40 --corpora=goth --dict=isle
