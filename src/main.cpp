#include <iostream>
#include <string>

#include <batch_command_handler.hpp>

int main(int argc, char** argv) {
    if (argc != 2)
        return 1;

    handler::BatchCommandHandler bch(std::stoi(argv[1]));
    bch.exec();

    return 0;
}
