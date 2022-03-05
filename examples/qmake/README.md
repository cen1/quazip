# QMake example

This is a simple Qt console application that extacts a local zip file.

# Build and use on Windows

Prerequisite installs:
- Visual Studio
- Qt5 and Qt creator  (from official Windows installer)
- cmake
- git

## Install zlib

In Visual Studio, Tools -> Command Line -> Developer Command Prompt
```
git clone https://github.com/madler/zlib.git
cd zlib
cmake -G "NMake Makefiles" -B./build_release -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="C:/zlib"
cd build_release
nmake install
cd ..
cmake -G "NMake Makefiles" -B./build_debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="C:/zlib"
cd build_debug
nmake install
```

This builds an installs zlib into `C:/zlib`. You can add this to your PATH or just use the absolute path in qmake file.
For the sake of simplicity, we just use the absolute path in this example.

## Install quazip

In Visual Studio, Tools -> Command Line -> Developer Command Prompt
```
git clone https://github.com/stachenov/quazip.git
cd quazip
cmake -G "NMake Makefiles" -B./build_release -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="C:/quazip"
cd build_release
nmake install
cd ..
cmake -G "NMake Makefiles" -B./build_debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="C:/quazip"
cd build_debug
nmake install
```

This builds an installs quazip into `C:/quazip`. You can add this to your PATH or just use the absolute path in qmake file.
For the sake of simplicity, we just use the absolute path in this example.

## Compile and run the sample

Open this project in QT creator and Build -> Run qmake. Switch build to release mode, then build.
Under left menu Projects -> Build & Run -> Run, add a command line argument which should be absolute path to helloworld.zip in quotes.
For example: `"C:/Users/me/git/quazip/examples/qmake/helloworld.zip"`

Running the project will extract the files into the current working directory.