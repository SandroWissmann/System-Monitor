# System-Monitor

![System Monitor](images/application.png)

# Features:
* Displays utilization of all cores of the CPU
* Displays memory consumption
* Displays the top 10 of the most hungry processes
* Displays System and kernel version
* Displays System uptime

Currently runs only on Linux with NCurses. 
I plan to also add Windows and change the UI to QT with QML/Javascript

## Dependencies for Running Locally

* cmake >= 3.7
  * [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 
  * `make` is installed by default on most Linux distros
* ncurses >= 6.1
  * Install with `sudo apt install libncurses5-dev libncursesw5-dev`


## Running the application

1. Clone repo
1. Go to folder `System-Monitor`
2. Run `make build`
3. `cd build`
4. `./monitor`


## Additional Commands from Makefile

* `make debug` -> builds with debug information
* `make format` -> runs [clangFormat](https://clang.llvm.org/docs/ClangFormat.html) on project
* `make clean` -> deletes build folder
* `make memcheck` -> builds app and runs it with [valgrind](https://www.valgrind.org/)

