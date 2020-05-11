#include <curses.h>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

using std::string;
using std::to_string;

namespace NCursesDisplay {

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
        init_pair(1, COLOR_BLUE, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
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
    PrintOS(system, window, row);
    PrintKernel(system, window, row);
    PrintCpu(system, window, row);

    auto coreUtilisations = system.Cpu()->CoreUtilizations();
    for (int i = 0; i < static_cast<int>(coreUtilisations.size()); ++i) {
        PrintCore(i + 1, coreUtilisations[i], window, row);
    }

    PrintMemory(system, window, row);
    PrintSwap(system, window, row);
    PrintTotalProcesses(system, window, row);
    PrintRunningProcesses(system, window, row);
    PrintUpTime(system, window, row);
    wrefresh(window);
}

void PrintOS(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
}

void PrintKernel(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, ("Kernel: " + system.Kernel()).c_str());
}

void PrintCpu(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "CPU: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(system.Cpu()->Utilization()).c_str());
    wattroff(window, COLOR_PAIR(1));
}

void PrintCore(int no, float utilization, WINDOW* window, int& row) {
    std::string core = "Core " + std::to_string(no) + ':';
    mvwprintw(window, ++row, 2, core.c_str());
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window, ProgressBar(utilization).c_str());
    wattroff(window, COLOR_PAIR(1));
}

void PrintMemory(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "Memory: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window,
            ProgressBar(system.MemoryUtilization()->TotalUsedMemoryInPercent())
                .c_str());
    wattroff(window, COLOR_PAIR(1));
}

void PrintSwap(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2, "Swap: ");
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, row, 10, "");
    wprintw(window,
            ProgressBar(system.MemoryUtilization()->SwapInPercent()).c_str());
    wattroff(window, COLOR_PAIR(1));
}

void PrintTotalProcesses(System& system, WINDOW* window, int& row) {
    mvwprintw(
        window, ++row, 2,
        ("Total Processes: " + to_string(system.TotalProcesses())).c_str());
}

void PrintRunningProcesses(System& system, WINDOW* window, int& row) {
    mvwprintw(
        window, ++row, 2,
        ("Running Processes: " + to_string(system.RunningProcesses())).c_str());
}

void PrintUpTime(System& system, WINDOW* window, int& row) {
    mvwprintw(window, ++row, 2,
              ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());
}

// 50 bars uniformly displayed from 0 - 100 %
// 2% is one bar(|)
std::string ProgressBar(float percent) {
    std::string result{"0%"};
    int size{50};
    float bars{percent * size};

    for (int i{0}; i < size; ++i) {
        result += i <= bars ? '|' : ' ';
    }

    string display{to_string(percent * 100).substr(0, 4)};
    if (percent < 0.1 || percent == 1.0)
        display = " " + to_string(percent * 100).substr(0, 3);
    return result + " " + display + "/100%";
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
        float cpu = processes[i]->CpuUtilization() * 100;
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