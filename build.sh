#!/bin/bash

set -Eeuo pipefail

mkdir -p lib
if [ ! -f lib/libfrida-core-linux-x86_64.a ]; then
	echo "[*] Missing frida-core library for Linux, retrieving..."
	wget -q --show-progress https://github.com/frida/frida/releases/download/16.1.8/frida-core-devkit-16.1.8-linux-x86_64.tar.xz
	tar -xf frida-core-devkit-16.1.8-linux-x86_64.tar.xz ./libfrida-core.a
	mv libfrida-core.a lib/libfrida-core-linux-x86_64.a
	rm frida-core-devkit-16.1.8-linux-x86_64.tar.xz
fi

if [ ! -f lib/libfrida-core-macos-arm64.a ]; then
	echo "[*] Missing frida-core library for macOS, retrieving..."
	wget -q --show-progress https://github.com/frida/frida/releases/download/16.1.8/frida-core-devkit-16.1.8-macos-arm64.tar.xz
	tar -xf frida-core-devkit-16.1.8-macos-arm64.tar.xz ./libfrida-core.a
	mv libfrida-core.a lib/libfrida-core-macos-arm64.a
	rm frida-core-devkit-16.1.8-macos-arm64.tar.xz
fi

mkdir -p build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
popd

javac -d build src/FridaExample.java
