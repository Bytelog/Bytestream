#!/usr/bin/env bash

if [ ! -d "build" ]; then
    meson build
fi

cd build
ninja
cd meson-out
ln -sf ../../assets assets
./client
