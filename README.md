# What is it? 
**Directory_Explorer** is a simple, multithreaded console application that given a directory path, recursively crawls around in that path, counts number of directories, files and lines in files.

To complete this task, this program gathers files in specified path, distributes them between collections. Then, each thread takes own collection of files and processes it.

Thread number (specified by parameter) doesn't exceed number of threads supported by hardware. 

This projects uses [Meson](https://mesonbuild.com/) as build system and [Gtest](https://google.github.io/googletest/) as testing framework.

# Dependencies
To build and run this project following dependencies are required:
- Meson build system
    - python3
    - ninja

Optional:
- Gtest (system library used by default, if not present meson will provide)

# Installing dependencies
### Debian based distros (Ubuntu):
    sudo apt update
    sudo apt install build-essential libgtest-dev meson ninja-build

### Redhat based distros (Fedora, Centos, RHEL):
    sudo dnf install gcc-c++ meson ninja-build gtest-devel

### Windows
Please follow instructions stated [here](https://mesonbuild.com/SimpleStart.html).

# Building
Move to cloned project directory and setup the build directory with:

    $ meson setup build

Then build it with ninja

    $ ninja -C build

To build and run just tests:

    $ ninja -C build test

Both program and tests are build this way.
# Running
Execute program by running:

    $ ./build/directory_explorer pathname thread_number

Execute tests by running:

    $ ./build/tests 