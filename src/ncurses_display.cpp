#include "ncurses_display.h"

#include "format.h"
#include "system.h"

#include <curses.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

using std::string;
using std::to_string;

namespace NCursesDisplay {

static constexpr auto colorBlue = 1;
static constexpr auto colorGreen = 2;
static constexpr auto colorYellow = 3;

void Display(System& system, int n) {
    initscr();      // start ncurses
    noecho();       // do not print input values
    cbreak();       // terminate ncurses on ctrl + c
    start_color();  // enable color

    int x_max{getmaxx(stdscr)};

    auto countOfSystemRows = 10 + system.Cpu()->CountOfCores();
    WINDOW* system_window = newwin(countOfSystemRows, x_max - 1, 0, 0);

    WINDOW* process_window =
        newwin(3 + n, x_max - 1, system_window->_maxy + 1, 0);

    while (1) {
        init_pair(colorBlue, COLOR_BLUE, COLOR_BLACK);
        init_pair(colorGreen, COLOR_GREEN, COLOR_BLACK);
        init_pair(colorYellow, COLOR_YELLOW, COLOR_BLACK);
        box(system_window, 0, 0);
        box(process_window, 0, 0);
        DisplaySystem(system, system_window);
        DisplayProcesses(system.Processes(), process_window, n);
        wrefresh(system_window);
        wrefresh(process_window);
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    endwin();
}

void DisplaySystem(System& system, WINDOW* window) {
    int row{0};
    PrintOS(system.OperatingSystem(), window, row);
    PrintKernel(system.Kernel(), window, row);
    PrintCpu(system.Cpu()->Utilization(), window, row);

    auto coreUtilisations = system.Cpu()->CoreUtilizations();
    for (int i = 0; i < static_cast<int>(coreUtilisations.size()); ++i) {
        PrintCore(i + 1, coreUtilisations[i], window, row);
    }

    PrintMemory(system, window, row);
    PrintSwap(system.MemoryUtilization()->SwapInPercent(), window, row);
    PrintTotalProcesses(system.TotalProcesses(), window, row);
    PrintRunningProcesses(system.RunningProcesses(), window, row);
    PrintUpTime(system.UpTime(), window, row);
    wrefresh(window);
}

void PrintOS(const std::string& os, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, ("OS: " + os).c_str());
}

void PrintKernel(const std::string& kernel, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, ("Kernel: " + kernel).c_str());
}

void PrintCpu(double utilization, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "CPU: ");
    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(utilization).c_str());
    wattroff(window, COLOR_PAIR(colorBlue));
}

void PrintCore(int no, double utilization, WINDOW* window, int& row) {
    std::string core = "Core " + std::to_string(no) + ':';
    mvwprintw(window, ++row, 2, core.c_str());
    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(utilization).c_str());
    wattroff(window, COLOR_PAIR(colorBlue));
}

void PrintMemory(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "Memory: ");

    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, 10, "");
    wattroff(window, COLOR_PAIR(colorBlue));

    PrintProgressBarMemory(
        system.MemoryUtilization()->TotalUsedMemoryInPercent(),
        system.MemoryUtilization()->NonCacheNonBufferMemoryInPercent(),
        system.MemoryUtilization()->BuffersInPercent(),
        system.MemoryUtilization()->CachedMemoryInPercent(), window, row);

    wattroff(window, COLOR_PAIR(colorGreen));
}

void PrintSwap(double swap, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "Swap: ");
    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(swap).c_str());
    wattroff(window, COLOR_PAIR(colorBlue));
}

void PrintTotalProcesses(int totalProcesses, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2,
              ("Total Processes: " + to_string(totalProcesses)).c_str());
}

void PrintRunningProcesses(int runningProcesses, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2,
              ("Running Processes: " + to_string(runningProcesses)).c_str());
}

void PrintUpTime(long uptime, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2,
              ("Up Time: " + Format::ElapsedTime(uptime)).c_str());
}

// 50 bars uniformly displayed from 0 - 100 %
// 2% is one bar(|)
std::string ProgressBar(double percent) {
    std::string result{"0%"};
    int size{50};
    double bars{percent * size};

    for (int i{0}; i < size; ++i) {
        result += i <= bars ? '|' : ' ';
    }

    auto display = ToDisplayPercentage(percent);
    return result + " " + display + "/100%";
}

void PrintProgressBarMemory(double totalUsed, double nonCachedNonBuffer,
                            double buffer, double cached, WINDOW* window,
                            int& row) {
    constexpr auto size{50};

    const std::string percent0 = "0%";

    auto filled1 = static_cast<int>(nonCachedNonBuffer * size);
    std::string str1(filled1, '|');

    auto filled2 = static_cast<int>(buffer * size);
    std::string str2(filled2, '|');

    auto filled3 = static_cast<int>(cached * size);
    std::string str3(filled3, '|');

    auto empty = size - filled1 - filled2 - filled3;
    std::string str4(empty, ' ');

    auto display = ToDisplayPercentage(totalUsed);

    const std::string percent100 = "/100%";

    auto offset = 10;

    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, offset, percent0.c_str());

    offset += static_cast<int>(percent0.size());
    mvwprintw(window, row, offset, str1.c_str());
    wattroff(window, COLOR_PAIR(colorBlue));

    offset += filled1;
    wattron(window, COLOR_PAIR(colorYellow));
    mvwprintw(window, row, offset, str2.c_str());
    wattroff(window, COLOR_PAIR(colorYellow));

    offset += filled2;
    wattron(window, COLOR_PAIR(colorGreen));
    mvwprintw(window, row, offset, str3.c_str());
    wattroff(window, COLOR_PAIR(colorGreen));

    offset += filled3;
    mvwprintw(window, row, offset, str4.c_str());

    wattron(window, COLOR_PAIR(colorBlue));

    offset += empty;
    std::string fillEnd = " ";
    mvwprintw(window, row, offset, fillEnd.c_str());

    offset += static_cast<int>(fillEnd.size());
    wattron(window, COLOR_PAIR(colorBlue));
    mvwprintw(window, row, offset, display.c_str());

    offset += static_cast<int>(display.size());
    mvwprintw(window, row, offset, percent100.c_str());

    wattroff(window, COLOR_PAIR(colorBlue));
}

std::string ToDisplayPercentage(double percent) {
    std::string display{std::to_string(percent * 100).substr(0, 4)};
    if (percent < 0.1 || percent == 1.0) {
        display = " " + std::to_string(percent * 100).substr(0, 3);
    }
    return display;
}

void DisplayProcesses(const std::vector<std::shared_ptr<Process>>& processes,
                      WINDOW* window, int n) {
    int row{0};
    int const pid_column{2};
    int const user_column{9};
    int const cpu_column{16};
    int const ram_column{26};
    int const time_column{35};
    int const command_column{46};
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, ++row, pid_column, "PID");
    mvwprintw(window, row, user_column, "USER");
    mvwprintw(window, row, cpu_column, "CPU[%%]");
    mvwprintw(window, row, ram_column, "RAM[MB]");
    mvwprintw(window, row, time_column, "TIME+");
    mvwprintw(window, row, command_column, "COMMAND");
    wattroff(window, COLOR_PAIR(2));

    for (int i = 0; i < n && i < static_cast<int>(processes.size()); ++i) {
        mvwprintw(window, ++row, pid_column,
                  to_string(processes[i]->Pid()).c_str());
        mvwprintw(window, row, user_column, processes[i]->User().c_str());
        double cpu = processes[i]->CpuUtilization() * 100;
        mvwprintw(window, row, cpu_column, to_string(cpu).substr(0, 4).c_str());
        mvwprintw(window, row, ram_column,
                  std::to_string(processes[i]->RamInMb()).c_str());
        mvwprintw(window, row, time_column,
                  Format::ElapsedTime(processes[i]->UpTime()).c_str());
        mvwprintw(
            window, row, command_column,
            processes[i]->Command().substr(0, window->_maxx - 46).c_str());
    }
}

}  // namespace NCursesDisplay