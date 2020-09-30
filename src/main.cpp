#include "HuffmanArchiver.h"
#include "CLI.h"

#include <iostream>
#include <fstream>


int main(int argc, char *argv[]) {

    HuffmanCLI cli;
    HuffmanArchiver archiver;

    try {
        DataCLI data = cli(argc, argv);
        std::ifstream input(data.input);
        std::ofstream output(data.output);
        switch (data.mode) {
            case compress:
                std::cout << archiver.compress(input, output) << std::endl;
                break;
            case extract:
                std::cout << archiver.extract(input, output) << std::endl;
                break;
        }
    } catch (const ExceptionCLI &exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}
