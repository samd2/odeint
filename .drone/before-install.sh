#!/bin/bash

if [ "$DRONE_JOB_UUID" = "b6589fc6ab" ] || [ "$DRONE_JOB_UUID" = "356a192b79" ] ; then
    wget https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2/download?use_mirror=superb-dca2 -O /tmp/boost.tar.bz2
    tar jxf /tmp/boost.tar.bz2
    mv boost_1_63_0 $PWD/boost-trunk
    export BOOST_ROOT="$PWD/boost-trunk"
    cd $BOOST_ROOT
    ./bootstrap.sh
    cd $TRAVIS_BUILD_DIR
    if [ "$TRAVIS_OS_NAME" = "osx" ] && [ "$CC" = "gcc" ]; then export CC=gcc-4.8; fi
    echo $CC
    $CC --version
fi

