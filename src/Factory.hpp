#ifndef AVM_FACTORY_HPP
#define AVM_FACTORY_HPP

#include <array>
#include <cfenv>
#include <functional>
#include <string>

#include "Common.hpp"
#include "Exceptions.hpp"

class IOperand;

class Factory {
    typedef IOperand const *(Factory::* Func)(const std::string &) const;

  public:
    Factory();

    IOperand const *createOperand(eOperandType type, std::string const &value) const;

  private:
    Factory(const Factory &);
    Factory &operator=(const Factory &);

    IOperand const *createInt8(std::string const &value) const;
    IOperand const *createInt16(std::string const &value) const;
    IOperand const *createInt32(std::string const &value) const;
    IOperand const *createFloat(std::string const &value) const;
    IOperand const *createDouble(std::string const &value) const;

    template <typename T>
    IOperand const *createOperand(std::string const &value, int precision, eOperandType type) const;

    std::array<Func, NumOfType> _funcs;
};

#endif  // AVM_FACTORY_HPP
