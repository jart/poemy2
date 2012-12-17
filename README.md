# poemy - A poetry generator

Poemy is a poetry generator written in C++11 with Googley libraries that uses
markov chains and speech dictionaries to write poetry in any meter or rhyming
scheme.

## Installation

1. `sudo apt-get install build-essential pkg-config autoconf automake`
2. Install Google gflags: <http://code.google.com/p/gflags/>
3. Install Google glog: <http://code.google.com/p/google-glog/>
4. Install Google SparseHash: <http://code.google.com/p/sparsehash/>
5. Optional: Install libunwind: <http://www.nongnu.org/libunwind/>
6. Optional: Install Google gperftools: <http://code.google.com/p/gperftools/>
7. `./autogen.sh && ./configure && make check -j4`
8. `sudo make install`

## Invocation

    poemy

## Heap profiling

    HEAPPROFILE=/tmp/heap ./poemy
    pprof --gif poemy /tmp/heap.* >/tmp/heap.gif
    eog /tmp/heap.gif
    rm /tmp/heap.*
