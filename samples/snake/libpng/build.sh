#!/usr/bin/env bash

PREFIX=$PWD

zpkgver=1.2.5

wget -c http://zlib.net/zlib-$zpkgver.tar.gz
tar xvf zlib-$zpkgver.tar.gz
pushd zlib-$zpkgver
CC="ppu-gcc" RANLIB="ppu-ranlib" AR="ppu-ar" CFLAGS="-g -O2 -Wall" ./configure --prefix=$PREFIX
make
make install
popd

rm lib/*.so*

ppkgver=1.4.4

wget -c http://sourceforge.net/projects/libpng/files/01-libpng-master/$ppkgver/libpng-$ppkgver.tar.gz/download -O libpng-$ppkgver.tar.gz
tar xvf libpng-$ppkgver.tar.gz
pushd libpng-$ppkgver
CFLAGS="-g -O2 -Wall -L$PREFIX/lib -I$PREFIX/include" ./configure --host=powerpc64-linux --disable-shared --enable-static --prefix=$PREFIX
make
make install
popd


pushd pixman*
CFLAGS="-g -O2 -Wall -DPIXMAN_NO_TLS" ./configure --prefix=/home/phire/ps3/PSL1GHT/samples/snake/libpng/ --host=powerpc64-linux --disable-shared --enable-static
make
make install
popd
