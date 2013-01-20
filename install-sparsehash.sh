#!/bin/bash
set -ex

VERSION="2.0.2"

pushd /tmp
rm -rf sparsehash-$VERSION sparsehash-$VERSION.tar.gz
wget http://sparsehash.googlecode.com/files/sparsehash-$VERSION.tar.gz || \
    exit $?
tar -xzf sparsehash-$VERSION.tar.gz || exit $?
pushd sparsehash-$VERSION
./configure || exit $?
make -j4 || exit $?
sudo make install || exit $?
popd
rm -rf sparsehash-$VERSION sparsehash-$VERSION.tar.gz
popd

echo -e "\e[1;32msuccess\e[0m"
