#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

namespace NCursesDisplay {
void Display(System& system, int n = 10);
void DisplaySystem(System& system, WINDOW* window);

void PrintOS(const std::string& os, WINDOW* window, int& row);
void PrintKernel(const std::string& kernel, WINDOW* window, int& row);
void PrintCpu(double utilization, WINDOW* window, int& row);
void PrintCore(int no, double utilization, WINDOW* window, int& row);
void PrintMemory(System& system, WINDOW* window, int& row);
void PrintSwap(double swap, WINDOW* window, int& row);
void PrintTotalProcesses(int totalProcesses, WINDOW* window, int& row);
void PrintRunningProcesses(int runningProcesses, WINDOW* window, int& row);
void PrintUpTime(long uptime, WINDOW* window, int& row);

std::string ProgressBar(double percent);

void PrintProgressBarMemory(double totalUsed, double nonCachedNonBuffer,
                            double buffer, double cached, WINDOW* window,
                            int& row);

std::string ToDisplayPercentage(double percent);

void DisplayProcesses(const std::vector<std::shared_ptr<Process>>& processes,
                      WINDOW* window, int n);
};  // namespace NCursesDisplay

#endif