#ifndef AVM_COMMON_HPP
#define AVM_COMMON_HPP

#include <cstdint>
#include <memory>

class IOperand;

enum Instr { PUSH, POP, DUMP, ASSERT, ADD, SUB, MUL, DIV, MOD, PRINT, EXIT, INSTR_NUM };

enum eOperandType { Int8 = 0, Int16, Int32, Float, Double, NumOfType };

typedef std::pair<Instr, std::shared_ptr<IOperand> > Op;

template <typename T>
struct is_floating_point
{
    static const bool value;
};

template <typename T>
const bool is_floating_point<T>::value =
    std::numeric_limits<T>::is_specialized &&
    !std::numeric_limits<T>::is_integer;  

#endif  // AVM_COMMON_HPP
