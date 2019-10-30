#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include <fstream>
#include <stack>
#include <string>
#include <vector>

#include "Common.hpp"
#include "IOperand.hpp"
#include "Lexer.hpp"

class Parser {
  public:

    Parser();
    explicit Parser(const std::string &file);
    ~Parser();

    void parse();
    std::vector<Op> &getInstructions();

  private:
    void removeComment(std::string &str);

    Parser(const Parser &);

    Parser &operator=(const Parser &);

    Lexer _lexer;
    std::vector<Op> _intructions;
    std::ifstream _in;
    bool _isFile;
};

#endif  // AVM_PARSER_HPP
