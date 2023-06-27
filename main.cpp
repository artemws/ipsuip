/** Made by I'Pancake **/

#include "choose_your_fate.h"
#include <exception>
#include <iostream>

int main(int argc, char **argv)
{
    try {
        return choose_your_fate(argc, argv);

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
