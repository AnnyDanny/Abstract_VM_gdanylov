#ifndef AVM_LEXER_HPP
#define AVM_LEXER_HPP

#include <string>
#include "Common.hpp"

class Lexer {
  public:
    Lexer() {}

    Op verificate(std::string &str);

  private:
    Instr get_instruction(std::string &str);
    eOperandType get_type(std::string &str);
};

#endif  // AVM_LEXER_HPP
