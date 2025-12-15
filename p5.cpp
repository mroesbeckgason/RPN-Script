#include "script.h"
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc!=2) {
        std::cout << "Exactly one argument required: the path of the script."
                  << std::endl;
        return 1;
    }

    Script script(argv[1]);
    while (script.is_halted() == false) {
        script.step();
    }

    std::cout << std::endl; // just to remove the % printed in my terminal
    return 0;
}
