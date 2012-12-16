#!/bin/sh
set -x
aclocal --install --force -I config || exit $?
autoreconf --install --force --verbose -I config || exit $?
