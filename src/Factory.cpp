#include "Factory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include <functional>
#include <cfenv>

Factory::Factory()
{
    _funcs[Int8] = &Factory::createInt8;
    _funcs[Int16] = &Factory::createInt16;
    _funcs[Int32] = &Factory::createInt32;
    _funcs[Float] = &Factory::createFloat;
    _funcs[Double] = &Factory::createDouble;
}

IOperand const *Factory::createOperand(eOperandType type, std::string const &value) const
{
    return ((*this).*(_funcs[type]))(value);
}

IOperand const *Factory::createInt8(std::string const &value) const
{
    return createOperand<int8_t>(value, 1, Int8);
}

IOperand const *Factory::createInt16(std::string const &value) const
{
    return createOperand<int16_t>(value, 2, Int16);
}

IOperand const *Factory::createInt32(std::string const &value) const
{
    return createOperand<int32_t>(value, 3, Int32);
}

IOperand const *Factory::createFloat(std::string const &value) const
{
    return createOperand<float>(value, 4, Float);
}

IOperand const *Factory::createDouble(std::string const &value) const
{
    return createOperand<double>(value, 5, Double);
}  

template <typename T>
IOperand const *Factory::createOperand(std::string const &value, int precision, eOperandType type) const
{
    T res;

    try {
        if (is_floating_point<T>::value) {
            std::feclearexcept(FE_OVERFLOW);
            std::feclearexcept(FE_UNDERFLOW);
            double val = std::stod(value);
            res = val;
            if ((bool)std::fetestexcept(FE_OVERFLOW)) {
                throw Overflow();
            }
            if ((bool)std::fetestexcept(FE_OVERFLOW)) {
                throw Underflow();
            }
            
        }
        else {
            int32_t val = std::stoi(value);
            res = val;
            if (res != val) {
                 if (val < 0) {
                    throw Underflow();
                }
                throw Overflow();
            }
        }
    } catch (std::out_of_range &) {
        if (value[0] == '-') {
            throw Underflow();
        }
        throw Overflow();
    }

    return new Operand<T>(res, precision, type);
}
