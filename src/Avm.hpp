#ifndef Avm_HPP_
#define Avm_HPP_

#include <functional>
#include <stack>
#include <string>
#include <vector>
#include <array>

#include "Common.hpp"

class Avm {
    typedef void (Avm::*Action)(std::shared_ptr<IOperand>);

  public:
    explicit Avm(std::vector<Op> &instructions);

    void run();

  private:
    Avm();
    Avm(const Avm &);
    Avm &operator=(const Avm &);
    std::pair<std::shared_ptr<IOperand>, std::shared_ptr<IOperand> > get_operands();
    void push(std::shared_ptr<IOperand>);
    void pop(std::shared_ptr<IOperand>);
    void dump(std::shared_ptr<IOperand>);
    void assert_actions(std::shared_ptr<IOperand>);
    void add(std::shared_ptr<IOperand>);
    void sub(std::shared_ptr<IOperand>);
    void mul(std::shared_ptr<IOperand>);
    void div(std::shared_ptr<IOperand>);
    void mod(std::shared_ptr<IOperand>);
    void print(std::shared_ptr<IOperand>);
    void exit_(std::shared_ptr<IOperand>);
    std::vector<Op> _instructions;
    std::array<Action, INSTR_NUM> _actions;
    std::vector<std::shared_ptr<IOperand> > _stack;
};

#endif  // Avm_HPP_
