#include "Parser.hpp"
#include <fstream>
#include <iostream>
#include "Exceptions.hpp"

Parser::Parser() : _isFile(false)
{
}

Parser::Parser(const std::string &file) : _isFile(true)
{
    _in.open(file);
    if (_in.is_open()) {
        std::cin.rdbuf(_in.rdbuf());
        std::cin.tie(nullptr);
    } else {
        throw BadFile();
    }
}

Parser::~Parser()
{
    if (_isFile) {
        _in.close();
    }
}

void Parser::parse()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        if (!_isFile && line == ";;") {
            break;
        }

        removeComment(line);

        if (!line.empty()) {
            _intructions.push_back(_lexer.verificate(line));
        }
    }
}

void Parser::removeComment(std::string &str)
{
    size_t pos = str.find_first_of(';');
    if (pos != std::string::npos) {
        str = str.substr(0, pos);
    }

    pos = str.find_last_not_of(' ');
    if (pos != std::string::npos) {
        str = str.substr(0, pos + 1);
    }
}

std::vector<Op> &Parser::getInstructions()
{
    return _intructions;
}
