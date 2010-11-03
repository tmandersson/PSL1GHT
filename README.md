PSL1GHT
=======

PSL1GHT is a lightweight PlayStation 3 homebrew SDK, provided as a temporary
way to compile user apps to run from the XMB using the open-source PS3
toolchains available.


Credits
-------

Tempus - default package ICON0.PNG


Environment
-----------

A GCC toolchain that supports the PowerPC 64bit architecture is required to
build PSL1GHT and its samples. It also requires the toolchain to provide
a full newlib environment; at the moment only two toolchains do so:

* [ps3chain](http://github.com/HACKERCHANNEL/ps3chain)
* [ps3toolchain](http://github.com/ooPo/ps3toolchain)

The SDK also includes a few standalone tools to help compilation. A host gcc
is required to build raw2h, and sprxlinker requires libelf. Python 2.x is
required to run fself.py

Building
--------

Run make install in the psl1ght directory to build it all, and make sure to
set the environment variable $PSL1GHT to the folder where you wish to
install it to, for example...

    cd /path/to/psl1ght.git
    export PSL1GHT=/path/to/psl1ght.git/build
    make
    make install

... for a local build of it. Ensure that $PSL1GHT is set when you are
building any of the examples or other apps that use PSL1GHT.


Status
------

Graphics

Simple Framebuffer: Yes

3D: No

Input
Ps3 controllers fully supported.

Networking
The main functions for sockets are available, berkleys based.

SPRX's
Any libraries available to ps3 apps can be used, the exports just need to be filled out.
Currently we support:
libio
|
|-> libpad
|-> libmouse
liblv2
libsysutil
More to come.

File Access
As far as I know, only fstat is missing.

Stdout Debugging
Using Kammy's lv2 hook you can debug output to stdout using udp.
