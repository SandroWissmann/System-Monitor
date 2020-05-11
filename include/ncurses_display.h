#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

namespace NCursesDisplay {
void Display(System& system, int n = 10);
void DisplaySystem(System& system, WINDOW* window);

void PrintOS(System& system, WINDOW* window, int& row);
void PrintKernel(System& system, WINDOW* window, int& row);
void PrintCpu(System& system, WINDOW* window, int& row);
void PrintCore(int no, float utilization, WINDOW* window, int& row);
void PrintMemory(System& system, WINDOW* window, int& row);
void PrintSwap(System& system, WINDOW* window, int& row);
void PrintTotalProcesses(System& system, WINDOW* window, int& row);
void PrintRunningProcesses(System& system, WINDOW* window, int& row);
void PrintUpTime(System& system, WINDOW* window, int& row);

std::string ProgressBar(float percent);

void DisplayProcesses(const std::vector<std::shared_ptr<Process>>& processes,
                      WINDOW* window, int n);
};  // namespace NCursesDisplay

#endif