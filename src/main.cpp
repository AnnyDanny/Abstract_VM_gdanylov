#include <iostream>
#include "Parser.hpp"
#include "Avm.hpp"
#include <memory>

int main(int ac, char *av[]) {
    try {
        std::unique_ptr<Parser> parser;

        if (ac == 2) {
            parser = std::unique_ptr<Parser>(new Parser(av[1]));
        } else if (ac == 1) {
            parser = std::unique_ptr<Parser>(new Parser());
        } else {
            std::cerr << "Too much arguments" << std::endl;
        }
        parser->parse();
        Avm avm(parser->getInstructions());
        avm.run();
    } catch (std::runtime_error &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return 0;
}
