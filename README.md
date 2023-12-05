# Java <-> Frida Example

An example project showing how to call a Frida script using JNI and `frida-core`.

## Usage
```bash
# Install the dependencies
sudo apt install openjdk-11-jdk openjdk-11-jre cmake build-essential
pip3 install frida-tools

# Build the project
./build.sh

# Run the example binary in a separate terminal
./build/example

# Run the Java example
./run.sh
```
