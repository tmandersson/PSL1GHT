#!/usr/bin/env bash

pkgver=1.2.5

wget -c http://zlib.net/zlib-$pkgver.tar.gz
tar xvf zlib-$pkgver.tar.gz
pushd zlib-$pkgver
CC="ppu-gcc" CFLAGS="-g -O2 -Wall" ./configure --static
make
popd
