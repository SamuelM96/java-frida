# Java <-> Frida Example

An example project showing how to call a Frida script from Java using JNI and `frida-core`.

## Usage/Building

### Linux/macOS

```bash
# Install the dependencies (Ubuntu example)
sudo apt install openjdk-11-jdk openjdk-11-jre cmake build-essential
# Or
brew install openjdk@11 cmake

# Build the project
./build.sh # Linux/macOS

# Run the example binary in a separate terminal
./build/example # Linux/macOS

# Run the Java example
./run.sh # Linux/macOS
```

### Windows

```powershell
# Install dependencies
winget install cmake ojdkbuild.openjdk.11.jre ojdkbuild.openjdk.11.jdk Microsoft.VisualStudio.2022.Community

# Build the project
./build.ps1
# Open ./build/java-frida.sln in Visual Studio and run Build > Build Solution

# Run the example binary in a separate terminal
./build/Debug/example.exe

# Run the Java example
./run.ps1
```
