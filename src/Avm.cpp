#include <iostream>

#include "Avm.hpp"
#include "Exceptions.hpp"
#include "IOperand.hpp"

Avm::Avm(std::vector<Op> &instructions) : _instructions(std::move(instructions))
{
    _actions[PUSH] = &Avm::push;

    _actions[POP] = &Avm::pop;

    _actions[DUMP] = &Avm::dump;

    _actions[ASSERT] = &Avm::assert_actions;

    _actions[ADD] = &Avm::add;

    _actions[SUB] = &Avm::sub;

    _actions[MUL] = &Avm::mul;

    _actions[DIV] = &Avm::div;

    _actions[MOD] = &Avm::mod;

    _actions[PRINT] = &Avm::print;

    _actions[EXIT] = &Avm::exit_;
}

std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > Avm::get_operands() {
    if (_stack.size() < 2) {
            throw ToFewOperands();
        }

        std::shared_ptr<IOperand> f = _stack.back();
        _stack.pop_back();
        std::shared_ptr<IOperand> s = _stack.back();
        _stack.pop_back();

        return std::make_pair(f, s);
}

void Avm::push(std::shared_ptr<IOperand> op) {
   _stack.push_back(op); 
}
void Avm::pop(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        if (_stack.empty()) {
            throw PopOnEmpty();
        }
        _stack.pop_back();
}
void Avm::dump(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        for (auto e = _stack.rbegin(); e != _stack.rend(); e++) {
            std::cout << (*e)->toString() << std::endl;
        }
}
void Avm::assert_actions(std::shared_ptr<IOperand> op) {
     if (op->getType() != _stack.back()->getType() || op->toString() != _stack.back()->toString()) {
            throw AssertionError();
        }
}
void Avm::add(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > operands = get_operands();
        _stack.push_back(std::shared_ptr<IOperand>(const_cast<IOperand *>(*operands.first + *operands.second)));
}
void Avm::sub(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > operands = get_operands();
        _stack.push_back(std::shared_ptr<IOperand>(const_cast<IOperand *>(*operands.second - *operands.first)));
}
void Avm::mul(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > operands = get_operands();
        _stack.push_back(std::shared_ptr<IOperand>(const_cast<IOperand *>(*operands.first * *operands.second)));
}
void Avm::div(std::shared_ptr<IOperand> op) {
     static_cast<void>(op);
        std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > operands = get_operands();
        _stack.push_back(std::shared_ptr<IOperand>(const_cast<IOperand *>(*operands.second / *operands.first)));
}
void Avm::mod(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > operands = get_operands();
        _stack.push_back(std::shared_ptr<IOperand>(const_cast<IOperand *>(*operands.second % *operands.first)));
}
void Avm::print(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        if (_stack.back()->getType() != Int8) {
            throw AssertionError();
        }
        std::cout << static_cast<char>(std::stoi(_stack.back()->toString())) << std::endl;
}
void Avm::exit_(std::shared_ptr<IOperand> op) {
    static_cast<void>(op);
        exit(0);
}

void Avm::run()
{
    for (unsigned i = 0; i < _instructions.size(); i++) {
        ((*this).*(_actions[_instructions[i].first]))(_instructions[i].second);
    }
    throw ExitMissing();
}
