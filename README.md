# Preface
## Task
Create the application that will analyze and show statistics of specified directory that will handle recursive directories. It should print number of files and total number of lines (might as well count non-empty and empty lines). Provide unit tests for solutions.

- Application should use multithreading (keep in mind system limitations, you might need to control number of concurrent calls, e.g., use thread pool).

- Use std::filesystem

- Use GTest for Unit Tests

- As a bonus, you could also count words and letters and provide performance benchmarks (e.g., measure the impact of using the different number of threads).
## My comments
This projects uses Meson as build system.

To complete this task, my program gathers files in specified path, distributes them between collections. Then, each thread takes own collection of files and processes it.

Thread number (specified by parameter) doesn't exceed number of threads supported by hardware. 

# Dependencies
To build and run this project following dependencies are required:
- GTK development tools 
- Meson build system
    - python3
    - ninja

Optional:
- Gtest (system library used by default, if not present meson will provide)

# Installing dependencies
## GTK development tools
### Debian based distros (Ubuntu):
    sudo apt update
    sudo apt install build-essential
### Redhat based distros (Fedora, Centos, RHEL):
    sudo dnf install gcc-c++
## Meson
### Debian based distros (Ubuntu):
    sudo apt update
    sudo apt install meson ninja-build

### Redhat based distros (Fedora, Centos, RHEL):
    sudo dnf install meson ninja-build

### Windows
Please follow instructions stated ![here](https://mesonbuild.com/SimpleStart.html).

# Building
Setup the build enviroment:

    $ cd /project_dir
    $ meson setup build
Then build it with ninja

    $ ninja -C build
Both program and tests are build this way.
# Running
Execute program by running:

    $ ./build/bcf pathname_str thread_number

Execute tests by running:

    $ ./build/tests 