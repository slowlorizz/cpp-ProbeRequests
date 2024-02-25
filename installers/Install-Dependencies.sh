#!/bin/bash

LIBTINS_DIR="../libs/libtins"

if [[ "${PWD}" =~ ^.*\/installers$ ]]
then
    cwd="${PWD}"

    git clone https://github.com/mfontanini/libtins.git $LIBTINS_DIR

    apt-get install -y libpcap-dev libssl-dev cmake

    mkdir "${LIBTINS_DIR}/build"
    cd "${LIBTINS_DIR}/build"

    cmake ../ -DLIBTINS_ENABLE_CXX11=1
    #make

    make install
    ldconfig

    cd $cwd
else
    printf "NOT ON INSTALLER PATH\n"
fi