# poemy - A poetry generator

Poemy is a program that creates computer-generated poetry in any meter or
rhyming scheme. It was written by Justine Tunney using C++11 and lots of
Googley libraries. Poemy works by using markov chains and the isledict speech
pronunciation dictionary.

## Getting Started

First you need to install some dependencies:

- `sudo apt-get install build-essential`
- Google gflags: <http://code.google.com/p/gflags/>
- Google glog: <http://code.google.com/p/google-glog/>
- Google SparseHash: <http://code.google.com/p/sparsehash/>

Then build / install poemy as follows:

    ./configure
    make check -j4
    sudo make install

Here's some example commands for using poemy:

    poemy
    poemy --help
    poemy --alsologtostderr --minloglevel=0

## Developers

Want to hack poemy? First you'll need to install some additional dependencies:

- `sudo apt-get install pkg-config autoconf automake`
- libunwind: <http://www.nongnu.org/libunwind/>
- Google gperftools: <http://code.google.com/p/gperftools/>

Then create a developers build:

    ./autogen.sh
    ./configure CPPFLAGS="-O0 -g3 -fno-inline -Wall -pipe -march=native"
    make check -j4

Here's how to check for leaks:

    HEAPCHECK=normal ./poemy

Here's how to do a heap profile:

    HEAPPROFILE=/tmp/heap ./poemy
    pprof --gif poemy /tmp/heap.* >/tmp/heap.gif
    chrome /tmp/heap.gif
    rm /tmp/heap.*
