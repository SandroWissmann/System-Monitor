# System-Monitor

![System Monitor](images/application.png)

System monitor.

Features:
-Shows utilization of all cores of the CPU
-Shows memory consumption
-Shows the top 10 of the most hungry processes

Currently runs only on Linux with NCurses. But I plan to also add Windows and change the UI to QT with QML/Javascript

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Install ncurses under linux: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has five targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts
* `valgrind` compiles the source code as debug and runs application with valgrind