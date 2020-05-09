#include "ncurses_display.h"
#include "system.h"

#include <iostream>
#include <fstream>

int main() {

    try{
        System system;
        NCursesDisplay::Display(system);
    }
    catch(std::exception& e) {
        std::ofstream ofs {"debug.txt", std::ios_base::app};
        ofs << e.what() << "/t" <<'\n';
    }
}