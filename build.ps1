mkdir -Force lib
if (!(Test-Path lib/frida-core.lib)) {
	Write-Host "[*] Missing frida-core library for Windows, retrieving..."
	Invoke-WebRequest https://github.com/frida/frida/releases/download/16.1.8/frida-core-devkit-16.1.8-windows-x86_64.tar.xz -Out frida-core-devkit-16.1.8-windows-x86_64.tar.xz
	tar -xf frida-core-devkit-16.1.8-windows-x86_64.tar.xz ./frida-core.lib
	mv frida-core.lib lib/frida-core.lib
	Remove-Item -Force -Confirm:$false frida-core-devkit-16.1.8-windows-x86_64.tar.xz
}

mkdir -Force build
cd build
cmake ..
cd ..

javac -d build src/FridaExample.java
