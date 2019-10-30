#include "Lexer.hpp"
#include <cstring>
#include <regex>
#include "IOperand.hpp"
#include "Factory.hpp"

static std::array<std::pair<std::string, Instr>, INSTR_NUM> instructions = {
    std::make_pair("push", PUSH),     std::make_pair("pop", POP),  std::make_pair("dump", DUMP),
    std::make_pair("assert", ASSERT), std::make_pair("add", ADD),  std::make_pair("sub", SUB),
    std::make_pair("mul", MUL),       std::make_pair("div", DIV),  std::make_pair("mod", MOD),
    std::make_pair("print", PRINT),   std::make_pair("exit", EXIT)};

static std::array<std::pair<std::regex, eOperandType>, NumOfType> types = {
    std::make_pair(std::regex("^(int8\\([-]?[0-9]+\\))$"), Int8),
    std::make_pair(std::regex("^(int16\\([-]?[0-9]+\\))$"), Int16),
    std::make_pair(std::regex("^(int32\\([-]?[0-9]+\\))$"), Int32),
    std::make_pair(std::regex("^(float\\([-]?([0-9]*[.])?[0-9]+\\))$"), Float),
    std::make_pair(std::regex("^(double\\([-]?([0-9]*[.])?[0-9]+\\))$"), Double),
};

Op Lexer::verificate(std::string &str)
{
    Instr instr = get_instruction(str);
    std::shared_ptr<IOperand> val;

    if (instr == PUSH || instr == ASSERT) {
        Factory factory;
        eOperandType type = get_type(str);
        val = std::shared_ptr<IOperand>(const_cast<IOperand *>(factory.createOperand(type, str)));
    }

    return std::make_pair(instr, val);
}

Instr Lexer::get_instruction(std::string &str)
{
    Instr ret = INSTR_NUM;

    for (int i = 0; i < INSTR_NUM; i++) {
        if (std::strncmp(&instructions[i].first[0], &str[0], instructions[i].first.size()) == 0) {
            ret = instructions[i].second;
            if (ret == PUSH || ret == ASSERT) {
                if (str.size() < instructions[i].first.size() + 2)
                    throw SyntaxError();
                str = str.substr(instructions[i].first.size() + 1);
            } else {
                str = str.substr(instructions[i].first.size());
            }
            break;
        }
    }

    if (ret == INSTR_NUM) {
        throw UnknownInstruction();
    }

    return ret;
}

eOperandType Lexer::get_type(std::string &str)
{
    eOperandType ret = NumOfType;

    for (int i = 0; i < NumOfType; i++) {
        if (std::regex_match(str, types[i].first)) {
            ret = types[i].second;
            str = str.substr(str.find('(') + 1, str.find(')') - str.find('(') - 1);
            break;
        }
    }

    if (ret == NumOfType) {
        throw BadValue();
    }

    return ret;
}
