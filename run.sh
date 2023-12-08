#!/bin/bash

if [ ! -d build ]; then
	./build.sh
fi

pushd build
EXAMPLE_PID=$(ps -Ac -o pid,comm | awk '/^ *[0-9]+ example$/ {print $1}')
if [ -z $EXAMPLE_PID ]; then
	echo "Start ./build/example in another terminal"
else
	java FridaExample $EXAMPLE_PID ../src/script.js
fi
popd
