#!/bin/bash

if [ ! -d build ]; then
	./build.sh
fi

pushd build
EXAMPLE_PID=$(frida-ps | grep example | cut -d' ' -f1)
if [ -z $EXAMPLE_PID ]; then
	echo "Start ./build/example in another terminal"
else
	java FridaExample $EXAMPLE_PID ../src/script.js
fi
popd
